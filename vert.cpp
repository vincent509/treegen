#include "vert.h"
#include <math.h>

Vert::Vert()
{
}
void Vert::Set(Vert v){
       x = v.x;
       y = v.y;
       z = v.z;
}

Vert* Vert::normalize(Vert *v){
    Vert *res = new Vert();
    float dist = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
    res->x = v->x/dist;
    res->y = v->y/dist;
    res->z = v->z/dist;


    return res;
}
