/* Identities */

INSERT INTO identities (
  type, data
) VALUES ( /* C=CH, O=Linux strongSwan, CN=strongSwan Root CA */
  9, X'3045310B300906035504061302434831193017060355040A13104C696E7578207374726F6E675377616E311B3019060355040313127374726F6E675377616E20526F6F74204341'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* subjkey of 'C=CH, O=Linux strongSwan, CN=strongSwan Root CA' */
  11, X'5da7dd700651327ee7b66db3b5e5e060ea2e4def'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* keyid of 'C=CH, O=Linux strongSwan, CN=strongSwan Root CA' */
  11, X'ae096b87b44886d3b820978623dabd0eae22ebbc'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* moon.strongswan.org */
  2, X'6d6f6f6e2e7374726f6e677377616e2e6f7267'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* sun.strongswan.org */
  2, X'73756e2e7374726f6e677377616e2e6f7267'
 );

INSERT INTO identities (
  type, data
) VALUES ( /* subjkey of 'C=CH, O=Linux strongSwan, CN=moon.strongswan.org' */
  11, X'6a9c74d1f8897989f65a94e989f1fac3649d292e'
 );

/* Certificates */

INSERT INTO certificates (
   type, keytype, data
) VALUES ( /* C=CH, O=Linux strongSwan, CN=strongSwan Root CA */
  1, 1, X'2d2d2d2d2d424547494e2043455254494649434154452d2d2d2d2d0a4d494944754443434171436741774942416749424144414e42676b71686b69473977304241517346414442464d517377435159445651514745774a445344455a0a4d4263474131554543684d5154476c7564586767633352796232356e55336468626a45624d426b474131554541784d53633352796232356e55336468626942530a6232393049454e424d423458445441304d446b784d4445774d4445784f466f58445445354d446b774e7a45774d4445784f466f775254454c4d416b47413155450a42684d43513067784754415842674e5642416f5445457870626e563449484e30636d39755a314e3359573478477a415a42674e5642414d54456e4e30636d39750a5a314e3359573467556d39766443424451544343415349774451594a4b6f5a496876634e4151454242514144676745504144434341516f4367674542414c2f790a58324c7150565a75574c5049656b6e4b383678687a366c6a64334e4e6843327a2b5031756f43503373424d755a695a51456a467a686e4b6362587843656f32660a466e76684f4f6a727269735375566b7a757538326f7858443366496b7a7553376d395634453130455a7a676d4b5749662b57754e52666267417555494e6d4c630a345947415842514c50797a7050344f75343868687a2f59516f3538426963733650487935763334714356524f4958447671686a39315038672b70532b4632312f0a37502b4348326a5263564945485a7447384d2f507765545051393564507a705964324f7636535a2f553745576d624d6d5438566355596e3161436878466d79350a6777655642576c6b48364d502b31446545302f744c35633837786f354b4365474b3854647170653773425243347050454548445163695455766b65754a3150720a4b2b314c77647152786f3748674d5269447738434177454141614f42736a4342727a415342674e5648524d4241663845434441474151482f416745424d4173470a413155644477514541774942426a416442674e5648513445466751555861666463415a524d6e376e746d327a74655867594f6f7554653877625159445652306a0a424759775a4941555861666463415a524d6e376e746d327a74655867594f6f7554652b68536152484d455578437a414a42674e5642415954416b4e494d526b770a467759445651514b4578424d615735316543427a64484a76626d6454643246754d527377475159445651514445784a7a64484a76626d64546432467549464a760a6233516751304743415141774451594a4b6f5a496876634e4151454c425141446767454241434f536d71454274424c52396156335579434938676d7a5235696e0a4c74653961555858532b716973364632683253746634734e2b4e6c36476a37524543365370664548347757647769554c354a30434a68796f4f6a5175446c336e0a314477336445342f7a714d5a6479444b455954553735546d7675734e4a426447734c6b726637454154416a6f692f6e72544f5950506853555a7650702f442b590a764f524a39456a353147586c4b316e774542356941382b7444596e694e516e364244314d456749656a7a4b2b66626979376272615a42316b71686f45723253690a376c7542536e55393132737734393445383861324557626d4d766732545648504e7a4370566b704e6b376b69664369776d7739566c646b71597939792f6c43610a45707970376c54664b77376362443034566b38514a573738324c36437375786b6c333436623137776d4f716e38415a6970733374467375415933773d0a2d2d2d2d2d454e442043455254494649434154452d2d2d2d2d0a'
);

