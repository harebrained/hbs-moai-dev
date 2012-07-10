TEMPLATE = lib
TARGET = crypto
DESTDIR = ../lib
CONFIG += staticlib release

DEFINES -= UNICODE

QMAKE_CFLAGS += -DDSO_WIN32 -DOPENSSL_SYSNAME_WIN32 -DWIN32_LEAN_AND_MEAN
QMAKE_CFLAGS += -DL_ENDIAN -DOPENSSL_NO_RC5 -DOPENSSL_NO_MD2 -DOPENSSL_NO_KRB5
QMAKE_CFLAGS += -DOPENSSL_NO_JPAKE -DOPENSSL_NO_STATIC_ENGINE
QMAKE_CFLAGS += -DMK1MF_BUILD -DMK1MF_PLATFORM_VC_WIN32

win32{
    QMAKE_CFLAGS += -DOPENSSL_NO_BF -DOPENSSL_NO_CAMELLIA -DOPENSSL_NO_CAST -DOPENSSL_NO_CMS  -DOPENSSL_NO_EC
    QMAKE_CFLAGS += -DOPENSSL_NO_ECDH -DOPENSSL_NO_ECDSA -DOPENSSL_NO_ENGINE -DOPENSSL_NO_ERR  -DOPENSSL_NO_GMP
    QMAKE_CFLAGS += -DOPENSSL_NO_IDEA -DOPENSSL_NO_MDC2 -DOPENSSL_NO_RFC3779 -DOPENSSL_NO_RIPEMD -DOPENSSL_NO_SEED
    QMAKE_CFLAGS += -DOPENSSL_NO_STORE -DOPENSSL_NO_WHIRLPOOL -DOPENSSL_NO_STATIC_ENGINE
}

INCLUDEPATH += ../../..
INCLUDEPATH += ../../../src
INCLUDEPATH += ../../../src/aku
INCLUDEPATH += ../../../src/config-default
INCLUDEPATH += ../../../src/moaicore
INCLUDEPATH += ../../../src/moaiext-untz
INCLUDEPATH += ../../../src/uslscore
INCLUDEPATH += ../../../src/zipfs
INCLUDEPATH += ../../../3rdparty
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D/Collision/Shapes
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D/Collision
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D/Common
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D/Dynamics
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D/Dynamics/Contacts
INCLUDEPATH += ../../../3rdparty/box2d-2.2.1/Box2D/Dynamics/Joints
INCLUDEPATH += ../../../3rdparty/c-ares-1.7.5
INCLUDEPATH += ../../../3rdparty/c-ares-1.7.5/include-apple
INCLUDEPATH += ../../../3rdparty/chipmunk-5.3.4/include
INCLUDEPATH += ../../../3rdparty/chipmunk-5.3.4/include/chipmunk
INCLUDEPATH += ../../../3rdparty/chipmunk-5.3.4/include/chipmunk/constraints
INCLUDEPATH += ../../../3rdparty/contrib
INCLUDEPATH += ../../../3rdparty/curl-7.19.7/include
INCLUDEPATH += ../../../3rdparty/expat-2.0.1/amiga
INCLUDEPATH += ../../../3rdparty/expat-2.0.1/lib
INCLUDEPATH += ../../../3rdparty/expat-2.0.1/xmlwf
INCLUDEPATH += ../../../3rdparty/freetype-2.4.4/include
INCLUDEPATH += ../../../3rdparty/freetype-2.4.4/include/freetype
INCLUDEPATH += ../../../3rdparty/freetype-2.4.4/include/freetype2
INCLUDEPATH += ../../../3rdparty/freetype-2.4.4/builds
INCLUDEPATH += ../../../3rdparty/freetype-2.4.4/src
INCLUDEPATH += ../../../3rdparty/freetype-2.4.4/config
INCLUDEPATH += ../../../3rdparty/jansson-2.1/src
INCLUDEPATH += ../../../3rdparty/jpeg-8c
INCLUDEPATH += ../../../3rdparty/libogg-1.2.2/include
INCLUDEPATH += ../../../3rdparty/libvorbis-1.3.2/include
INCLUDEPATH += ../../../3rdparty/libvorbis-1.3.2/lib
INCLUDEPATH += ../../../3rdparty/lpng140
INCLUDEPATH += ../../../3rdparty/lua-5.1.3/src
INCLUDEPATH += ../../../3rdparty/luacrypto-0.2.0/src
INCLUDEPATH += ../../../3rdparty/luacurl-1.2.1
INCLUDEPATH += ../../../3rdparty/luafilesystem-1.5.0/src
INCLUDEPATH += ../../../3rdparty/luasocket-2.0.2/src
INCLUDEPATH += ../../../3rdparty/luasql-2.2.0/src
INCLUDEPATH += ../../../3rdparty/openssl-1.0.0d/include
INCLUDEPATH += ../../../3rdparty/openssl-1.0.0d/include-win32
INCLUDEPATH += ../../../3rdparty/ooid-0.99
INCLUDEPATH += ../../../3rdparty/sqlite-3.6.16
INCLUDEPATH += ../../../3rdparty/tinyxml
INCLUDEPATH += ../../../3rdparty/tlsf-2.0
INCLUDEPATH += ../../../3rdparty/untz/include
INCLUDEPATH += ../../../3rdparty/untz/src
INCLUDEPATH += ../../../3rdparty/zlib-1.2.3
INCLUDEPATH += ../../../3rdparty/glew-1.5.6/include

