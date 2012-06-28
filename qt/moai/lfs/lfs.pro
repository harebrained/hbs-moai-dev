TEMPLATE = lib
TARGET = lfs
DESTDIR = ../lib
CONFIG += staticlib release

DEFINES -= UNICODE

QMAKE_CFLAGS += -DAKU_STATIC -DCURL_STATICLIB
QMAKE_CFLAGS += -DHAVE_CONFIG_H -DUSE_SSL -DUSE_SSLEAY -DUSE_OPENSSL -DBUILDING_LIBCURL
QMAKE_CFLAGS += -DUSE_ARES -DCARES_STATICLIB -DCURL_STATICLIB -DCURL_DISABLE_LDAP

INCLUDEPATH += ../../..
INCLUDEPATH += ../../../src

INCLUDEPATH += ../../../3rdparty/lua-5.1.3/src
INCLUDEPATH += ../../../3rdparty/luacrypto-0.2.0/src
INCLUDEPATH += ../../../3rdparty/luafilesystem-1.5.0/src
INCLUDEPATH += ../../../3rdparty/luasql-2.2.0/src


SOURCES 	+= ../../../3rdparty/luafilesystem-1.5.0/src/lfs.c