INSERT INTO certificates (
   type, keytype, data
) VALUES ( /* C=CH, O=Linux strongSwan, CN=moon.strongswan.org */
  1, 1, X'2d2d2d2d2d424547494e2043455254494649434154452d2d2d2d2d0a4d494945496a4343417771674177494241674942467a414e42676b71686b69473977304241517346414442464d517377435159445651514745774a445344455a0a4d4263474131554543684d5154476c7564586767633352796232356e55336468626a45624d426b474131554541784d53633352796232356e55336468626942530a6232393049454e424d423458445441354d4467794e7a45774d444d7a4d6c6f58445445304d4467794e6a45774d444d7a4d6c6f77526a454c4d416b47413155450a42684d43513067784754415842674e5642416f5445457870626e563449484e30636d39755a314e33595734784844416142674e5642414d5445323176623234750a633352796232356e6333646862693576636d6377676745694d4130474353714753496233445145424151554141344942447741776767454b416f49424151444b0a4c324d39314c753642595968577857674d53397a39544d535477737a6d3572684f375a497343744d526f3450416559772b2b2b5347587433435058622f2b702b0a53574b476c6d313172504537316551336568676832433368417572666d574f306951516143772b6664726565495643714f51494f503655715a333237683579590a5970486b385651763476424a547078636c553150716e5768657165315a6c4c7873573737334c526d6c2f6651742f5567764a6b4342545a5a4f4e4c4e4d664b2b0a3754446e5961567341746e636776444e37386e554e456532715939324b4b375372424a36537055456734396d3531462b586773476373675756485338356f6e330a4f6d2f47343863724c45564a6a6475384378657753525667622b6c504a577a4864385173553056672f37766c7173335a524d794e744e4b7272346f70537656620a41366167476c5458684443726544695855384b4841674d424141476a676745614d494942466a414a42674e5648524d45416a41414d41734741315564447751450a417749447144416442674e564851344546675155617078303066694a65596e325770547069664836773253644b533477625159445652306a424759775a4941550a5861666463415a524d6e376e746d327a74655867594f6f7554652b68536152484d455578437a414a42674e5642415954416b4e494d526b77467759445651514b0a4578424d615735316543427a64484a76626d6454643246754d527377475159445651514445784a7a64484a76626d64546432467549464a7662335167513047430a4151417748675944565230524242637746594954625739766269357a64484a76626d647a643246754c6d39795a7a415442674e56485355454444414b426767720a42674546425163444154413542674e56485238454d6a41774d4336674c4b41716869686f644852774f69387659334a734c6e4e30636d39755a334e33595734750a62334a6e4c334e30636d39755a334e335957347559334a734d4130474353714753496233445145424377554141344942415143637458673278654d6f7a6154560a6a69424c3150384d5939754548354a7455304563655131526249352f32764752646e45434e44396f4144593576616d616145324d64713251682f766c586e4d4c0a6f33696935454c6a73516c596454595a4f634d4f6463555558597662624658316377706b426879426c314832354b7074486367512f486e63654b70336b4f75710a77594f596a6777655058756c6370575878304532517451434651515a4650794557654e4a7848306f676c6735335150586648593949322f47756b6a355630627a0a70374d45304773384b646e59646d626244717a51675073746139362f6d2b486f4a6c737256462b34477169686a3642574d42513279626a50575a6447336f48390a32356345387636305279393844305a2f747967624155466e68356f4f766166363432706156676333616f4137374938552b555a6a45437849536f6948756c74590a37515475664f77500a2d2d2d2d2d454e442043455254494649434154452d2d2d2d2d0a'
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  1, 1
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  1, 2
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  1, 3
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  2, 4 
);

INSERT INTO certificate_identity (
  certificate, identity
) VALUES (
  2, 6 
);

/* Private Keys */