win32{
    HEADERS     += ../../../3rdparty/openssl-1.0.0d/include-win32/openssl/opensslconf.h
}


#Crypto A
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_bitstr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_bool.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_bytes.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_d2i_fp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_digest.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_dup.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_enum.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_gentm.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_i2d_fp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_int.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_mbstr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_object.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_octet.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_print.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_set.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_sign.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_strex.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_strnid.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_time.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_type.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_utctm.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_utf8.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/a_verify.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/ameth_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn1_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn1_gen.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn1_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn1_par.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn_mime.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn_moid.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/asn_pack.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/bio_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/bio_ndef.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/d2i_pr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/d2i_pu.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/evp_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/f_enum.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/f_int.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/f_string.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/i2d_pr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/i2d_pu.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/n_pkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/nsseq.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/p5_pbe.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/p5_pbev2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/p8_pkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_bitst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_crl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_pkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_req.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_spki.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_x509.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/t_x509a.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_dec.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_fre.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_new.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_typ.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/tasn_utl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_algor.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_attrib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_bignum.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_crl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_exten.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_info.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_long.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_name.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_nx509.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_pkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_pubkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_req.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_sig.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_spki.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_val.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_x509.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/asn1/x_x509a.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_api.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_def.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_mall.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_mod.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/conf/conf_sap.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/bio_b64.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/bio_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/bio_md.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/bio_ok.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/c_all.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/c_allc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/c_alld.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/digest.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_aes.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_bf.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_camellia.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_cast.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_des.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_des3.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_idea.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_null.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_old.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_rc2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_rc4.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_rc5.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_seed.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/e_xcbc_d.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/encode.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_acnf.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_pbe.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/evp_pkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_dss.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_dss1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_ecdsa.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_md2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_md4.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_md5.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_mdc2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_null.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_ripemd.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_sha.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_sha1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_sigver.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/m_wp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/names.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p5_crpt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p5_crpt2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_dec.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_open.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_seal.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_sign.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/p_verify.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/pmeth_fn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/pmeth_gn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/evp/pmeth_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/lhash/lh_stats.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/lhash/lhash.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_asn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_cl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_ext.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_ht.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_srv.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ocsp/ocsp_vfy.c

