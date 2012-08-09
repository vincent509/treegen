#include "meshdata.h"
#ifndef CYLINDER_H
#define CYLINDER_H


class cylinder : public meshData
{
public:
    cylinder(int size);
    int n_edges;
    int n_levels;
    //int n_indices;
    int getIndexAtLevel(int index, int level);
    void extrude();
    void copyVertArray(Vert* source, Vert* Dest,int size);
    void copyIndexArray( unsigned short* source, unsigned short* dest,int size);
    void deleteLevel();
    void connectEdge(int v1, int v2, int v3, int v4);
    void mergeCylinder(cylinder *c1);
   // ~cylinder();
   // void createCylinder();
};


#endif // CYLINDER_H
