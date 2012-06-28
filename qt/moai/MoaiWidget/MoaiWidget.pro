CONFIG      += designer plugin release
CONFIG      += -TP
TARGET      = $$qtLibraryTarget(moaiwidgetplugin)
TEMPLATE    = lib

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
INCLUDEPATH += ../../../3rdparty/luacurl-1.2.1
INCLUDEPATH += ../../../3rdparty/luafilesystem-1.5.0/src
INCLUDEPATH += ../../../3rdparty/luasocket-2.0.2/src
INCLUDEPATH += ../../../3rdparty/luasql-2.2.0/src
INCLUDEPATH += ../../../3rdparty/openssl-1.0.0d/include-win32
INCLUDEPATH += ../../../3rdparty/ooid-0.99
INCLUDEPATH += ../../../3rdparty/sqlite-3.6.16
INCLUDEPATH += ../../../3rdparty/tinyxml
INCLUDEPATH += ../../../3rdparty/tlsf-2.0
INCLUDEPATH += ../../../3rdparty/untz/include
INCLUDEPATH += ../../../3rdparty/untz/src
INCLUDEPATH += ../../../3rdparty/zlib-1.2.3
INCLUDEPATH += ../../../3rdparty/glew-1.5.6/include

HEADERS     = moaiwidgetplugin.h
SOURCES     = moaiwidgetplugin.cpp
RESOURCES   = icons.qrc
QT += opengl
LIBS        += -L.
LIBS += -L../lib \
     -laku \
     -lbox2d \
     -lcares \
     -lchipmunk \
     -lcontrib \
     -lcrypto \
     -lcurl \
     -lexpat \
     -lfreetype \
     -lglew \
     -ljpg \
     -ljson \
     -llfs \
     -llua \
     -lmoaicore \
     -lmoaiext-luaext \
     -lmoaiext-untz \
     -logg \
     -lpng \
     -lsqlite \
     -lssl \
     -ltinyxml \
     -luslscore \
     -lvorbis \
     -lzipfs

win32{
    LIBS += -lpsapi \
            -liphlpapi \
            -ladvapi32 \
            -lws2_32 \
            -lshell32 \
            -lrpcrt4
}


target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(moaiwidget.pri)
