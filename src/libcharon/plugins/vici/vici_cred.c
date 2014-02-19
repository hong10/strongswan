/*
 * Copyright (C) 2014 Martin Willi
 * Copyright (C) 2014 revosec AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "vici_cred.h"
#include "vici_builder.h"

#include <credentials/sets/mem_cred.h>
#include <credentials/certificates/ac.h>
#include <credentials/certificates/crl.h>
#include <credentials/certificates/x509.h>

typedef struct private_vici_cred_t private_vici_cred_t;

/**
 * Private data of an vici_cred_t object.
 */
struct private_vici_cred_t {

	/**
	 * Public vici_cred_t interface.
	 */
	vici_cred_t public;

	/**
	 * Dispatcher
	 */
	vici_dispatcher_t *dispatcher;

	/**
	 * credentials
	 */
	mem_cred_t *creds;
};

/**
 * Create a (error) reply message
 */
static vici_message_t* create_reply(char *fmt, ...)
{
	vici_builder_t *builder;
	va_list args;

	builder = vici_builder_create();
	builder->add_kv(builder, "success", fmt ? "no" : "yes");
	if (fmt)
	{
		va_start(args, fmt);
		builder->vadd_kv(builder, "errmsg", fmt, args);
		va_end(args);
	}
	return builder->finalize(builder);
}

CALLBACK(load_cert, vici_message_t*,
	private_vici_cred_t *this, char *name, u_int id, vici_message_t *message)
{
	certificate_type_t type;
	x509_flag_t required_flags = 0, additional_flags = 0;
	certificate_t *cert;
	x509_t *x509;
	chunk_t data;
	char *str;

	str = message->get_str(message, NULL, "type");
	if (!str)
	{
		return create_reply("certificate type missing");
	}
	if (strcaseeq(str, "x509"))
	{
		type = CERT_X509;
	}
	else if (strcaseeq(str, "x509ca"))
	{
		type = CERT_X509;
		required_flags = X509_CA;
	}
	else if (strcaseeq(str, "x509aa"))
	{
		type = CERT_X509;
		additional_flags = X509_AA;
	}
	else if (strcaseeq(str, "x509crl"))
	{
		type = CERT_X509_CRL;
	}
	else if (strcaseeq(str, "x509ac"))
	{
		type = CERT_X509_AC;
	}
	else
	{
		return create_reply("invalid certificate type: %s", str);
	}
	data = message->get_value(message, chunk_empty, "data");
	if (!data.len)
	{
		return create_reply("certificate data missing");
	}
	cert = lib->creds->create(lib->creds, CRED_CERTIFICATE, type,
							  BUILD_BLOB_PEM, data,
							  BUILD_X509_FLAG, additional_flags,
							  BUILD_END);
	if (!cert)
	{
		return create_reply("parsing %N certificate failed",
							certificate_type_names, type);
	}
	if (cert->get_type(cert) == CERT_X509)
	{
		x509 = (x509_t*)cert;

		if ((required_flags & x509->get_flags(x509)) != required_flags)
		{
			cert->destroy(cert);
			return create_reply("certificate misses required flag, rejected");
		}
	}

	DBG1(DBG_CFG, "loaded certificate '%Y'", cert->get_subject(cert));

	this->creds->add_cert(this->creds, TRUE, cert);

	return create_reply(NULL);
}

CALLBACK(load_key, vici_message_t*,
	private_vici_cred_t *this, char *name, u_int id, vici_message_t *message)
{
	key_type_t type;
	private_key_t *key;
	chunk_t data;
	char *str;

	str = message->get_str(message, NULL, "type");
	if (!str)
	{
		return create_reply("key type missing");
	}
	if (strcaseeq(str, "any"))
	{
		type = KEY_ANY;
	}
	else if (strcaseeq(str, "rsa"))
	{
		type = KEY_RSA;
	}
	else if (strcaseeq(str, "ecdsa"))
	{
		type = KEY_ECDSA;
	}
	else
	{
		return create_reply("invalid key type: %s", str);
	}
	data = message->get_value(message, chunk_empty, "data");
	if (!data.len)
	{
		return create_reply("key data missing");
	}
	key = lib->creds->create(lib->creds, CRED_PRIVATE_KEY, type,
							 BUILD_BLOB_PEM, data, BUILD_END);
	if (!key)
	{
		return create_reply("parsing %N private key failed",
							key_type_names, type);
	}

	DBG1(DBG_CFG, "loaded %N private key", key_type_names, type);

	this->creds->add_key(this->creds, key);

	return create_reply(NULL);
}

CALLBACK(clear_creds, vici_message_t*,
	private_vici_cred_t *this, char *name, u_int id, vici_message_t *message)
{
	vici_builder_t *builder;

	this->creds->clear(this->creds);

	builder = vici_builder_create();
	return builder->finalize(builder);
}

static void manage_command(private_vici_cred_t *this,
						   char *name, vici_command_cb_t cb, bool reg)
{
	this->dispatcher->manage_command(this->dispatcher, name,
									 reg ? cb : NULL, this);
}

/**
 * (Un-)register dispatcher functions
 */
static void manage_commands(private_vici_cred_t *this, bool reg)
{
	manage_command(this, "clear-creds", clear_creds, reg);
	manage_command(this, "load-cert", load_cert, reg);
	manage_command(this, "load-key", load_key, reg);
}

METHOD(vici_cred_t, destroy, void,
	private_vici_cred_t *this)
{
	manage_commands(this, FALSE);

	lib->credmgr->remove_set(lib->credmgr, &this->creds->set);
	this->creds->destroy(this->creds);
	free(this);
}

/**
 * See header
 */
vici_cred_t *vici_cred_create(vici_dispatcher_t *dispatcher)
{
	private_vici_cred_t *this;

	INIT(this,
		.public = {
			.destroy = _destroy,
		},
		.dispatcher = dispatcher,
		.creds = mem_cred_create(),
	);

	lib->credmgr->add_set(lib->credmgr, &this->creds->set);

	manage_commands(this, TRUE);

	return &this->public;
}