INSERT INTO private_keys (
   type, data
) VALUES ( /* key of 'C=CH, O=Linux strongSwan, CN=moon.strongswan.org' */
  1, X'2d2d2d2d2d424547494e205253412050524956415445204b45592d2d2d2d2d0a4d4949456f77494241414b43415145417969396a5064533775675747495673566f444576632f557a456b384c4d35756134547532534c41725445614f4477486d0a4d5076766b686c3764776a31322f2f71666b6c6968705a7464617a784f39586b4e336f594964677434514c7133356c6a74496b45476773506e3361336e6946510a716a6b43446a2b6c4b6d6439753465636d474b52355046554c2b4c7753553663584a564e543670316f58716e74575a53386246752b3979305a706633304c66310a494c795a4167553257546a537a544879767530773532476c62414c5a33494c777a652f4a3144524874716d506469697530717753656b715642494f505a7564520a666c344c426e4c49466c5230764f614a397a7076787550484b797846535933627641735873456b5659472f7054795673783366454c464e4659502b373561724e0a3255544d6a62545371362b4b4b55723157774f6d6f42705531345177713367346c3150436877494441514142416f494241434246422f5871616a763666626e390a4b367078727a3032755877476d61635841745649446f507a656a576d5853345141346c313748724a446d656c536e68656c444b7279386e6e59486b5472547a370a6d6e307751344844577938366f2f6f6b4a55472f544b524c64366266373961525171716f6871643369516b486b343347797a7558482b6f47696f564b463066630a41434457773477666a4c37464d4e6448435a34427a394472484f2f79734865394236727653596d33565a52685378616e65496b614c6b6b4461644b70567833660a584e466c4d785934714b504a5959536f4a5a3631694d71724f372b726e413933746d7944447338504b553342746e70664e72646550676c654a48686b385a71790a4576322f4e4f43535578624b45384e43744c704754732b5430716a6a6e75346b33575064335a4f4241616e30755044656b485a6548422f6158474c68596378780a4a35537572714543675945412b46316770706b4552354a746f617564742f43557064513173523977786637355642714a34466959414247517a39786c47346f6a0a7a4c2f6f3537327330695633627746706e51612b5775577278476b50365a75422f5a38326e7063304e2f764c6f752f623464787667346e374b2b654f4f4566300a38464d6a7373653274715449584b4371636d516e52304e5051316a777576454b73585035772f4a4f6c6e525841586e64346a78734a49304367594541304761540a3631795374745557396a43336d787559366a6b5179385445517152336e4f467657776d435849574f704e2f4d54545075732b54656c78702f70644b68552b6d6f0a506d5833556e796e65355076776c6557447133597a6c7458355a445a474a35554a6c4b754e6e6647497a51364f6348526262377a4270514736715352507575670a62676f36383868546e62314c35396e4b38387a57564b3435657566367079756f492b537749474d436759454137797645386b6e7968425876657a7576307a31620a6547486d4870352f564477593044514b5345416f6942426957726b4c714c7962677758662f4b4a38645a5a6338456e303861465832474c4a7959652f4b6942310a797333797045424a716776526179502b6f2f394b5a2b714e4e5264307271416b735058764c3741424e4e74306b7a617054535644616533597536732f6a31616d0a44494c35714165455249446564473575445070517a645543675942374d746a705036334142684c76385862706242516e43787442797733573839462b586372740a7635356751646845346353754d7a412f43754d4834764e7050533641493961424a4e686a3343744b6f2f634f4a616368414762312f77766b4f35414c764c57300a66685a6450737455546e444a61696e377666462f68777a62732f506c685867753954394b6c4c665276584664472b53643467386d756d52696f7a634c6b6f52770a7936585054774b4267444a502b733977586d644739304853542f61714337464b7256584c7042363364593573774e556651503673613070466e4f4e3072304a430a682f594373474646494165625132754f6b4d33673366396e6b775470373931306f762b2f3575546876524932773242425079306d5675414c506a797946315a320a6362397a70794b694975586f585243663473643872316c5239626e304678783053767078662b66704d475349357175484e424b590a2d2d2d2d2d454e44205253412050524956415445204b45592d2d2d2d2d0a'
);

