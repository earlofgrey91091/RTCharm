//Ray header file
#ifndef RAY_H
#define RAY_H
#include "common.h"
#include <math.h>
#include "vecmath.h"
#define EPISILON .0000000001

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

	void modv()
        {
	    //float mag = dir.mag();
            //dir = vec3d(dir.x/mag, dir.y/mag, dir.z/mag);
            dir.norm();    
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
       
        vec3d v0, v1, v2, N, c_Amb, c_Dif, c_Spk;
        float r;
        
        //TRIANGLE
        Shape(vec3d iv0, vec3d iv1, vec3d iv2, vec3d ambient, vec3d diffuse, 
                vec3d specular, float reflectivity)
        {
            v0 = iv0;
            v1 = iv1;
            v2 = iv2;
            c_Amb = ambient;
            c_Dif = diffuse;
            c_Spk = specular;
            r = reflectivity;
            
            N = cross(v1 - v0, v2 - v0);
            
            N.norm();
            r = reflectivity;
        }

        void print()
        {
	    //we took out loc variavle so this line does not work anymore
            //CkPrintf("location(x,y,z) = (%f, %f, %f)\n", loc.x, loc.y, loc.z);
            //CkPrintf("type = %d \n", type);
            //CkPrintf("color = (%f,%f,%f)\n", color.x, color.y, color.z);
        }
        
        vec3d getNormal()
        {
            vec3d tempN = cross(v1 - v0, v2 - v0);
            CkAssert(tempN == N);
            return N;
        }
        
        //
        bool SameSide(vec3d &ray, vec3d &vec0, vec3d &vec1, vec3d &vec2)
        {
            double cp1x = 0, cp1y = 0, cp1z = 0, cp2x = 0, cp2y = 0;
            vec3d n1 = cross(vec1- vec2, ray - vec2);
            vec3d n2 = cross(vec1- vec2, vec0 - vec2);
            
            if (dot(n1,n2) > -EPSILON)
                return true;
            else
                return false;
        }
        
        //
        bool PointInTriangle(vec3d ray)
        {
            if (SameSide(ray, this->v0, this->v1, this->v2) &&
                SameSide(ray, this->v1, this->v0, this->v2) &&
                SameSide(ray, this->v2, this->v0, this->v1))
                return true;
            else
                return false;
        }
        
        // scr is (screenx, screen y, 0)
        float GetInterSect(vec3d ray, vec3d scr)
        {
            vec3d v1 = this->v2 - ray;
            vec3d v2 = scr - ray;
            float dot1 = dot(this->N, this->v0);
            float dot2 = dot(this->N, this->v1);

            if (abs(dot2) < EPISILON) return -1; // division by 0 means parallel
            float u = dot1 / dot2;

            if(!PointInTriangle(ray + u*(ray-scr))) //am i in the triangle may be unnecessary
                return -1;

            return u; // u is the distance
        }
        
        

        void pup(PUP::er &p)
        {
            p | v0;
            p | v1;
            p | v2;
            p | N;
            p | c_Amb;
            p | c_Dif;
            p | c_Spk;
            p | r;
        }
};

#endif //RAY_H
