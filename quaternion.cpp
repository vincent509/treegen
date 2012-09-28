#include "quaternion.h"

Quaternion::Quaternion()
{
}
Quaternion* Quaternion::QuatFromAxisAngle(Vert *axis, float angleInRadians)
{
     Quaternion *result = new Quaternion();
     float angle = angleInRadians / 2.0f;
     float sinAngle = sin(angle);
     Vert *n = Vert::normalize(axis);


     result->x = n->x * sinAngle;
     result->y = n->y * sinAngle;
     result->z = n->z * sinAngle;
     result->w = cos(angle);
     return result;
}

Quaternion* Quaternion::quatMult(Quaternion *q1, Quaternion *q2){
    Quaternion *res = new Quaternion();
    float x1,x2,y1,y2,z1,z2,w1,w2;
    w1 = q1->w;
    w2 = q2->w;
    x1 = q1->x;
    x2 = q2->x;
    y1 = q1->y;
    y2 = q2->y;
    z1 = q1->z;
    z2 = q2->z;

    res->w = (w1*w2) - (x1*x2) - (y1*y2) - (z1*z2);
    res->x = (w1*x2) + (x1*w2) + (y1*z2) - (z1*y2);
    res->y = (w1*y2) - (x1*z2) + (y1*w2) + (z1*x2);
    res->z = (w1*z2) + (x1*y2) - (y1*x2) + (z1*w2);

    return res;
}

Quaternion* Quaternion::normalize(Quaternion *v){
    Quaternion *res = new Quaternion();
    float dist = sqrt(v->x*v->x + v->y*v->y + v->z*v->z +v->w*v->w);
    res->x = v->x/dist;
    res->y = v->y/dist;
    res->z = v->z/dist;
    res->w = v->w/dist;

    return res;
}

