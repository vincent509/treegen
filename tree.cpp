#include "tree.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

Tree::Tree(int nEdges)
{
    trunk = new cylinder(nEdges);
    treeLevel = 1;
    branchChance = 0;
    random;
    n_branches = 1;
    //branches = new cylinder[10];
}

void Tree::draw(){
    trunk->draw();
}
void Tree::extrude(){
    float scale;
    bool inv;
    srand(5);
    branchChance = (pow(2.72,treeLevel)/100)/n_branches;
    random = rand();
    int invertedChance;
    if(branchChance != 0)
        if(branchChance > 0.5){
            inv = true;
            branchChance = 1-branchChance;
        }
        invertedChance = 1/branchChance;
    int randTemp = random % invertedChance;
    randTemp++;
    if(random == 1 || (inv == true && random != 1)){
        std::cout << "branching ";
        fflush(0);
        branchChance *= 0.5;
        n_branches++;
    }
    scale = pow(0.99, treeLevel);
    trunk->extrude(scale+(1-scale)/2);
    treeLevel++;
}

void Tree::init(){
    trunk->initMesh();
}
