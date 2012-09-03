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


   // cylinder branches[];
};

#endif // TREE_H
