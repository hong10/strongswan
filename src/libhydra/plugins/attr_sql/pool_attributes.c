/*
 * Copyright (C) 2009-2010 Andreas Steffen
 * Hochschule fuer Technik Rapperswil
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

#define _GNU_SOURCE
#include <string.h>

#include <library.h>
#include <utils/host.h>

#include "pool_attributes.h"
#include "pool_usage.h"

/**
 * global database handle
 */
extern database_t *db;

#define UNITY_NETWORK_LEN	14

ENUM(value_type_names, VALUE_HEX, VALUE_SUBNET,
	"hex",
	"string",
	"server",
	"subnet"
);

typedef struct attr_info_t attr_info_t;

struct attr_info_t {
	char*                           keyword;
	value_type_t                    value_type;
	configuration_attribute_type_t  type;
	configuration_attribute_type_t  type_ip6;
};

static const attr_info_t attr_info[] = {
	{ "internal_ip4_dns",    VALUE_ADDR,   INTERNAL_IP4_DNS,    0 },
	{ "internal_ip6_dns",    VALUE_ADDR,   INTERNAL_IP6_DNS,    0 },
	{ "dns",                 VALUE_ADDR,   INTERNAL_IP4_DNS,
										   INTERNAL_IP6_DNS       },
	{ "internal_ip4_nbns",   VALUE_ADDR,   INTERNAL_IP4_NBNS,   0 },
	{ "internal_ip6_nbns",   VALUE_ADDR,   INTERNAL_IP6_NBNS,   0 },
	{ "nbns",                VALUE_ADDR,   INTERNAL_IP4_NBNS,
										   INTERNAL_IP6_NBNS      },
	{ "wins",                VALUE_ADDR,   INTERNAL_IP4_NBNS,
										   INTERNAL_IP6_NBNS      },
	{ "internal_ip4_dhcp",   VALUE_ADDR,   INTERNAL_IP4_DHCP,   0 },
	{ "internal_ip6_dhcp",   VALUE_ADDR,   INTERNAL_IP6_DHCP,   0 },
	{ "dhcp",                VALUE_ADDR,   INTERNAL_IP4_DHCP,
										   INTERNAL_IP6_DHCP      },
	{ "internal_ip4_server", VALUE_ADDR,   INTERNAL_IP4_SERVER, 0 },
	{ "internal_ip6_server", VALUE_ADDR,   INTERNAL_IP6_SERVER, 0 },
	{ "server",              VALUE_ADDR,   INTERNAL_IP4_SERVER,
										   INTERNAL_IP6_SERVER    },
	{ "application_version", VALUE_STRING, APPLICATION_VERSION, 0 },
	{ "version",             VALUE_STRING, APPLICATION_VERSION, 0 },
	{ "unity_banner",        VALUE_STRING, UNITY_BANNER,        0 },
	{ "banner",              VALUE_STRING, UNITY_BANNER,        0 },
	{ "unity_splitdns_name", VALUE_STRING, UNITY_SPLITDNS_NAME, 0 },
	{ "unity_split_include", VALUE_SUBNET, UNITY_SPLIT_INCLUDE, 0 },
	{ "unity_local_lan",     VALUE_SUBNET, UNITY_LOCAL_LAN,     0 },
};

/**
 * Determine the type of the attribute and its value
 */
