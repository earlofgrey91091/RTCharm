#include <time.h>
#include <math.h>
#include "common.h"
#include "pup.h"
#include "pup_stl.h"
#include "ray.h"



/*class Shape {
public:

	coord3D pos;
	float size;

	
}*/




/*
class Shape  : public PUP::able {
public:
	float r,b,g;
    virtual float hit(float ox, float oy, float *n) {CkPrintf("000");return 0;};

	Shape()
	{
		srand(time(NULL));

		r = rnd(1.0f);
        	g = rnd(1.0f);
        	b = rnd(1.0f);	
		r = 2.0;
		g = 3.0;
		b = 9.0;	
	};

	PUPable_decl(Shape);
    Shape(CkMigrateMessage *m) : PUP::able(m) {}
	virtual void printShape(void) {CkPrintf("l");};
	virtual void pup(PUP::er &p)
	{ 
        PUP::able::pup(p); 
        p | r;
        p | g;
        p | b;
	};

};


class Sphere : public Shape {

public:
	coord3D origin;
    float radius;


	Sphere()
	{
		//srand(time(NULL));
		radius = rnd(100.0f) + 20;
		
		origin.x = rnd(1000.0f) - 500;
		origin.y = rnd(1000.0f) - 500;
		origin.z = rnd(1000.0f) - 500;
		
		radius = 10.1;
		
		origin.x = 136.0;
		origin.y = 137.0;
		origin.z = 138.0;

		//r = rnd(1.0f);
		//g = rnd(1.0f);
		//b = rnd(1.0f);
	};
	void printShape(void) {
		CkPrintf("\n Sphere Origin = (%f, %f, %f) radius = %f rgb = (%f, %f, %f)", origin.x, origin.y, origin.z, radius, r, g, b);
	}

	float hit(float ox, float oy, float *n) 
        {
		float dx = ox - origin.x; // distance on x-axis
	    	float dy = oy - origin.y; // distance on y-axis
		
	    	//if (dx*dx + dy*dy > radius*radius), ray will not hit sphere
	    	if (dx*dx + dy*dy < radius*radius) {
	       		float dz = sqrtf( radius*radius - dx*dx - dy*dy );
	       		*n = dz / sqrtf( radius * radius );
			CkPrintf("\n Sphere was hit by ray from [%f][%f]", ox, oy);
	       		return dz + origin.z;
	    	}
		return NEGINF;
	}

	PUPable_decl(Sphere);
    	Sphere(CkMigrateMessage *m) : Shape(m) {}
	void pup(PUP::er &p) 
        {
	    Shape::pup(p);
            p | origin;
	    p | radius;
	}

};
*/
/*

class Triangle : public Shape {
private:

	coord3D randomize(void) {
                struct coord3D temp;
                srand(time(NULL));
                temp.x = rnd(1000.0f) - 500;
                temp.y = rnd(1000.0f) - 500;
                temp.y = rnd(1000.0f) - 500;
                return temp;
        }

public:

	coord3D vert1;
	coord3D vert2;
	coord3D vert3;
	Triangle(){
		srand(time(NULL));
		vert1 = randomize();
		vert2 = randomize();
		vert3 = randomize();
		r = rnd(1.0f);
                g = rnd(1.0f);
                b = rnd(1.0f);
	}
	float hit(float ox, float oy, float *n);

	PUPable_decl(Triangle);
    Sphere(CkMigrateMessage *m) : Shape(m) {}
	void pup(PUP::er &p) {
	    Shape::pup(p);
	    p | vert1;
	    p | vert2;
	    p | vert3;
	}
	

};*/ 
