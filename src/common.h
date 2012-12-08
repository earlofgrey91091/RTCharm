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
#define PAUSE_TIME 5.0
#define DEBUG_CODE false
#define LB_TIME 5
#define ROT_CONSTANT 2
#define ROT_DEGREE 2

#endif //COMMON_H
