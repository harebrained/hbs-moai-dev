#include <QtGui/QMouseEvent>
#include "moaiwidget.h"
#include "stdio.h"
#include <aku/AKU.h>
#include <aku/AKU-luaext.h>
#include <zlcore/zl_replace.h>
#include <lua-headers/moai_lua.h>

namespace QTInputDeviceID {
    enum {
        DEVICE,
        TOTAL
    };
}

namespace QTInputDeviceSensorID {
    enum {
        KEYBOARD,
        POINTER,
        MOUSE_LEFT,
        MOUSE_MIDDLE,
        MOUSE_RIGHT,
        TOTAL
    };
}

MoaiWidget::MoaiWidget(QWidget *parent) :
    QGLWidget(parent)
{
    mInitialized = false;
    mWidth = 0;
    mHeight = 0;
}

MoaiWidget::~MoaiWidget()
{
     AKUFinalize();
}

void MoaiWidget::initializeGL() {

    refreshContext();

}

void MoaiWidget::resizeGL(int w, int h) {

    if(mInitialized)
    {
        AKUSetScreenSize ( w, h);
        AKUSetViewSize(w,h);

        if(mDocuments)
        {
            setActiveDirectory(mActiveDirectory);
            mDocuments = false;
        }

        if(mScripts)
        {
            runScript(mActiveFile);
            mScripts = false;
        }
    }
    mWidth = w;
    mHeight = h;
}

void MoaiWidget::paintGL() {

    if(mInitialized)
    {
           AKURender ();
    }
    else{
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,0,0);
        glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(100,500);
        glVertex2f(500,100);
        glEnd();
        //printf("Render. Man.");
    }
}

void MoaiWidget::mousePressEvent(QMouseEvent *event) {
    printf("%d, %d\n", event->x(), event->y());
    switch( event->button())
    {
    case Qt::LeftButton:
        AKUEnqueueButtonEvent(QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_LEFT, true);
        event->accept();
        break;
    case Qt::MidButton:
        AKUEnqueueButtonEvent(QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_MIDDLE, true);
        event->accept();
        break;
    case Qt::RightButton:
        AKUEnqueueButtonEvent(QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_RIGHT, true);
        event->accept();
        break;
    }
}
void MoaiWidget::mouseReleaseEvent(QMouseEvent *event){

    switch( event->button())
    {
    case Qt::LeftButton:
        AKUEnqueueButtonEvent(QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_LEFT, false);
        event->accept();
        break;
    case Qt::MidButton:
        AKUEnqueueButtonEvent(QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_MIDDLE, false);
        event->accept();
        break;
    case Qt::RightButton:
        AKUEnqueueButtonEvent(QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_RIGHT, false);
        event->accept();
        break;
    }
}

void MoaiWidget::mouseMoveEvent(QMouseEvent *event) {
    //printf("%d, %d\n", event->x(), event->y());
    AKUEnqueuePointerEvent ( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::POINTER, event->x(), event->y() );
    event->accept();
}

void MoaiWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

void MoaiWidget::refreshContext(){

    printf("Starting load\n");
    AKUContextID context = AKUGetContext ();

    if ( context ) {
        AKUDeleteContext ( context );
    }
    AKUCreateContext ();


    AKUExtLoadLuacrypto ();
    AKUExtLoadLuacurl ();
    AKUExtLoadLuafilesystem ();
    AKUExtLoadLuasocket ();
    AKUExtLoadLuasql ();

    AKUSetInputConfigurationName ( "AKUQT" );

    AKUReserveInputDevices			( QTInputDeviceID::TOTAL );
    AKUSetInputDevice				( QTInputDeviceID::DEVICE, "device" );

    AKUReserveInputDeviceSensors	( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::TOTAL );
    AKUSetInputDeviceKeyboard		( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::KEYBOARD,		"keyboard" );
    AKUSetInputDevicePointer		( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::POINTER,		"pointer" );
    AKUSetInputDeviceButton			( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_LEFT,	"mouseLeft" );
    AKUSetInputDeviceButton			( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_MIDDLE,	"mouseMiddle" );
    AKUSetInputDeviceButton			( QTInputDeviceID::DEVICE, QTInputDeviceSensorID::MOUSE_RIGHT,	"mouseRight" );

    AKUDetectGfxContext ();
    if(mWidth > 0 )
    {
        printf("this could be: %d, %d", mWidth, mHeight);
        AKUSetScreenSize ( mWidth, mHeight);
        AKUSetViewSize(mWidth,mHeight);
    }

    AKURunBytecode ( moai_lua, moai_lua_SIZE );
    mTimer = new QTimer(this);
    mTimer->setInterval( 30 );
    connect(mTimer, SIGNAL(timeout()), this, SLOT(onUpdate()) );
    mTimer->start();
    mInitialized = true;
    printf("Intiialized\n");
}


void MoaiWidget::setActiveDirectory(QString directory){
    mActiveDirectory = directory;
    if(mInitialized)
    {
        const char *path = directory.toAscii().data();
        printf("Setting active directory: %s \n", path);
        AKUSetWorkingDirectory ( path );
    }
    else
       mDocuments = true;
}

void MoaiWidget::runScript(QString script){
    mActiveFile = script;
    if(mInitialized)
    {
        const char *path = script.toAscii().data();
        printf("Running script: %s \n", path);
        AKURunScript ( path );
    }
    else
        mScripts = true;
}

void MoaiWidget::closeWindow(){
    AKUFinalize();
}

void MoaiWidget::onUpdate(){
    AKUUpdate ();
    updateGL();
}
