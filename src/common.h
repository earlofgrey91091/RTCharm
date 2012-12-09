#ifndef COMMON_H
#define COMMON_H

#define ITERATIONS 100
#define SHAPES 2
#define loc(x,y, width)  (x + (y*width))
#define rnd(x) (x*rand() / RAND_MAX)
#define BOX_DIM 1000
#define INF 999999
#define NEGINF -999999
#define SPHERE 0
#define TRIANGLE 1
#define PAUSE_TIME 5.0
#define DEBUG_CODE false
#define PI 3.14159265
#define LB_TIME 5
#define ROT_TIME 1
#define ROT_RAD 0.034906585 //2*PI/180
#define LIMIT 512 //boundry size of the viewable space
#define GAMMA true
#define ANTI_ALIASING true
#define EXPOSURE true
#endif //COMMON_H
