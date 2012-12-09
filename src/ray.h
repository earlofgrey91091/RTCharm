//Ray header file
#ifndef RAY_H
#define RAY_H

class  coord3D
{
    public:
        float x;
        float y;
        float z;

        coord3D()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
        coord3D(float x, float y, float z) 
        {
            this->x = x;
            this->y = y;
            this->z = z;    
        }
        void pup(PUP::er &p)
        {
            p | x;
            p | y;
            p | z;
        }
    
};

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
        void pup(PUP::er &p)
        {
            p | x;
            p | y;
            p | z;
        }
};

inline coord3D operator + (const coord3D &p, const vec3D &v)
{
    coord3D p2;
    p2.x = p.x + v.x;
    p2.y = p.y + v.y;
    p2.z = p.z + v.z;
    return p2;
}

inline coord3D operator - (const coord3D &p, const vec3D &v)
{
    coord3D p2;
    p2.x = p.x - v.x;
    p2.y = p.y - v.y;
    p2.z = p.z - v.z;
    return p2;
}

inline vec3D operator + (const vec3D &v1, const vec3D &v2)
{
    vec3D v(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    return v;
}

inline vec3D operator - (const coord3D &p1, const coord3D &p2)
{
    vec3D v( p1.x - p2.x, p1.y - p2.y, p1.z - p2.z );
    return v;
}

inline vec3D operator * (float c, const vec3D &v)
{
    vec3D v2( v.x * c, v.y * c, v.z * c );
    return v2;
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
        
        coord3D start;
        vec3D dir;
     
        ray()
        {
        //do nothing defult constructor for start and dir will run    
        }

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

        coord3D loc;
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
       
        coord3D loc;
        float size;
        float reflection;
        float red, green, blue;
        int type;

        Shape()
        {
           this->size = 1;
           this->type = 0;
           this->reflection = 0.0;
           this->red = 0;
           this->green = 0;
           this->blue = 0;
        }

        Shape(float size)
        {
            this->size = size;
            this->type = 0;
            this->reflection = 0.0;
            this->red = 0;
            this->green = 0;
            this->blue = 0;
        }

        Shape(float size, int type)
        {
            this->size = size;
            this->type = type;
            this->reflection = 0.0;
            this->red = 0;
            this->green = 0;
            this->blue = 0;
        }

        Shape(float size, int type, float x, float y, float z)
        {
            this->size = size;
            this->type = type;
            this->loc.x = x;
            this->loc.y = y;
            this->loc.z = z;
            this->reflection = 0.0;
            this->red = 0;
            this->green = 0;
            this->blue = 0;
        }

        Shape(float size, int type, float x, float y, float z, float reflection, float r, float g, float b)
        {
            this->size = size;
            this->type = type;
            this->loc.x = x;
            this->loc.y = y;
            this->loc.z = z;
            this->reflection = reflection;
            this->red = r;
            this->green = g;
            this->blue = b;

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
        }
    
};

#endif //RAY_H
