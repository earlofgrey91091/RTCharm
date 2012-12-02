#ifndef PIXELCHARE_H
#define PIXELCHARE_H
#include <pup_stl.h>
#include "common.h"
#include "main.decl.h"
//#include "shape.h"
//#include "ShapeMsg.h"

extern /*readonly*/ int size;

class PixelChare : public CBase_PixelChare 
{
    private:
    typedef struct { byte r, g, b; } rgb;
    vector<rgb> pixelArray;
    double *tmpBuffer;
    //Shape *shapes;
    vector<Shape> shapes;
    Sphere *spheres;
    int x, y, w, h;
    int iteration;

    public:
    PixelChare_SDAG_CODE;    
    PixelChare(int width, int height); 
    PixelChare(CkMigrateMessage *m);
    ~PixelChare(); 
    void doWork();
    void runStep(int size, Shape *s);
    void recvSphere(int size, Sphere *s);
    void liveVizDump(liveVizRequestMsg *m); 


};

#endif //PIXELCHARE_H 
