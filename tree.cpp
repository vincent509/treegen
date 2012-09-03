#include "tree.h"
#include <math.h>

Tree::Tree(int nEdges)
{
    trunk = new cylinder(nEdges);
    treeLevel = 1;
    //branches = new cylinder[10];
}

void Tree::draw(){
    trunk->draw();
}
void Tree::extrude(){
    float scale;
    scale = pow(0.99, treeLevel);
    trunk->extrude(scale+(1-scale)/2);
    treeLevel++;
}

void Tree::init(){
    trunk->initMesh();
}
