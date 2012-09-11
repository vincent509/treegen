#include "cylinder.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define PI 3.14159265

cylinder::cylinder(int edgeSize): meshData(edgeSize*1000, edgeSize*1000)
{
     n_indices = 0;
     n_edges = edgeSize;
     n_levels = 0;
     cylinderHeightPos = 0;

    float revStep = 360/edgeSize;
    for(int i = 0; i < edgeSize; i++){

        float x, z;
        x = cos(PI*(i*revStep)/180);
        z = sin(PI*(i*revStep)/180);
        vertexList[i].Set(Vert(x, cylinderHeightPos, z));
    }
    for(int i = 0; i < edgeSize; i++){

        float x, z;
        x = cos(PI*(i*revStep)/180);
        z = sin(PI*(i*revStep)/180);
        vertexList[i+edgeSize].Set(Vert(x, cylinderHeightPos+1, z));
    }
    listSize += edgeSize*2;
    int i;
    for( i = 0; i < edgeSize-1; i++){
        connectEdge(i, i+1, getIndexAtLevel(1, i), getIndexAtLevel(1, i+1));
    }
   // i++;
    connectEdge(i, 0,  getIndexAtLevel(1, i), getIndexAtLevel(1, 0));
    n_levels += 1;
    cylinderHeightPos +=2;

}
void cylinder::connectEdge(int v1, int v2, int v3, int v4){
    index[n_indices] = v1;
    index[n_indices+1] = v3;
    index[n_indices+2] = v2;
    index[n_indices+3] = v2;
    index[n_indices+4] = v3;
    index[n_indices+5] = v4;
    n_indices += 6;

}

int cylinder::getIndexAtLevel(int level, int index){
    return (n_edges*level)+index;
}

/*void cylinder::extrude(){
    cylinder *e_cylinder = new cylinder(n_edges);
    e_cylinder->move(0,cylinderHeightPos,0);
    increaseListSize(e_cylinder->listSize, e_cylinder->n_indices);
     adjustSize(e_cylinder);
    for(int i = 0; i < e_cylinder->listSize; i++){
        vertexList[listSize+i] = e_cylinder->vertexList[i];
    }
    connectCap(n_levels, n_levels);
    for(int i = 0; i < e_cylinder->n_indices; i++){
        index[n_indices+i] = (e_cylinder->index[i])+listSize;
    }
    n_indices += e_cylinder->n_indices;



    listSize += e_cylinder->listSize;
    n_levels += 2;
    cylinderHeightPos += 2;
    delete e_cylinder;

}*/


void cylinder::extrude(float scale){
    //cylinder *e_cylinder = new cylinder(n_edges);
   // e_cylinder->move(0,cylinderHeightPos,0);
    increaseListSize(n_edges, n_edges*6);

    for(int i = 0; i < n_edges; i++){
        vertexList[listSize+i] = vertexList[listSize+i-n_edges];
    }
    listSize += n_edges;

    scaleSegment(listSize-n_edges, scale);

    for(int i = 0; i < n_edges; i++){
        vertexList[listSize-n_edges+i].y += 1;
    }

    connectCap(n_levels,n_levels);
    n_levels += 1;
    cylinderHeightPos += 1;
    addVboData();
}


void cylinder::connectCap(int start, int end){
    int i;
    int startPos = getIndexAtLevel(start,0);
    for(i = startPos; i < startPos+n_edges-1; i++){
        connectEdge(i, i+1, i+(n_edges), i+1+n_edges);
    }
    connectEdge(i, startPos,  i+n_edges, startPos+n_edges);
}


void cylinder::scaleSegment(int start, float scaleValue){

    Vert v;
    for(int i  = start; i < start + n_edges; i++){
        vertexList[i].x *= scaleValue;
        vertexList[i].z *= scaleValue;
        //c->vertexList[i].Vert.z = 5.0;
    }


}
Vert* cylinder::getRotationAngle(Vert *v){
    Vert *res = new Vert();
    Vert *t1 = new Vert(1,0,0);
    Vert *t2 = new Vert(0,1,0);
    Vert *t3 = new Vert(0,0,1);

    float t21,t22,t23;


    t21 = v->x*t1->x + v->y*t1->y + v->z*t1->z;
    t22 = v->x*t2->x + v->y*t2->y + v->z*t2->z;
    t23 = v->x*t3->x + v->y*t3->y + v->z*t3->z;

    float xang = acos(t21)*(180/PI);
    float yang = acos(t22)*(180/PI);
    float zang = acos(t23)*(180/PI);


    res->x = xang;
    res->y = yang;
    res->z = zang;

    return res;
}

Vert* cylinder::getNormalVector(Vert *v1, Vert *v2, Vert *v3){
    Vert *temp1 = new Vert();
    Vert *temp2 = new Vert();
    Vert *res = new Vert();

    temp1->x = (v2->x - v1->x);
    temp1->y = (v2->y - v1->y);
    temp1->z = (v2->z - v1->z);

    temp2->x = (v3->x - v1->x);
    temp2->y = (v3->y - v1->y);
    temp2->z = (v3->z - v1->z);


    res->x = temp1->y*temp2->z - temp1->z*temp2->y;
    res->y = temp1->z*temp2->x - temp1->x*temp2->z;
    res->z = temp1->x*temp2->y - temp1->y*temp2->x;

    /*float dist = sqrt(res->x*res->x + res->y*res->y + res->z*res->z);
    res->x = res->x/dist;
    res->y = res->y/dist;
    res->z = res->z/dist;*/
   // dist = sqrt(res->x*res->x + res->y*res->y + res->z*res->z);
    return res;
}

cylinder::~cylinder(){

}


