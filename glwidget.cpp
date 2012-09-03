#include "GL/glew.h"
#include "glwidget.h"
#include "GL/glut.h"
#include <QMouseEvent>
#include <iostream>
#include <math.h>
#include "vert.h"
//#include "cylinder.h"
#include "tree.h"
 #include <QTime>


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

m_mouseClick = false;
this->setMouseTracking(true);

timer = new QTime();
timer->start();
}

int tX,tY,tZ,lX,lY;
double mX = 0;
double mY = 0;
double mZ = 0;
float distance = 5, camAngleX = 1, camAngleY = 1;
Tree *t = new Tree(12);
//cylinder *cyl2 = new cylinder(20);

int frameCount = 0;
void GLWidget::mousePressEvent ( QMouseEvent * e )
{
    // store click position

        // set the flag meaning "click begin"
    if(e->button() == Qt::LeftButton){
        m_mouseClick = true;
        tX = e->pos().x();
        tY = (e->pos().y()*-1)+height();
    }
}
void GLWidget::wheelEvent(QWheelEvent *e)
{
    distance -= (float)e->delta()/500;
    update();
    //updateCamera();
}

void GLWidget::updateCamera(){
    int xPos = (int)m_lastPoint.x();
    int yPos = ((int)m_lastPoint.y()*-1)+height();

    camAngleX = (float)(tX - xPos   + lX)/(width()/200);
    camAngleY = (float)(tY - yPos   + lY)/(height()/200);

    mX = 1 * -sinf(camAngleX*(M_PI/180)) * cosf((camAngleY)*(M_PI/180));
    mY = 1 * -sinf((camAngleY)*(M_PI/180));
    mZ = -1 * cosf((camAngleX)*(M_PI/180)) * cosf((camAngleY)*(M_PI/180));

}

void GLWidget::mouseMoveEvent ( QMouseEvent * e )
{
    if (m_mouseClick)
    {
        m_lastPoint = e->pos();
        updateCamera();
        update();
    }

}
void GLWidget::mouseReleaseEvent( QMouseEvent * e ){
    lX -= tX - e->pos().x();
    lY += tY - ((e->pos().y()*-1)+height());
 /*   std::cout << "tY  is: " << tY << "\n";
    std::cout << "pos  is: " << (double)(e->pos().y()*-1)+height() << "\n";
    std::cout << "lY  is: " << lY << "\n";*/
    m_mouseClick = false;
}

void GLWidget::initializeGL(){

    this->setMouseTracking(true);
    glewInit();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90,1,   0.1,   100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //connect(QAbstractEventDispatcher::instance(), SIGNAL(aboutToBlock()),
            //this, SLOT(onAboutToBlock()));

    t->init();
}




/*void GLWidget::addVboData(meshData *mesh){
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnableClientState(GL_VERTEX_ARRAY);
    //Vert *data;  //mesh->getData();

    n_vertex = mesh->listSize;
    n_indice = mesh->n_indices;
    for(int i = 0; i < (n_vertex); i++){
      //  std::cout <<i  << " data value is : "<< (mesh->vertexList+i)->x << "\n";
    }

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexId);
    glBufferData(GL_ARRAY_BUFFER, 3 * (n_vertex) * sizeof(GLfloat), mesh->vertexList, GL_DYNAMIC_DRAW_ARB);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indiceId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (n_indice) * sizeof(GLushort), mesh->index, GL_DYNAMIC_DRAW_ARB);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}*/

void GLWidget::paintGL(){
    frameCount++;
    float fps;
    if(frameCount == 10){
        if(timer->elapsed() != 0)
            fps = timer->restart();
             std::cout << "FPS: " << fps << "\n";
           // emit setFps(timer->elapsed());

        fflush(0);
        frameCount = 0;

    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   /* temp_mX += mX;
    temp_mY += mY;
    temp_mZ += mZ;
    double magnitude = sqrt(temp_mX*temp_mX+temp_mY*temp_mY+temp_mZ*temp_mZ);
    temp_mX = temp_mX/magnitude;
    temp_mY = temp_mY/magnitude;
    temp_mZ = temp_mZ/magnitude;*/
    gluLookAt((mX)*distance,(mY)*distance,(mZ)*distance,0,0,0,0,1,0);


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4f,0.4f,0.8f);
    t->draw();
    glFlush();

}

void GLWidget::resizeGL(int w, int h){

}
void GLWidget::extrude(){
  //  addVboData();

  //  cyl1->mergeCylinder(cyl2);
    t->extrude();
    //addVboData(cyl1);
   // delete cyl1;
    //delete cyl2;
    //cyl2->move(5,6,6);
   // addVboData(cyl2);
    updateGL();

}



