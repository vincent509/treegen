#ifndef VERT_H
#define VERT_H

class Vert
{
    public:
    Vert();
        Vert(float _x,float _y, float _z): x(_x), y(_y), z(_z){}
        float x,y,z;
        void Set(Vert v);
    private:

};


#endif // VERT_H