INSERT INTO private_key_identity (
  private_key, identity
) VALUES (
  1, 4 
);

INSERT INTO private_key_identity (
  private_key, identity
) VALUES (
  1, 6 
);

/* Algorithms */

INSERT INTO algorithms (
  algorithm
) VALUES (
  'aes128-sha256-modp2048'
);

INSERT INTO algorithms (
  algorithm
) VALUES (
  'aes192-sha384-modp3072'
);

INSERT INTO algorithms (
  algorithm
) VALUES (
  'aes128gcm128'
);

INSERT INTO algorithms (
  algorithm
) VALUES (
  'aes192gcm128'
);

/* Configurations */

INSERT INTO ike_configs (
  local, remote
) VALUES (
  'PH_IP_MOON', 'PH_IP_SUN'
);

INSERT INTO ike_config_algorithm (
  ike_cfg, prio, alg
) VALUES (
  1, 1, 1
);

INSERT INTO ike_config_algorithm (
  ike_cfg, prio, alg
) VALUES (
  1, 2, 2
);

INSERT INTO peer_configs (
  name, ike_cfg, local_id, remote_id, mobike, dpd_delay
) VALUES (
  'net-net', 1, 4, 5, 0, 30
);

INSERT INTO child_configs (
  name, updown, start_action, dpd_action
) VALUES (
  'net-1', 'ipsec _updown iptables', 2, 2
);

INSERT INTO child_configs (
  name, updown, start_action, dpd_action
) VALUES (
  'net-2', 'ipsec _updown iptables', 2, 2
);

INSERT INTO child_configs (
  name, updown, start_action, dpd_action
) VALUES (
  'net-3', 'ipsec _updown iptables', 2, 2
);

INSERT INTO peer_config_child_config (
  peer_cfg, child_cfg
) VALUES (
  1, 1
);

INSERT INTO peer_config_child_config (
  peer_cfg, child_cfg
) VALUES (
  1, 2
);

INSERT INTO peer_config_child_config (
  peer_cfg, child_cfg
) VALUES (
  1, 3
);

INSERT INTO child_config_algorithm (
  child_cfg, prio, alg
) VALUES (
  1, 1, 3
);

INSERT INTO child_config_algorithm (
  child_cfg, prio, alg
) VALUES (
  2, 1, 4
);

INSERT INTO child_config_algorithm (
  child_cfg, prio, alg
) VALUES (
  3, 1, 3
);

INSERT INTO child_config_algorithm (
  child_cfg, prio, alg
) VALUES (
  3, 2, 4
);

INSERT INTO traffic_selectors (
  type, start_addr, end_addr
) VALUES (
  7, X'0a010000', X'0a01000f'
);

INSERT INTO traffic_selectors (
  type, start_addr, end_addr
) VALUES (
  7, X'0a010010', X'0a01001f'
);

INSERT INTO traffic_selectors (
  type, start_addr, end_addr
) VALUES (
  7, X'0a010200', X'0a0103ff'
);

INSERT INTO traffic_selectors (
  type, start_addr, end_addr
) VALUES (
  7, X'0a020000', X'0a0201ff'
);

INSERT INTO traffic_selectors (
  type, start_addr, end_addr
) VALUES (
  7, X'0a020200', X'0a0203ff'
);

INSERT INTO child_config_traffic_selector (
  child_cfg, traffic_selector, kind
) VALUES (
  1, 1, 0
);

INSERT INTO child_config_traffic_selector (
	child_cfg, traffic_selector, kind
) VALUES (
  1, 4, 1
);

INSERT INTO child_config_traffic_selector (
  child_cfg, traffic_selector, kind
) VALUES (
  2, 2, 0
);

INSERT INTO child_config_traffic_selector (
	child_cfg, traffic_selector, kind
) VALUES (
  2, 4, 1
);

INSERT INTO child_config_traffic_selector (
  child_cfg, traffic_selector, kind
) VALUES (
  3, 3, 0
);

INSERT INTO child_config_traffic_selector (
	child_cfg, traffic_selector, kind
) VALUES (
  3, 5, 1
);