static bool parse_attributes(char *name, char *value, value_type_t *value_type,
							 configuration_attribute_type_t *type,
							 configuration_attribute_type_t *type_ip6,
							 chunk_t *blob)
{
	host_t *addr = NULL, *mask = NULL;
	chunk_t addr_chunk, mask_chunk;
	char *text = "", *pos, *endptr;
	int i;

	switch (*value_type)
	{
		case VALUE_STRING:
			*blob = chunk_create(value, strlen(value));
			*blob = chunk_clone(*blob);
			break;
		case VALUE_HEX:
			*blob = chunk_from_hex(chunk_create(value, strlen(value)), NULL);
			break;
		case VALUE_ADDR:
			addr = host_create_from_string(value, 0);
			if (addr == NULL)
			{
				fprintf(stderr, "invalid IP address: '%s'.\n", value);
				return FALSE;
			}
			addr_chunk = addr->get_address(addr);
			*blob = chunk_clone(addr_chunk);
			break;
		case VALUE_SUBNET:
			pos = strchr(value, '/');
			if (pos == NULL || (value - pos) == strlen(value))
			{
				fprintf(stderr, "invalid IPv4 subnet: '%s'.\n", value);
				return FALSE;
			}
			*pos = '\0';
			addr = host_create_from_string(value, 0);
			mask = host_create_from_string(pos+1, 0);
			if (addr == NULL || addr->get_family(addr) != AF_INET ||
				mask == NULL || mask->get_family(addr) != AF_INET)
			{
				fprintf(stderr, "invalid IPv4 subnet: '%s'.\n", value);
				DESTROY_IF(addr);
				DESTROY_IF(mask);
				return FALSE;
			}
			addr_chunk = addr->get_address(addr);
			mask_chunk = mask->get_address(mask);
			*blob = chunk_alloc(UNITY_NETWORK_LEN);
			memset(blob->ptr, 0x00, UNITY_NETWORK_LEN);
			memcpy(blob->ptr,     addr_chunk.ptr, 4);
			memcpy(blob->ptr + 4, mask_chunk.ptr, 4);
			addr->destroy(addr);
			mask->destroy(mask);
			break;
		case VALUE_NONE:
			*blob = chunk_empty;
			break;
	}

	/* init the attribute type */
	*type     = 0;
	*type_ip6 = 0;

	for (i = 0; i < countof(attr_info); i++)
	{
		if (strcaseeq(name, attr_info[i].keyword))
		{
			if (*value_type == VALUE_NONE)
			{
				*value_type = attr_info[i].value_type;
				*type       = attr_info[i].type;
				*type_ip6   = attr_info[i].type_ip6;
				return TRUE;
			}
			if (*value_type != attr_info[i].value_type &&
				*value_type != VALUE_HEX)
			{
				switch (attr_info[i].value_type)
				{
					case VALUE_STRING:
						text = "a string";
						break;
					case VALUE_HEX:
						text = "a hex";
						break;
					case VALUE_ADDR:
						text = "an IP address";
						break;
					case VALUE_SUBNET:
						text = "a subnet";
						break;
					case VALUE_NONE:
						text = "no";
						break;
				}
				fprintf(stderr, "the %s attribute requires %s value.\n",
								 name, text);
				DESTROY_IF(addr);
				free(blob->ptr);
				return FALSE;
			}
			if (*value_type == VALUE_ADDR)
			{
				*type = (addr->get_family(addr) == AF_INET) ?
						 	attr_info[i].type : attr_info[i].type_ip6;
				addr->destroy(addr);
			}
			if (*value_type == VALUE_HEX)
			{
				*value_type = attr_info[i].value_type;

				if (*value_type == VALUE_ADDR)
				{
					if (blob->len == 4)
					{
						*type = attr_info[i].type;
					}
					else if (blob->len == 16)
					{
						*type = attr_info[i].type_ip6;
					}
					else
					{
						fprintf(stderr, "the %s attribute requires "
										"a valid IP address.\n", name);
						free(blob->ptr);
						return FALSE;
					}
				}
				else
				{
					*type = attr_info[i].type;
				}			
			}
			else
			{
				*type = attr_info[i].type;
			}
			return TRUE;
		}
	}

	/* clean up */
	DESTROY_IF(addr);

	/* is the attribute type numeric? */	
	*type = strtol(name, &endptr, 10);

	if (*endptr != '\0')
	{
		fprintf(stderr, "the %s attribute is not recognized.\n", name);
		free(blob->ptr);
		return FALSE;
	}
	if (*value_type == VALUE_NONE)
	{
		*value_type = VALUE_HEX;
	}
	return TRUE;
}
 
/**
 * ipsec pool --addattr <type> --string|server|subnet - add attribute entry
 */
void add_attr(char *name, char *value, value_type_t value_type)
{
	configuration_attribute_type_t type, type_ip6;
	chunk_t blob;
	bool success;

	if (value_type == VALUE_NONE)
	{
		fprintf(stderr, "the value of the %s attribute is missing.\n", name);
		usage();
		exit(EXIT_FAILURE);
	}	
	if (!parse_attributes(name, value, &value_type, &type, &type_ip6, &blob))
	{
		exit(EXIT_FAILURE);
	}
	success = db->execute(db, NULL,
				"INSERT INTO attributes (type, value) VALUES (?, ?)",
				DB_INT, type, DB_BLOB, blob) == 1;
	free(blob.ptr);

	if (success)
	{
		printf("added %s attribute (%N).\n", name,
				configuration_attribute_type_names, type);
	}
	else
	{
		fprintf(stderr, "adding %s attribute (%N) failed.\n", name,
						 configuration_attribute_type_names, type);
		exit(EXIT_FAILURE);
	}
}

/**
 * ipsec pool --delattr <type> --string|server|subnet - delete attribute entry
 */
