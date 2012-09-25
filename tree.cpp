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
    branchProb = treeLevel*2 - n_branches-5;
    n_branches;


   // int randTemp = random % invertedChance;
   // randTemp++;
    for(int i = 0; i < branchProb;i++){
        random = rand() % trunk->n_edges;
        Vert *v1,*v2,*v3,*v4;
        v1 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel,random)];
        v2 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel +1 ,random)];
        v3 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel,random+1)];
        v4 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel +1 ,random+1)];
        branch(v1,v2,v3,v4);
        n_branches++;
        branchProb--;
        std::cout << " branching";
        fflush(0);
    }
    scale = pow(0.99, treeLevel);
    trunk->extrude(scale+(1-scale)/2);
    treeLevel++;
    Tree *t;
    for(int i = 0; i < branches.size(); i++){
        t = branches[i];
        t->extrude();

    }
}
void Tree::branch(Vert *v1, Vert *v2, Vert *v3,Vert *v4){
    Tree *b = new Tree(10);
    branches.push_back(b);
    Vert *v11 = new Vert(0,0,0);
    Vert *v22 = new Vert(0,0,1);
    Vert *v33 = new Vert(0,1,0);
    Vert *v = new Vert();
    v->x = 0;
    v->y = 1;
    v->z = 0;
    b->trunk->scaleSegment(0,0.3);
    b->trunk->scaleSegment(b->trunk->n_edges,0.3);

    //Vert *angles = cylinder::getRotationAngle(v);
    float sAngle = meshData::getScalarAngle(v,cylinder::getRotationAxis(v1,v2,v3));
    v = cylinder::getRotationAxis(v1,v2,v3);
    rotateBranch(b->trunk,v,sAngle);

    //rotateBranch(b->trunk,angles->x,angles->y,angles->z);
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


void Tree::rotateBranch(cylinder *c,Vert *v, float angle){
    float rotMat[3][3];
    float vector[3][1];
    float result[3][1];
    float rad;
    rad = (PI*angle)/180;


    cylinder *cyl = c;

    meshData::getRotationMatrix(v,angle,rotMat);
    for(int i = 0;i < cyl->listSize;i++){
        vector[0][0] = cyl->vertexList[i].x;
        vector[1][0] = cyl->vertexList[i].y;
        vector[2][0] = cyl->vertexList[i].z;
        meshData::matrixMult(vector,rotMat,result);
        if(i >= cyl->listSize/2)
        {
        cyl->vertexList[i].x = result[0][0];
        cyl->vertexList[i].y = result[1][0];
        cyl->vertexList[i].z = result[2][0];
        }else{
            cyl->vertexList[i].x = result[0][0];
            cyl->vertexList[i].y = result[1][0];
            cyl->vertexList[i].z = result[2][0];
        }


    }
/*

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

    }*/
    cyl->addVboData();
}

void Tree::init(){
    trunk->initMesh();
}
