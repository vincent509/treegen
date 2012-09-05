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
   /* trunk->vertexList[0].x = 1;
    trunk->vertexList[0].y = 0;
    trunk->vertexList[0].z = 1;

    trunk->vertexList[1].x = 1;
    trunk->vertexList[1].y = 0;
    trunk->vertexList[1].z = 1;

    trunk->vertexList[2].x = 1;
    trunk->vertexList[2].y = 0;
    trunk->vertexList[2].z = 1;*/

    //branches = new cylinder[10];
}

void Tree::getXRotationMatrix(float angle, float matrix[4][4]){
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = cos(angle);
    matrix[1][2] = sin(angle);
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = sin(angle);
    matrix[2][2] = -cos(angle);
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

}

void Tree::getYRotationMatrix(float angle, float matrix[4][4]){
    matrix[0][0] = cos(angle);
    matrix[0][1] = 0;
    matrix[0][2] = sin(angle);
    matrix[0][3] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[2][0] = -sin(angle);
    matrix[2][1] = 0;
    matrix[2][2] = cos(angle);
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;

}

void Tree::getZRotationMatrix(float angle, float matrix[4][4]){

    matrix[0][0] = cos(angle);
    matrix[0][1] = -sin(angle);
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = sin(angle);
    matrix[1][1] = cos(angle);
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
}
void Tree::matrixMult(float vector[4][1], float rotMatrix[4][4], float result[4][1]){
    int row = 4;
    for(int i = 0; i < row;i++){
        for(int j = 0; j < row; j++){
            result[i][0] += vector[j][0]*rotMatrix[i][j];
        }
    }
}

void Tree::draw(){
    trunk->draw();
}
void Tree::extrude(){

    rotateBranch(trunk);



    /*
    float scale;
    bool inv;
    srand(5);
    branchChance = (pow(2.72,treeLevel)/50);
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
    treeLevel++;*/
}
void Tree::branch(){


        //float x =

        //branch.vertexList[i].x

    //branch->initMesh();
   // branch->addVboData();
}
void Tree::rotateBranch(cylinder *c){
    float xRotMat[4][4];
    float vector[4][1];
    float result[4][1];

    getZRotationMatrix(0.1,xRotMat);
    cylinder *cyl = c;

    for(int i = 0;i < cyl->listSize;i++){
        for(int i = 0; i < 4; i++){

             result[i][0] = 0;
        }
        vector[0][0] = cyl->vertexList[i].x;
        vector[1][0] = cyl->vertexList[i].y;
        vector[2][0] = cyl->vertexList[i].z;
        vector[3][0] = 1;
        matrixMult(vector,xRotMat,result);
        cyl->vertexList[i].x = result[0][0];
        cyl->vertexList[i].y = result[1][0];
        cyl->vertexList[i].z = result[2][0];

    }
    cyl->addVboData();
}

void Tree::init(){
    trunk->initMesh();
}