#Crypto B
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_add.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_asm.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_blind.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_const.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_ctx.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_depr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_div.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_exp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_exp2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_gcd.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_gf2m.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_kron.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_mod.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_mont.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_mpi.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_mul.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_nist.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_prime.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_print.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_rand.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_recp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_shift.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_sqr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_sqrt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bn/bn_word.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/hmac/hm_ameth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/hmac/hm_pmeth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/hmac/hmac.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_all.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_info.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_oth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_pk8.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_pkey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_seal.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_sign.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_x509.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pem_xaux.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pem/pvkfmt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_ameth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_depr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_gen.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_ossl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_pmeth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_sign.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dsa/dsa_vrf.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_ameth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_check.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_depr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_gen.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_pmeth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dh/dh_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/modes/cbc128.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/modes/cfb128.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/modes/ctr128.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/modes/cts128.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/modes/ofb128.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/bio_pk7.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_attr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_dgst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_doit.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_mime.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pk7_smime.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs7/pkcs7err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_add.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_asn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_attr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_crpt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_crt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_decr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_init.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_kiss.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_mutl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_npas.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_p8d.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_p8e.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/p12_utl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pkcs12/pk12err.c


#Crypto C
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_cbc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_cfb.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_core.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_ctr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_ecb.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_ige.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_misc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_ofb.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/aes/aes_wrap.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/b_dump.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/b_print.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/b_sock.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bf_buff.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bf_lbuf.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bf_nbio.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bf_null.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bio_cb.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bio_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bio_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_acpt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_bio.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_conn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_dgram.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_fd.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_file.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_log.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_mem.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_null.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/bio/bss_sock.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/buffer/buf_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/buffer/buffer.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/cbc_cksm.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/cbc_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/cfb64ede.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/cfb64enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/cfb_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/des_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/ecb3_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/ecb_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/enc_read.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/enc_writ.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/fcrypt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/fcrypt_b.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/ofb64ede.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/ofb64enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/ofb_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/pcbc_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/qud_cksm.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/rand_key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/read2pwd.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/rpc_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/set_key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/str2key.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/des/xcbc_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/err/err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/err/err_all.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/err/err_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/comp/c_rle.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/comp/c_zlib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/comp/comp_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/comp/comp_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/objects/o_names.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/objects/obj_dat.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/objects/obj_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/objects/obj_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/objects/obj_xref.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc2/rc2_cbc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc2/rc2_ecb.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc2/rc2_skey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc2/rc2cfb64.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc2/rc2ofb64.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc4/rc4_enc.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rc4/rc4_skey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/md5/md5_dgst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/md5/md5_one.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/sha/sha1_one.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/sha/sha1dgst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/sha/sha256.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/sha/sha512.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/sha/sha_dgst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/sha/sha_one.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/md4/md4_dgst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/md4/md4_one.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/pqueue/pqueue.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/cpt_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/cryptlib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/cversion.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ebcdic.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ex_data.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/mem.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/mem_clr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/mem_dbg.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/o_dir.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/o_str.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/o_time.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/uid.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/stack/stack.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ui/ui_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ui/ui_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ui/ui_openssl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ui/ui_util.c

#Crypto D
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/md_rand.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_egd.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_nw.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_os2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_unix.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/rand_win.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rand/randfile.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_ameth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_chk.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_depr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_eay.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_gen.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_none.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_null.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_oaep.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_pk1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_pmeth.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_pss.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_saos.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_sign.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_ssl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/rsa/rsa_x931.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_beos.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_dl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_dlfcn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_null.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_openssl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_vms.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/dso/dso_win32.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_asn1.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_conf.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_req_print.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_req_utils.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_rsp_print.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_rsp_sign.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_rsp_utils.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_rsp_verify.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/ts/ts_verify_ctx.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/txt_db/txt_db.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/by_dir.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/by_file.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_att.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_cmp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_d2.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_def.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_err.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_ext.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_lu.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_obj.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_r2x.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_req.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_set.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_trs.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_txt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_v3.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_vfy.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509_vpm.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509cset.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509name.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509rset.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509spki.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x509type.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509/x_all.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/pcy_cache.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/pcy_data.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/pcy_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/pcy_map.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/pcy_node.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/pcy_tree.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_addr.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_akey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_akeya.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_alt.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_asid.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_bcons.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_bitst.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_conf.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_cpols.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_crld.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_enum.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_extku.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_genn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_ia5.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_info.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_int.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_lib.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_ncons.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_ocsp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_pci.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_pcia.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_pcons.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_pku.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_pmaps.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_prn.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_purp.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_skey.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_sxnet.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3_utl.c
SOURCES += ../../../3rdparty/openssl-1.0.0d/crypto/x509v3/v3err.c
