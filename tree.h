#ifndef TREE_H
#define TREE_H
#include "cylinder.h"
#include <vector>

class Tree{

public:
    Tree(int nEdges);
    int treeLevel;
    cylinder *trunk;
    std::vector<Tree*> branches;
    void draw();
    void extrude();
    void init();
    float branchChance;
    int random;
    int n_branches;
    Vert *upVector;
    int branchLevel;


    void branch(Tree *t, Vert *v1, Vert *v2,Vert *v3, Vert *v4);
    void rotateBranch(cylinder *c,Vert *v,float angle);
    Vert* getCenterPoint(Vert *v1, Vert *v2, Vert *v3, Vert *v4);
    void rotateVert(Vert *v,float xAngle, float yAngle, float zAngle);
   float getScalarAngle(Vert *v1,Vert *v2);


   // cylinder branches[];
};

#endif // TREE_H
