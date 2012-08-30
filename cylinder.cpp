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


void cylinder::extrude(){
    //cylinder *e_cylinder = new cylinder(n_edges);
   // e_cylinder->move(0,cylinderHeightPos,0);
    increaseListSize(n_edges, n_edges*6);

    for(int i = 0; i < n_edges; i++){
        vertexList[listSize+i] = vertexList[listSize+i-n_edges];
    }
    listSize += n_edges;
    scaleSegment(listSize-n_edges, 0.88);

    for(int i = 0; i < n_edges; i++){
        vertexList[listSize-n_edges+i].y += 1;
    }

    connectCap(n_levels,n_levels);



    n_levels += 1;
    cylinderHeightPos += 1;


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

cylinder::~cylinder(){

}


