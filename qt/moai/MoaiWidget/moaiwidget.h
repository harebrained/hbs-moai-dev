#ifndef MOAIWIDGET_H
#define MOAIWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>

#if defined(MOAIWIDGETLIB)
#include "MoaiWidgetLib.h"
#endif

#if defined(MOAIWIDGETLIB)
    class MOAIWIDGET_EXPORT MoaiWidget : public QGLWidget
#else
    class MoaiWidget : public QGLWidget
#endif
{
    Q_OBJECT
    
public:
    MoaiWidget(QWidget *parent = 0);
    ~MoaiWidget();

public slots:
    void setActiveDirectory(QString directory);
    void runScript(QString script);
    void onUpdate();
    void closeWindow();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    bool mInitialized;
    bool mDocuments;
    bool mScripts;
    int mHeight;
    int mWidth;
    void refreshContext();
    QTimer *mTimer;
    QString mActiveDirectory;
    QString mActiveFile;



};

#endif
