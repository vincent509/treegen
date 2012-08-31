#include "GL/glew.h"
#include "glwidget.h"
#include "GL/glut.h"
#include <QMouseEvent>
#include <iostream>
#include <math.h>
#include "vert.h"
#include "cylinder.h"


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

m_mouseClick = false;
this->setMouseTracking(true);
}
int tX,tY,tZ,lX,lY;
double mX = 0;
double mY = 0;
double mZ = 0;
cylinder *cyl1 = new cylinder(20);
//cylinder *cyl2 = new cylinder(20);

void GLWidget::mousePressEvent ( QMouseEvent * e )
{
    // store click position

        // set the flag meaning "click begin"
        m_mouseClick = true;
        tX = e->pos().x();
        tY = (e->pos().y()*-1)+height();
}
void GLWidget::updateCamera(){
    int yPos = ((int)m_lastPoint.y()*-1)+height();
    int xPos = (int)m_lastPoint.x();

    mX = (float)(tX - xPos   + lX)/(width()/2);
    mY = (float)(tY - yPos   + lY)/(height()/2);
    double z2 = 1 - mX *mX - mY * mY;
    if(z2 > 0)
        mZ = (float)sqrt(z2);
    else
        mZ = 0;
 //   std::cout << "X  is: " << mX;
    fflush(0);
   // std::cout << "Y is: " << mY;
    fflush(0);
   // std::cout << "Z  is: " << mZ;
    fflush(0);
    double magnitude = sqrt(mX*mX+mY*mY+mZ*mZ);
    mX = mX/magnitude;
    mY = mY/magnitude;
    mZ = mZ/magnitude;
}

void GLWidget::mouseMoveEvent ( QMouseEvent * e )
{
    if (m_mouseClick)
    {
        m_lastPoint = e->pos();
        updateCamera();
        updateGL();
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

int n_vertex;
int n_indice;
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

    glGenBuffers(1, &cyl1->vertexId);
    glGenBuffers(1, &cyl1->indiceId);
    addVboData(cyl1);


}

void GLWidget::addVboData(meshData *mesh){
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
}

void GLWidget::paintGL(){

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   /* temp_mX += mX;
    temp_mY += mY;
    temp_mZ += mZ;
    double magnitude = sqrt(temp_mX*temp_mX+temp_mY*temp_mY+temp_mZ*temp_mZ);
    temp_mX = temp_mX/magnitude;
    temp_mY = temp_mY/magnitude;
    temp_mZ = temp_mZ/magnitude;*/
    gluLookAt((mX)*5,(mY)*5,(mZ)*5,0,0,0,0,1,0);


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4f,0.4f,0.8f);
    cyl1->draw();
    //cyl2->draw();

    glFlush();

}

void GLWidget::resizeGL(int w, int h){

}
void GLWidget::extrude(){
  //  addVboData();

  //  cyl1->mergeCylinder(cyl2);
    cyl1->extrude();
    addVboData(cyl1);
   // delete cyl1;
    //delete cyl2;
    //cyl2->move(5,6,6);
   // addVboData(cyl2);
    updateGL();

}



