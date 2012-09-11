#include "tree.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
const double PI = 3.1415926;
Tree::Tree(int nEdges)
{
    trunk = new cylinder(nEdges);
    treeLevel = -2;
    branchChance = 0;
    random;
    n_branches = 0;
    branches = std::vector<Tree*>();
}




void Tree::draw(){
    trunk->draw();
    for(int i = 0; i < branches.size();i++){
        Tree *c = branches[i];
        c->draw();
    }
}
void Tree::extrude(){
    float scale;
    srand(time(NULL));
    static float branchProb;
    branchProb = treeLevel*2 - n_branches;
    n_branches;
    random = rand() % trunk->n_edges;

   // int randTemp = random % invertedChance;
   // randTemp++;
    if(branchProb > 1){
        Vert *v1,*v2,*v3,*v4;
        v1 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel% trunk->n_edges,treeLevel)];
        v2 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel% trunk->n_edges +1 ,treeLevel)];
        v3 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel% trunk->n_edges,treeLevel+1)];
        v4 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel% trunk->n_edges +1 ,treeLevel+1)];
        branch(v1,v2,v3,v4);
        n_branches++;
        branchProb--;
        std::cout << " branching";
        fflush(0);
    }
    scale = pow(0.99, treeLevel);
    trunk->extrude(scale+(1-scale)/2);
    treeLevel++;
}
void Tree::branch(Vert *v1, Vert *v2, Vert *v3,Vert *v4){
    Tree *b = new Tree(10);
    branches.push_back(b);
    Vert *v11 = new Vert(0,0,0);
    Vert *v22 = new Vert(1,0,-1);
    Vert *v33 = new Vert(1,1,-1);
    Vert *v = cylinder::getNormalVector(v1,v2,v3);

    Vert *angles = cylinder::getRotationAngle(v);
   //
    b->trunk->scaleSegment(0,0.3);
    b->trunk->scaleSegment(b->trunk->n_edges,0.3);
    rotateBranch(b->trunk,angles->x,angles->y,angles->z);
    Vert *m = getCenterPoint(v1,v2,v3,v4);

    b->trunk->moveMesh(m->x,m->y,m->z);


    b->trunk->initMesh();
    b->trunk->addVboData();
}

Vert* Tree::getCenterPoint(Vert *v1, Vert *v2, Vert *v3, Vert *v4){

    float x,y,z;
    x = (v1->x+v2->x+v3->x+v4->x)/4;
    y = (v1->y+v2->y+v3->y+v4->y)/4;
    z = (v1->z+v2->z+v3->z+v4->z)/4;
    return new Vert(x,y,z);
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
