//Ray header file
#ifndef RAY_H
#define RAY_H
#include "common.h"
#include <math.h>
#include "vecmath.h"

class ray 
{
    public:
        
        vec3d start, dir;
     
        ray()
        {
            start = vec3d();
            dir = vec3d();
        }

        ray(float x, float y, float z)
        {
            start = vec3d(x, y, x);
            dir = vec3d();
        }

        ray(float cx, float cy, float cz, float vx, float vy, float vz)
        {
            start = vec3d(cx, cy, cx);
            dir = vec3d(vx, vy, vz);
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

        vec3d loc, color;

        lightSrc()
        {
            color = vec3d();
            loc = vec3d();
        }
     
        lightSrc(float r, float g, float b)
        {
            color = vec3d(r, g, b);
            loc = vec3d();
        }

        lightSrc(float r, float g, float b, float x, float y, float z)
        {
            color = vec3d(r, g, b);
            loc = vec3d(x, y, z);
        }
        

        void print()
        {
            CkPrintf("location(x, y, z) = (%f, %f, %f)\n", loc.x, loc.y, loc.z);
            CkPrintf("red = %f, green = %f, blue = %f \n", color.x, color.y, color.z);
        }

        void pup(PUP::er &p)
        {
            p | color;
            p | loc;
        }
};

class Shape
{
    public:
       
        vec3d loc;
        float size;
        vec3d v0, v1, v2, N, color;
        float r;
        int type;

        Shape()
        {
           size = 1;
           type = SPHERE;
           r = 0.0;
           color = vec3d();
       }
        
        //SPHERE
        Shape(float s, float x, float y, float z, float reflection, 
                float r, float g, float b)
        {
            size = s;
            type = SPHERE;
            loc = vec3d(x,y,z);
            r = reflection;
            color = vec3d(r, g, b);
            v1 = vec3d();
            v2 = vec3d();
            v0 = vec3d();
            N = vec3d();
        }
        
        //TRIANGLE
        Shape(float x0, float y0, float z0, float x1, float y1, float z1, 
                float x2, float y2, float z2, float reflection, 
                float r, float g, float b)
        {
            type = TRIANGLE;
            loc = vec3d((x0 + x1 + x2)/3, (y0 + y1 + y2)/3, (z0 + z1 + z2)/3);
            
            v1 = vec3d(x1, y1, z1);
            v1 -= loc;
            v2 = vec3d(x2, y2, z2);
            v2-= loc;
            v0 = vec3d(x0, y0, z0);
            v0 -= loc;
            N = cross(v1 - v0, v2 - v0);
            
            N.norm();
            r = reflection;
            color = vec3d(r, g, b);
            size = 0;
        }

        void print()
        {
            CkPrintf("location(x,y,z) = (%f, %f, %f)\n", loc.x, loc.y, loc.z);
            CkPrintf("size = %f \n", size);
            CkPrintf("type = %d \n", type);
            CkPrintf("color = (%f,%f,%f)\n", color.x, color.y, color.z);
        }

        void pup(PUP::er &p)
        {
            p | size;
            p | type;
            p | loc;
            p | r;
            p | color;
            p | v0;
            p | v1;
            p | v2;
            p | N;
        }
};

#endif //RAY_H