void del_attr(char *name, char *value, value_type_t value_type)
{
	configuration_attribute_type_t type, type_ip6, type_db;
	chunk_t blob, blob_db;
	u_int id;
	enumerator_t *query;
	bool found = FALSE;

	if (!parse_attributes(name, value, &value_type, &type, &type_ip6, &blob))
	{
		exit(EXIT_FAILURE);
	}
	if (blob.len > 0)
	{
		query = db->query(db,
					"SELECT id, type, value FROM attributes "
					"WHERE type = ? AND value = ?",
					DB_INT, type, DB_BLOB, blob,
					DB_UINT, DB_INT, DB_BLOB);
	}
	else if (type_ip6 == 0)
	{
		query = db->query(db,
					"SELECT id, type, value FROM attributes "
					"WHERE type = ?",
					DB_INT, type, 
					DB_UINT, DB_INT, DB_BLOB);
	}
	else
	{
		query = db->query(db,
					"SELECT id, type, value FROM attributes "
					"WHERE type = ? OR type = ?",
					DB_INT, type, DB_INT, type_ip6,
					DB_UINT, DB_INT, DB_BLOB);
	}

	if (!query)
	{
		fprintf(stderr, "deleting '%s' attribute (%N) failed.\n",
						 name, configuration_attribute_type_names, type);
		free(blob.ptr);
		exit(EXIT_FAILURE);
	}

	while (query->enumerate(query, &id, &type_db, &blob_db))
	{
		host_t *server = NULL;

		found = TRUE;

		if (value_type == VALUE_ADDR)
		{
			int family = (type_db == type_ip6) ? AF_INET6 : AF_INET;

			server = host_create_from_chunk(family, blob_db, 0);
		}

		if (db->execute(db, NULL,
					"DELETE FROM attributes WHERE id = ?",
					 DB_UINT, id) != 1)
		{
			if (server)
			{
				fprintf(stderr, "deleting %s server %H failed\n", name, server);
				server->destroy(server);
			}
			else if (value_type == VALUE_STRING)
			{
				fprintf(stderr, "deleting %s attribute (%N) with value '%.*s' failed.\n",
						 		name, configuration_attribute_type_names, type,
								blob_db.len, blob_db.ptr);
			}

			else
			{
				fprintf(stderr, "deleting %s attribute (%N) with value %#B failed.\n",
						 		name, configuration_attribute_type_names, type,
								&blob_db);
			}
			query->destroy(query);
			free(blob.ptr);
			exit(EXIT_FAILURE);
		}
		if (server)
		{
			printf("deleted %s server %H\n", name, server);
			server->destroy(server);
		}
		else if (value_type == VALUE_STRING)
		{
			printf("deleted %s attribute (%N) with value '%.*s'.\n",
				   name, configuration_attribute_type_names, type,
				   blob_db.len, blob_db.ptr);
		}
		else
		{
			printf("deleted %s attribute (%N) with value %#B.\n",
				   name, configuration_attribute_type_names, type,
				   &blob_db);
		}
	}
	query->destroy(query);

	if (!found)
	{
	 	if (blob.len == 0)
		{
			if (type_ip6 == 0)
			{
				fprintf(stderr, "no %s attribute (%N) was found.\n", name,
								 configuration_attribute_type_names, type);
			}
			else
			{
				fprintf(stderr, "no %s attribute was found.\n",	name);
			}
		}
		else
		{	
			if (value_type == VALUE_ADDR)
			{
				host_t *server = host_create_from_chunk(AF_UNSPEC, blob, 0);
	
				fprintf(stderr, "the %s server %H was not found.\n", name,
								 server);
				server->destroy(server);
			}
			else
			{
				fprintf(stderr, "the %s attribute (%N) with value '%*.s' "
								"was not found.\n", name,
								 configuration_attribute_type_names, type,
								 blob.len, blob.ptr);
			}
		}
		free(blob.ptr);
		exit(EXIT_FAILURE);
	}
	free(blob.ptr);
}

/**
 * ipsec pool --statusattr - show all attribute entries
 */
void status_attr(void)
{
	configuration_attribute_type_t type;
	chunk_t value;
	enumerator_t *enumerator;
	char type_name[30];
	bool first = TRUE;

	/* enumerate over all attributes */
	enumerator = db->query(db, "SELECT type, value FROM attributes ORDER BY type",
								DB_INT, DB_BLOB);
	if (enumerator)
	{
		while (enumerator->enumerate(enumerator, &type, &value))
		{
			if (first)
			{
				printf(" type  description          value\n");
				first = FALSE;
			}
			snprintf(type_name, sizeof(type_name), "%N",
					 configuration_attribute_type_names, type);
			if (type_name[0] == '(')
			{
				type_name[0] = '\0';
			}
			printf("%5d  %-20s %#B\n",type, type_name, &value);
		}
		enumerator->destroy(enumerator);
	}
}

/**
 * ipsec pool --showattr - show all supported attribute keywords
 */
void show_attr(void)
{
	int i;

	for (i = 0; i < countof(attr_info); i++)
	{
		char value_name[10];
		
		
		snprintf(value_name, sizeof(value_name), "%N",
			value_type_names, attr_info[i].value_type);
	
		printf("%-19s  --%-6s  (%N", 
				attr_info[i].keyword, value_name, 
				configuration_attribute_type_names, attr_info[i].type);

		if (attr_info[i].type_ip6)
		{
			printf(", %N)\n",
				configuration_attribute_type_names, attr_info[i].type_ip6);
		}
		else
		{
			printf(")\n");
		}
	}
}

