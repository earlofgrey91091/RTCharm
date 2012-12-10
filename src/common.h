#ifndef COMMON_H
#define COMMON_H

#define ITERATIONS 200
#define DEFAULT_CHAREDIM 8
#define DEFAULT_SPHERES 40
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
#define LB_TIME 10
#define ROT_TIME 1
#define ROT_RAD 0.034906585 //2*PI/180
#define LIMIT 1024 //boundry size of the viewable space
#define GAMMA true
#define ANTI_ALIASING false
#define EXPOSURE false
#define SHAPE_DISP 3
#define MOVE_SHAPE true
#define COS_ENOUGH 0.70710678118
#define EXPOSURE_CONST -1.00f
#define SAMPLE_RATIO 0.25f
#endif //COMMON_H
