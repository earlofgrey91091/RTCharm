#ifndef COMMON_H
#define COMMON_H

#define ITERATIONS 50
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
#define ANTI_ALIASING false
#define EXPOSURE false
#define SHAPE_DISP 3
#define MOVE_SHAPE false
#define COS_ENOUGH 0.70710678118
#endif //COMMON_H
