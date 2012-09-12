#ifndef MESHDATA_H
#define MESHDATA_H
#include "vert.h"
#include <vector>
#include <math.h>


class meshData
{

public:
    meshData(int vertexSize, int indiceSize);
    int listSize;
    int n_indices;
    unsigned int indiceId;
    unsigned int vertexId;
    Vert *vertexList;
    unsigned short *index;
    void addVertexData(Vert vertList[], int size);
    float* getData();
    void move(float x, float y, float z);
    void draw();
    void increaseListSize(int v_count, int i_count);
    void copyVertexData(Vert* newList);
    void copyIndexData(unsigned short* newList);
    void addVboData();
    void initMesh();
    static void getXRotationMatrix(float angle, float matrix[4][4]);
    static void getYRotationMatrix(float angle, float matrix[4][4]);
    static void getZRotationMatrix(float angle, float matrix[4][4]);
    static void getRotationMatrix(Vert *v,float angle, float matrix[3][3]);
    static void matrixMult(float vector[3][1], float rotMatrix[3][3], float result[3][1]);
    void moveMesh(float x, float y, float z);


    ~meshData();
};


#endif // MESHDATA_H
