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


    void branch();
    void rotateBranch(cylinder *c,float xAngle, float yAngle, float zAngle);


   // cylinder branches[];
};

#endif // TREE_H
