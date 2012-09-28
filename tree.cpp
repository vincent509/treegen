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
    upVector = new Vert(0,1,0);
    branchLevel = 0;
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
    branchProb = treeLevel*2 - n_branches-1;
    n_branches;


   // int randTemp = random % invertedChance;
   // randTemp++;
    for(int i = 0; i < branchProb;i++){
   // if(branches.size() == 0){
        random = rand() % trunk->n_edges;
        Vert *v1,*v2,*v3,*v4;
        v1 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel,random)];
        v2 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel +1 ,random)];
        v3 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel,random+1)];
        v4 = &trunk->vertexList[trunk->getIndexAtLevel(treeLevel +1 ,random+1)];
        branch(this,v1,v2,v3,v4);
        n_branches++;
        branchProb--;
      //  std::cout << " branching";
        fflush(0);
    }
    scale = pow(0.99, treeLevel);
    trunk->extrude(scale+(1-scale)/2);
    treeLevel++;
    Tree *t;
    if(branches.size() > 0){
        t = branches[0];
        t->extrude();

    }
}
void Tree::branch(Tree *t,Vert *v1, Vert *v2, Vert *v3,Vert *v4){
    Tree *b = new Tree(10);
    b->branchLevel = t->branchLevel+1;
    branches.push_back(b);
   // b->upVector = t->upVector;
 /*   Vert *v11 = new Vert(0,0,0);
    Vert *v22 = new Vert(0,0,1);
    Vert *v33 = new Vert(0,1,0);
    */
    b->trunk->scaleSegment(0,0.3);
    b->trunk->scaleSegment(b->trunk->n_edges,0.3);

    float sAngle = meshData::getScalarAngle(b->upVector,cylinder::getRotationAxis(v1,v2,v3));
    Vert *v = cylinder::getRotationAxis(v1,v2,v3);
    rotateBranch(b->trunk,v,sAngle);

    b->upVector = cylinder::getNormalVector(&b->trunk->vertexList[0],&b->trunk->vertexList[1],&b->trunk->vertexList[2]);
    if(branchLevel > 0){
        std::cout << "value";
    }
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
   // float rad;
   //rad = (PI*angle)/180;


    cylinder *cyl = c;

    meshData::getRotationMatrix(v,angle,rotMat);
    for(int i = 0;i < cyl->listSize;i++){
      /*  vector[0][0] = cyl->vertexList[i].x;
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
            */
        Vert u = cyl->vertexList[i];
        Vert *temp = quaternionRotation(v,angle,u);
        cyl->vertexList[i].x = temp->x;
        cyl->vertexList[i].y = temp->y;
        cyl->vertexList[i].z = temp->z;
        //}
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



Vert* Tree::quaternionRotation(Vert *v, float angle, Vert oldVector){
    Vert *res = new Vert();
    Quaternion *q = Quaternion::QuatFromAxisAngle(v,angle);
    q = Quaternion::normalize(q);
    Quaternion *p =  new Quaternion();
    p->x = oldVector.x;
    p->y = oldVector.y;
    p->z = oldVector.z;
    p->w = 0;
    //p = Quaternion::normalize(p);
    Quaternion *qInv = new Quaternion();
    qInv->x = -q->x;
    qInv->y = -q->y;
    qInv->z = -q->z;

    Quaternion *temp = new Quaternion();
    temp = Quaternion::quatMult(q,p);
   // temp = Quaternion::normalize(temp);
    //Quaternion *temp2 = Quaternion::quatMult(temp,qInv);

    res->x = temp->x;
    res->y = temp->y;
    res->z = temp->z;

    return res;

}

void Tree::init(){
    trunk->initMesh();
}
