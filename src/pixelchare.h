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
        class rgb
        {
            public: 
            float r, g, b;
            rgb(){};
            void pup(PUP::er &p)
            {
                p|r;
                p|g;
                p|b;
            };
            ~rgb(){};
        };

        typedef struct { byte r, g, b; } rgb_byte;
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
        void startStep(vector<Shape> shapes, vector<lightSrc> lights);
        void runStep(vector<Shape> shapes, vector<lightSrc> lights);
        int shoot(ray viewRay, float &dist);
        void draw(int index, ray theRay, int hitIndex, float dist, float &coef, int &level);
        
        bool hit(int index, ray theRay, float &n);
        bool sphereHit(int index, ray theRay, float &n);
        void liveVizFunc(liveVizRequestMsg *m); 
        void pup(PUP::er &p);
        void ResumeFromSync();
};

#endif //PIXELCHARE_H 
