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
        vector<Shape> myShapes;
        vector<lightSrc> myLights;
        double *tmpBuffer;
        int x, y, w, h;
        int iteration;

    public:
        PixelChare_SDAG_CODE;    
        PixelChare(int width, int height); 
        PixelChare(CkMigrateMessage *m);
        ~PixelChare(); 
        void doWork();
        void runStep(vector<Shape> shapes, vector<lightSrc> lights);
        int shoot(ray viewRay, float *n);
        void draw(int index, ray theRay, int hitIndex);
        
        bool hit(int index, ray theRay, float *n);
        bool sphereHit(int index, ray theRay, float *n);
        //rgb* draw();
        void liveVizFunc(liveVizRequestMsg *m); 
};

#endif //PIXELCHARE_H 
