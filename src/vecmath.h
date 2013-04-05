#ifndef VECMATH_H
#define VECMATH_H
#include <math.h>
#include <stdio.h>

class vec3d 
{
    public:
        float x, y, z;

        vec3d()
        {
            x = 0;
            y = 0;
            z = 0;
        }
     
        vec3d(float i)
        {
            x = i;
            y = i;
            z = i;
        }
        vec3d(float px, float py, float pz)
        {
            x = px;
            y = py;
            z = pz;
        }
        
        vec3d& operator += (const vec3d &v2)
        {
            x += v2.x;
            y += v2.y;
            z += v2.z;
            return *this;
        }
        
        vec3d& operator -= (const vec3d &v2)
        {
            x -= v2.x;
            y -= v2.y;
            z -= v2.z;
            return *this;
        }
        
        vec3d& operator *= (float i)
        {
            x *= i;
            y *= i;
            z *= i;
            return *this;
        }
        
        //cross product
        vec3d& operator *= (const vec3d &v)
        {
            float tx = y * v.z - z * v.y;
            float ty = z * v.x - x * v.z;
            float tz = x * v.y - y * v.x;
            
            x = tx; y = ty; z = tz;
            return *this;
        }
        
        vec3d& operator /= (float i)
        {
            x /= i;
            y /= i;
            z /= i;
            return *this;
        }
        
        vec3d& operator = (const vec3d &v2)
        {
            if(this == &v2) return *this;
            
            x = v2.x;
            y = v2.y;
            z = v2.z;
            return *this;
        }
        
        bool operator == (const vec3d &v2)
        {
            if(this == &v2) return true;
            if((x == v2.x) && (y == v2.y) && (z == v2.z)) return true;
            return false;
        }
        
        float mag()
        {
            return sqrtf((pow(x, 2)  + pow(y, 2) + pow(z, 2)));
        }
        
        void norm()
        {
            float m = mag();
            x /= m;
            y /= m;
            z /= m;
        }
        
        void pup(PUP::er &p)
        {
            p | x;
            p | y;
            p | z;
        }
        
};
        
inline vec3d operator + (const vec3d &v1, const vec3d &v2)
{
    vec3d v(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    return v;
}

inline vec3d operator + (const vec3d &v1, float val)
{
    vec3d v(v1.x + val, v1.y + val, v1.z + val );
    return v;
}

inline vec3d operator * (float c, const vec3d &v)
{
    vec3d v2( v.x * c, v.y * c, v.z * c );
    return v2;
}

inline vec3d operator / (float c, const vec3d &v0)
{
    vec3d v(v0.x/c, v0.y/c, v0.z/c);
    return v;
}

//cross product
inline vec3d operator *(const vec3d &v0, const vec3d &v1)
{
    vec3d v2(v0.y * v1.z - v0.z * v1.y, 
            v0.z * v1.x - v0.x * v1.z,  
            v0.x * v1.y - v0.y * v1.x);
    return v2;
}

//cross product alternate call
inline vec3d cross(const vec3d &v0, const vec3d &v1)
{
    vec3d v2(v0.y * v1.z - v0.z * v1.y, 
            v0.z * v1.x - v0.x * v1.z,  
            v0.x * v1.y - v0.y * v1.x);
    return v2;
}

inline vec3d operator - (const vec3d &v1, const vec3d &v2)
{
    vec3d v( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    return v;
}

inline vec3d operator - (const vec3d &v1, float val)
{
    vec3d v(v1.x - val, v1.y - val, v1.z - val );
    return v;
}

//dot product
inline float dot(const vec3d &v1, const vec3d &v2 ) 
{
    return (float)((float)v1.x * v2.x + (float)v1.y * v2.y + (float)v1.z * v2.z);
}

// We want a featured Quaternion class for safe rotations
// is based off of wikipedia's description of quatern rotations
class quat3d 
{
    public:
        float w, x, y, z;
        
        quat3d() 
        {
            //empty default constructor
        }
        
        quat3d(float a, float b, float c, float d) 
        {
            w = a;
            x = b; 
            y = c; 
            z = d;
        }
        
        quat3d(float i) 
        {
            w = i;
            x = y = z = 0;
        }
        
        quat3d(vec3d v, float d) 
        {
            w = d; 
            x = v.x;
            y = v.y;
            z = v.z;
        }
        
        quat3d(vec3d v) 
        {
            w = 0.0; 
            x = v.x;
            y = v.y;
            z = v.z;
        }
        
        //seperate magnitude and magnitude squared function(s)
        //returns the magnitude squared
        float mag_2()
        {
            return w * w + x * x + y * y + z * z; //possibility for rollover
        }
        
        //returns the magnitude
        float mag()
        {
            return sqrt(this->mag_2());
        }
        
        void norm() 
        {
            float m = sqrt(w * w + x * x + y * y + z * z);//this->mag_2();
            w /= m;
            x /= m;
            y /= m;
            z /= m;
        }
        
        //returns the conjugate for rotations
        quat3d conjugate() const 
        {
            return quat3d(w, -x, -y, -z);
        }
        
        quat3d operator * (const quat3d &q) const 
        {
            return quat3d(  w * q.w - x * q.x - y * q.y - z * q.z,
                            w * q.x + x * q.w + y * q.z - z * q.y,
                            w * q.y + y * q.w + z * q.x - x * q.z,
                            w * q.z + z * q.w + x * q.y - y * q.x);
        }
        
        //rotates a vector by the multiplied Quaternion and returns the result
        //note that the result is not
        vec3d operator * (const vec3d &v) const 
        {
            quat3d rot(v); // make our vector into a quaternon
            quat3d res; // make our resultant quaternion
            res = rot * conjugate();
            res = *this * res;
            return vec3d(res.x, res.y, res.z);
        }
        void pup(PUP::er &p)
        {
            p | x;
            p | y;
            p | z;
            p | w;
        }
	};

#endif //VECMATH_H
