#include <time.h>
#include <math.h>
#define rnd(x) (x*rand() / RAND_MAX)
#define BOX_DIM 1000
class  xyz
{
public:
	float x;
	float y;
	float z;

	xyz(){}

	void pup(PUP::er &p){
	  p | x;
	  p | y;
	  p | z;
	}
	
};


class Shape {
public:
	Shape();
	float r,b,g;
	virtual float hit(float ox, float oy, float *n);
};

class Sphere : public Shape {

public:
	Sphere()
	{
		srand(time(NULL));
		radius = rnd(100.0f) + 20;

		origin.x = rnd(1000.0f) - 500;
		origin.y = rnd(1000.0f) - 500;
		origin.z = rnd(1000.0f) - 500;

		r = rnd(1.0f);
		g = rnd(1.0f);
		b = rnd(1.0f);
	};

	xyz origin; 
	float radius;
	float hit(float ox, float oy, float *n) {
		float dx = ox - origin.x; // distance on x-axis
        	float dy = oy - origin.y; // distance on y-axis
        	//if (dx*dx + dy*dy > radius*radius), ray will not hit sphere
        	if (dx*dx + dy*dy < radius*radius) {
           		float dz = sqrtf( radius*radius - dx*dx - dy*dy );
           		*n = dz / sqrtf( radius * radius );
           		return dz + origin.z;
        	}
             return -999999;
	}

	void pup(PUP::er &p) {
	  p | origin;
	  p | radius;
	  p | r;
	  p | g;
	  p | b;
	}

};

class Triangle : public Shape {
private:

	xyz randomize(void) {
                struct xyz temp;
                srand(time(NULL));
                temp.x = rnd(1000.0f) - 500;
                temp.y = rnd(1000.0f) - 500;
                temp.y = rnd(1000.0f) - 500;
                return temp;
        }

public:

	xyz vert1;
	xyz vert2;
	xyz vert3;
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

	void pup(PUP::er &p){
	  p | vert1;
	  p | vert2;
	  p | vert3;
	  p | r;
	  p | g;
	  p | b;
	}
	

};