//Ray header file
class  coord3D
{
    public:
        float x;
        float y;
        float z;

        coord3D(){}
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

struct vec3D 
{
    float x, y, z;

    vec3D& operator += (const vec3D &v2)
    {
        this->x += v2.x;
        this->y += v2.y;
        this->z += v2.z;
        return *this;
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
    vec3D v={v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return v;
}

inline vec3D operator - (const coord3D &p1, const coord3D &p2)
{
    vec3D v = { p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
    return v;
}

inline vec3D operator * (float c, const vec3D &v)
{
    vec3D v2 = {v.x *c, v.y * c, v.z * c };
    return v2;
}

inline vec3D operator - (const vec3D &v1, const vec3D &v2)
{
    vec3D v = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return v;
}

inline float operator * (const vec3D &v1, const vec3D &v2 ) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

struct ray 
{
    coord3D start;
    vec3D dir;
};

struct lightSrc 
{
    coord3D loc;
    float r, g, b;
};
