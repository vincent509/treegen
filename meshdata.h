#ifndef MESHDATA_H
#define MESHDATA_H
#include "vert.h"
#include <vector>



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
    ~meshData();
};


#endif // MESHDATA_H
