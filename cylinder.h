#ifndef CYLINDER_H
#define CYLINDER_H
#include "meshdata.h"

class cylinder : public meshData
{
public:
    cylinder(int size);
    int n_edges;
    int n_levels;
    float cylinderHeightPos;
    //int n_indices;
    int getIndexAtLevel(int level, int index);
    void extrude(float scale);
    void copyVertArray(Vert* source, Vert* Dest,int size);
    void copyIndexArray( unsigned short* source, unsigned short* dest,int size);
    void deleteLevel();
    void connectEdge(int v1, int v2, int v3, int v4);
    void mergeCylinder(cylinder *c1);
    void connectCap(int start, int end);
    void scaleSegment(int start, float scaleValue);
    ~cylinder();
   // void createCylinder();
};


#endif // CYLINDER_H
