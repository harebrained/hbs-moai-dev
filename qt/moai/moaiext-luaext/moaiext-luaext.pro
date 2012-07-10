TEMPLATE = lib
TARGET = moaiext-luaext
DESTDIR = ../lib
CONFIG += staticlib release

DEFINES -= UNICODE

QMAKE_CFLAGS += -DAKU_STATIC -DCURL_STATICLIB
QMAKE_CFLAGS += -DHAVE_CONFIG_H -DUSE_SSL -DUSE_SSLEAY -DUSE_OPENSSL -DBUILDING_LIBCURL
QMAKE_CFLAGS += -DUSE_ARES -DCARES_STATICLIB -DCURL_STATICLIB  -DCURL_DISABLE_LDAP

INCLUDEPATH += ../../..
INCLUDEPATH += ../../../src
INCLUDEPATH += ../../../src/aku
INCLUDEPATH += ../../../src/config-default
INCLUDEPATH += ../../../src/moaicore
INCLUDEPATH += ../../../src/moaiext-untz
INCLUDEPATH += ../../../src/uslscore
INCLUDEPATH += ../../../src/zlcore
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
    INCLUDEPATH     += ../../../3rdparty/luasocket-2.0.2/src
    HEADERS     += ../../../3rdparty/luasocket-2.0.2/src/select.h
    SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/wsocket.c
}

HEADERS         += ../../../3rdparty/luasocket-2.0.2/src/*.h

SOURCES 	+= ../../../3rdparty/luacrypto-0.2.0/src/*.c

SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/auxiliar.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/buffer.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/except.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/inet.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/io.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/select.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/luasocket.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/mime.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/options.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/tcp.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/timeout.c
SOURCES 	+= ../../../3rdparty/luasocket-2.0.2/src/udp.c

SOURCES         += ../../../3rdparty/luasocket-2.0.2-embed/fullluasocket.c
SOURCES         += ../../../3rdparty/luasocket-2.0.2-embed/luasocketscripts.c
SOURCES 	+= ../../../3rdparty/luacurl-1.2.1/luacurl.c
SOURCES 	+= ../../../3rdparty/luasql-2.2.0/src/luasql.c
SOURCES 	+= ../../../3rdparty/luasql-2.2.0/src/ls_sqlite3.c
