#ifndef TREE_H
#define TREE_H
#include "cylinder.h"
#include <vector>

class Tree{

public:
    Tree(int nEdges);
    int treeLevel;
    cylinder *trunk;
    std::vector<cylinder*> branches;
    void draw();
    void extrude();
    void init();
    float branchChance;
    int random;
    int n_branches;
    void getXRotationMatrix(float angle, float matrix[4][4]);
    void getYRotationMatrix(float angle, float matrix[4][4]);
    void getZRotationMatrix(float angle, float matrix[4][4]);
    void matrixMult(float vector[4][1], float rotMatrix[4][4], float result[4][1]);
    void branch();
    void rotateBranch(cylinder *c);


   // cylinder branches[];
};

#endif // TREE_H
