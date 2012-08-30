#include "meshdata.h"
#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include "glwidget.h"
#include "GL/glut.h"

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

meshData::~meshData(){
    delete vertexList;
    delete index;
}
