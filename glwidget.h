#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
//#include "meshdata.h"
//#include "cylinder.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
signals:
    void mouseClickEvent();

public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    //meshData createTri();
   // meshData createPlane();
    GLfloat * getVertexData();
   // void addVboData(meshData *mesh);
    void updateCamera();
public slots:
    void extrude();
    void xRot(int value);
    void yRot(int value);
    void zRot(int value);

signals:
    void setFps(int newValue);


protected:
    // re-implement processing of mouse events
    void mousePressEvent ( QMouseEvent * e );
    void mouseMoveEvent( QMouseEvent * e );
    void mouseReleaseEvent( QMouseEvent * e );
    void wheelEvent(QWheelEvent *e);
    //void wheelEvent(QWheelEvent * e) {
private:
    // member variable to store click position
    QPoint m_lastPoint;
    // member variable - flag of click beginning
    bool m_mouseClick;
    QTime *timer;
};

#endif // GLWIDGET_H
