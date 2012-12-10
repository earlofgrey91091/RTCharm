//Ray header file
#ifndef RAY_H
#define RAY_H
#include "common.h"
#include <math.h>
class  vec3D 
{
    public:
        float x, y, z;

        vec3D()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
     
        vec3D(float i)
        {
            this->x = i;
            this->y = i;
            this->z = i;
        }
        vec3D(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        vec3D& operator += (const vec3D &v2)
        {
            this->x += v2.x;
            this->y += v2.y;
            this->z += v2.z;
            return *this;
        }
        vec3D& operator -= (const vec3D &v2)
        {
            this->x -= v2.x;
            this->y -= v2.y;
            this->z -= v2.z;
            return *this;
        }
        void pup(PUP::er &p)
        {
            p | x;
            p | y;
            p | z;
        }
};


inline vec3D operator + (const vec3D &v1, const vec3D &v2)
{
    vec3D v(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    return v;
}

inline vec3D operator + (const vec3D &v1, float val)
{
    vec3D v(v1.x + val, v1.y + val, v1.z + val );
    return v;
}

inline vec3D operator * (float c, const vec3D &v)
{
    vec3D v2( v.x * c, v.y * c, v.z * c );
    return v2;
}

//cross product
inline vec3D cross(const vec3D &v0, const vec3D &v1)
{
    vec3D v2(v0.y * v1.z - v0.z * v1.y, 
            v0.z * v1.x - v0.x * v1.z,  
            v0.x * v1.y - v0.y * v1.x);
    return v2;
}

//cross product
inline float mag(const vec3D &v)
{
    return sqrtf((pow(v.x, 2)  + pow(v.y, 2) + pow(v.z, 2)));
}

inline vec3D operator - (const vec3D &v1, const vec3D &v2)
{
    vec3D v( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    return v;
}

inline float operator * (const vec3D &v1, const vec3D &v2 ) 
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

class ray 
{
    public:
        
        vec3D start, dir;
     
        ray(){}

        ray(float x, float y, float z)
        {
            this->start.x = x;
            this->start.y = y;
            this->start.z = z;
        }

        ray(float cx, float cy, float cz, float vx, float vy, float vz)
        {
            this->start.x = cx;
            this->start.y = cy;
            this->start.z = cz;

            this->dir.x = vx;
            this->dir.y = vy;
            this->dir.z = vz;
        }

        void pup(PUP::er &p)
        {
            p | start;
            p | dir;
        }
    
};

class lightSrc 
{
    public:

        vec3D loc;
        float r, g, b;

        lightSrc()
        {
            this->r = 0;
            this->g = 0;
            this->b = 0;
        }
     
        lightSrc(float r, float g, float b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        lightSrc(float r, float g, float b, float x, float y, float z)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            
            this->loc.x = x;
            this->loc.y = y;
            this->loc.z = z;

        }
        

        void print()
        {
            CkPrintf("location(x, y, z) = (%f, %f, %f)\n", loc.x, loc.y, loc.z);
            CkPrintf("red = %f, green = %f, blue = %f \n", r, g, b);
        }

        void pup(PUP::er &p)
        {
            p | r;
            p | g;
            p | b;
            p | loc;
        }
    


};

class Shape
{
    public:
       
        vec3D loc;
        float size;
        vec3D v0;
        vec3D v1;
        vec3D v2;
        vec3D N;
        float reflection;
        float red, green, blue;
        int type;

        Shape()
        {
           this->size = 1;
           this->type = SPHERE;
           this->reflection = 0.0;
           this->red = 0;
           this->green = 0;
           this->blue = 0;
        }
        
        //SPHERE
        Shape(float size, float x, float y, float z, float reflection, float r, float g, float b)
        {
            this->size = size;
            this->type = SPHERE;
            this->loc.x = x;
            this->loc.y = y;
            this->loc.z = z;
            this->reflection = reflection;
            this->red = r;
            this->green = g;
            this->blue = b;
///
            this->v0.x = 0;
            this->v0.y = 0;
            this->v0.z = 0;
            this->v1.x = 0;
            this->v1.y = 0;
            this->v1.z = 0;
            this->v2.x = 0;
            this->v2.y = 0;
            this->v2.z = 0;
            this->N.x = 0;
            this->N.y = 0;
            this->N.z = 0;

        }
        
        //TRIANGLE
        Shape(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float reflection, float r, float g, float b)
        {
            this->type = TRIANGLE;
            this->loc.x = (x0 + x1 + x2)/3;
            this->loc.y = (y0 + y1 + y2)/3;
            this->loc.z = (z0 + z1 + z2)/3;
            this->v0.x = x0;
            this->v0.y = y0;
            this->v0.z = z0;
            this->v0 -=  this->loc;
            this->v1.x = x1;
            this->v1.y = y1;
            this->v1.z = z1;
            this->v0 -=  this->loc;
            this->v2.x = x2;
            this->v2.y = y2;
            this->v2.z = z2;
            this->N = cross(this->v1 - this->v0, this->v2 - this->v0);
            float tot = sqrtf(1/(pow(this->N.x, 2)  + pow(this->N.y, 2) + pow(this->N.z, 2)));
            this->N.x *= tot;
            this->N.y *= tot;
            this->N.z *= tot;
            this->reflection = reflection;
            this->red = r;
            this->green = g;
            this->blue = b;
///
            this->size = 0;
        }

        void print()
        {
            CkPrintf("location(x,y,z) = (%f, %f, %f)\n", loc.x, loc.y, loc.z);
            CkPrintf("size = %f \n", size);
            CkPrintf("type = %d \n", type);
            CkPrintf("color = (%f,%f,%f)\n", this->red, this->green, this->blue);
        }

        void pup(PUP::er &p)
        {
            p | size;
            p | type;
            p | loc;
            p | reflection;
            p | red;
            p | green;
            p | blue;
            /*p | v0;
            p | v1;
            p | v2;
            p | N;*/
        }
    
};

#endif //RAY_H
