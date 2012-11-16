#include <pup_stl.h>
#include <liveViz.h>
#include "shape.h"
#include "pup_stl.h"
#include <stdio.h>
using namespace std;
#include "pixelchare.decl.h"
#include "pixelchare.h"
#include "main.decl.h"



#define ITERATIONS 1000
#define loc(x,y, width)  (x + (y*width))


extern /*readonly*/ CProxy_Main mainProxy;
extern /*readonly*/ int Total_iterations;
extern /*readonly*/ int chareDimension;

PixelChare::PixelChare(int width, int height) 
{
    __sdag_init();
    iteration = 0;
    w = width;
    h = height;
    for(int i = 0; i < width * height; i++)
    {
        rgb p;
        p.r = 255;
        p.g = 0;
        p.b = 0;
        pixelArray.push_back(p);
    }
    tmpBuffer =  new double[w*h];
};

PixelChare::PixelChare(CkMigrateMessage *m)
{
    __sdag_init();
};

PixelChare::~PixelChare() 
{
    if(tmpBuffer != NULL) delete [] tmpBuffer;
};

void PixelChare::doWork()
{
    //Do work
    
    
}


void PixelChare::liveVizDump(liveVizRequestMsg *m) 
{        
    rgb* imageBuff = (rgb*)tmpBuffer;
    
    register int imgIndex;
    rgb* c;
    for (int x = 0; x < w; x++) 
    {
	    for (int y = 0; y < h; y++) 
	    {
            imgIndex = (y * w) + x;
		    c = &(imageBuff[imgIndex]);
		    c->r = pixelArray[imgIndex].r;
		    c->g = pixelArray[imgIndex].g;
		    c->b = pixelArray[imgIndex].b;
	    }
    }

    liveVizDeposit(m, thisIndex.x * w, thisIndex.y * h,
                    w, h, (byte*)(imageBuff), this);
}
#include "pixelchare.def.h" 