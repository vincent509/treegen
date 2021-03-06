#include "meshdata.h"
#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include "glwidget.h"
#include "GL/glut.h"
const double PI = 3.1415926;
meshData::meshData(int vertexSize, int indiceSize)
{

listSize = 0;
vertexList = new Vert[vertexSize];
index = new unsigned short[indiceSize];

}
void meshData::addVertexData(Vert vertList[], int size){
    for(int i = 0;i<size;i++){
        vertexList[i+listSize] = *(vertList+i);
    }
    listSize += size;
}
float* meshData::getData(){
    float* data;
    data = new float[listSize*3];

    // allocation
   // data = new float[listSize][3];
    for(int i = 0; i < listSize*3; i++)
        data[i] = 0.0;


    for(int i = 0; i<listSize;i++){
        data[i*3] = vertexList[i].x;
        data[i*3+1] = vertexList[i].y;
        data[i*3+2] = vertexList[i].z;
    }
    return data;
}
void meshData::move(float x, float y, float z){
    for(int i = 0; i < listSize; i++){
        float newX = vertexList[i].x + x;
        float newY = vertexList[i].y + y;
        float newZ = vertexList[i].z + z;
        vertexList[i].Set(Vert(newX, newY, newZ));

    }
}
void meshData::draw(){
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vertexId);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceId);

    glDrawElements(GL_TRIANGLES,n_indices, GL_UNSIGNED_SHORT,NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void meshData::addVboData(){
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnableClientState(GL_VERTEX_ARRAY);

    //n_vertex = mesh->listSize;
   // n_indice = mesh->n_indices;


    glBindBuffer(GL_ARRAY_BUFFER, vertexId);
    glBufferData(GL_ARRAY_BUFFER, 3 * (listSize) * sizeof(GLfloat), vertexList, GL_DYNAMIC_DRAW_ARB);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  indiceId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (n_indices) * sizeof(GLushort), index, GL_DYNAMIC_DRAW_ARB);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}
void meshData::initMesh(){

    glGenBuffers(1, &vertexId);
    glGenBuffers(1, &indiceId);
    addVboData();


}
void meshData::increaseListSize(int v_count, int i_count){
    Vert *tempV = vertexList;
   // unsigned short *tempI = index;

    vertexList = new Vert[listSize+v_count];
   // index = new unsigned short[n_indices+i_count];
    copyVertexData(tempV);
   // copyIndexData(tempI);
    free(tempV);

  // tempV = NULL;
  //  tempI = NULL;
}

void meshData::copyVertexData(Vert* newList){
    for(int i = 0; i < listSize; i++){
        vertexList[i] = newList[i];
    }
}
void meshData::copyIndexData(unsigned short* newList){
    for(int i = 0; i < n_indices; i++){
        index[i] = newList[i];
    }
}

void meshData::matrixMult(float vector[3][1], float rotMatrix[3][3], float result[3][1]){
    result[0][0] = 0;
    result[1][0] = 0;
    result[2][0] = 0;

    int row = 3;
    for(int i = 0; i < row;i++){
        for(int j = 0; j < row; j++){
            result[i][0] += vector[j][0]*rotMatrix[i][j];
        }
    }
}

void meshData::moveMesh(float x, float y, float z){
    for(int i  = 0; i < listSize;i++){
        vertexList[i].x += x;
        vertexList[i].y += y;
        vertexList[i].z += z;
    }
}

void meshData::getXRotationMatrix(float angle, float matrix[4][4]){
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = cos(angle);
    matrix[1][2] = sin(angle);
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = sin(angle);
    matrix[2][2] = -cos(angle);
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

}

void meshData::getYRotationMatrix(float angle, float matrix[4][4]){
    matrix[0][0] = cos(angle);
    matrix[0][1] = 0;
    matrix[0][2] = sin(angle);
    matrix[0][3] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[2][0] = -sin(angle);
    matrix[2][1] = 0;
    matrix[2][2] = cos(angle);
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

}

void meshData::getZRotationMatrix(float angle, float matrix[4][4]){

    matrix[0][0] = cos(angle);
    matrix[0][1] = -sin(angle);
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = sin(angle);
    matrix[1][1] = cos(angle);
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
}

void meshData::getRotationMatrix(Vert *v, float angle, float matrix[3][3]){
    float x = v->x;
    float y = v->y;
    float z = v->z;
    matrix[0][0] = cos(angle)+(x*x)*(1-cos(angle));
    matrix[0][1] = y*x*(1-cos(angle))-z*sin(angle);
    matrix[0][2] = x*z*(1-cos(angle))+y*sin(angle);

    matrix[1][0] = y*x*(1-cos(angle))+z*sin(angle);
    matrix[1][1] = cos(angle)+y*y+(1-cos(angle));
    matrix[1][2] = y*z*(1-cos(angle))-x*sin(angle);

    matrix[2][0] = z*x*(1-cos(angle)-y*sin(angle));
    matrix[2][1] = z*y*(1-cos(angle))+x*sin(angle);
    matrix[2][2] = cos(angle)+z*z*(1-cos(angle));


    /*
    matrix[0][0] = cos(angle1)*cos(angle2);
    matrix[0][1] = cos(angle3)*sin(angle2) + sin(angle3)*sin(angle1)*cos(angle2);
    matrix[0][2] = sin(angle3)*sin(angle2)-(cos(angle3)*sin(angle1)*cos(angle2));
    matrix[0][3] = 0;

    matrix[1][0] = -cos(angle1)*sin(angle2);
    matrix[1][1] = cos(angle3)*cos(angle2)-(sin(angle3)*sin(angle1)*sin(angle2));
    matrix[1][2] = sin(angle3)*cos(angle2)+cos(angle3)*sin(angle1)*sin(angle2);
    matrix[1][3] = 0;

    matrix[2][0] = sin(angle1);
    matrix[2][1] = -sin(angle3)*cos(angle1);
    matrix[2][2] = cos(angle3)*cos(angle1);
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;*/
}

float meshData::getScalarAngle(Vert *v1,Vert *v2){
    float x,y,z;
    float ls = v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
    float d1 = sqrt((v1->x*v1->x) + (v1->y*v1->y) + (v1->z*v1->z));
    float d2 = sqrt((v2->x*v2->x) + (v2->y*v2->y) + (v2->z*v2->z));
    return acos(ls/(d1*d2));
}
void meshData::rotateVert(Vert *v,Vert *u,float angle){
    float rotMat[3][3];
    float vector[3][1];
    float result[3][1];

    getRotationMatrix(u,angle,rotMat);

    vector[0][0] = v->x;
    vector[1][0] = v->y;
    vector[2][0] = v->z;
    matrixMult(vector,rotMat,result);
    v->x = result[0][0];
    v->y = result[1][0];
    v->z = result[2][0];

}
meshData::~meshData(){
    delete vertexList;
    delete index;
}
