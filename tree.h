#ifndef TREE_H
#define TREE_H
#include "cylinder.h"

class Tree
{
public:
    Tree(int nEdges);
    int treeLevel;
    cylinder *trunk;
    void draw();
    void extrude();
    void init();
    float branchChance;
    int random;
    int n_branches;


   // cylinder branches[];
};

#endif // TREE_H
