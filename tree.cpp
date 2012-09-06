#include "tree.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
const double PI = 3.1415926;
Tree::Tree(int nEdges)
{
    trunk = new cylinder(nEdges);
    treeLevel = 1;
    branchChance = 0;
    random;
    n_branches = 1;
    branches = std::vector<cylinder*>();
}




void Tree::draw(){
    trunk->draw();
    for(int i = 0; i < branches.size();i++){
        cylinder *c = branches[i];
        c->draw();
    }
}
void Tree::extrude(){
    float scale;
    bool inv;
    srand(123123213);
    branchChance = 1;
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
        branch();
        fflush(0);
        branchChance *= 0.5;
        n_branches++;
    }
    scale = pow(0.99, treeLevel);
    trunk->extrude(scale+(1-scale)/2);
    treeLevel++;
}
void Tree::branch(){
    cylinder *b = new cylinder(10);
    branches.push_back(b);

    b->scaleSegment(0,0.3);
    b->scaleSegment(b->n_edges,0.3);
    rotateBranch(b,90,0,0);
    b->moveMesh(0,treeLevel,0);


    b->initMesh();
    b->addVboData();


        //float x =

        //branch.vertexList[i].x

    //branch->initMesh();
   // branch->addVboData();
}
void Tree::rotateBranch(cylinder *c,float xAngle, float yAngle, float zAngle){
    float rotMat[4][4];
    float vector[4][1];
    float result[4][1];
    float xRad,yRad,zRad;
    xRad = (PI*xAngle)/180;
    yRad = (PI*yAngle)/180;
    zRad = (PI*zAngle)/180;

    cylinder *cyl = c;
    meshData::getXRotationMatrix(xRad,rotMat);
    for(int i = 0;i < cyl->listSize;i++){
        vector[0][0] = cyl->vertexList[i].x;
        vector[1][0] = cyl->vertexList[i].y;
        vector[2][0] = cyl->vertexList[i].z;
        vector[3][0] = 1;
        meshData::matrixMult(vector,rotMat,result);
        cyl->vertexList[i].x = result[0][0];
        cyl->vertexList[i].y = result[1][0];
        cyl->vertexList[i].z = result[2][0];

    }
    meshData::getYRotationMatrix(yRad,rotMat);
    for(int i = 0;i < cyl->listSize;i++){
        vector[0][0] = cyl->vertexList[i].x;
        vector[1][0] = cyl->vertexList[i].y;
        vector[2][0] = cyl->vertexList[i].z;
        vector[3][0] = 1;
        meshData::matrixMult(vector,rotMat,result);
        cyl->vertexList[i].x = result[0][0];
        cyl->vertexList[i].y = result[1][0];
        cyl->vertexList[i].z = result[2][0];

    }
    meshData::getZRotationMatrix(zRad,rotMat);
    for(int i = 0;i < cyl->listSize;i++){
        vector[0][0] = cyl->vertexList[i].x;
        vector[1][0] = cyl->vertexList[i].y;
        vector[2][0] = cyl->vertexList[i].z;
        vector[3][0] = 1;
        meshData::matrixMult(vector,rotMat,result);
        cyl->vertexList[i].x = result[0][0];
        cyl->vertexList[i].y = result[1][0];
        cyl->vertexList[i].z = result[2][0];

    }
    cyl->addVboData();
}

void Tree::init(){
    trunk->initMesh();
}
