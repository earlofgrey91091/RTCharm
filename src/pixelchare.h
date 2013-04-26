#ifndef PIXELCHARE_H
#define PIXELCHARE_H
#include <pup_stl.h>
#include "common.h"
#include "main.decl.h"
//#include "shape.h"
//#include "ShapeMsg.h"

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
        void doWork();
        void clearPixel(int index);
        void exposePixel(int index);
        float gamma(float);
        bool triHit(int index, ray theRay, float &n);

    public:
        PixelChare_SDAG_CODE;    
        PixelChare(int width, int height); 
        PixelChare(CkMigrateMessage *m);
        ~PixelChare(); 
        

        void startStep(vector<Shape> shapes, vector<lightSrc> lights);
        void runStep(vector<Shape> shapes, vector<lightSrc> lights);
        
        void liveVizFunc(liveVizRequestMsg *m); 
        void pup(PUP::er &p);
        void ResumeFromSync();
};

#endif //PIXELCHARE_H 
