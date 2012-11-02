#include "liveViz.h"
#include "shape.h"
#include "pup_stl.h"
#include <stdio.h>
#include "RTCharm.decl.h"
#define ITERATIONS 1000

/*readonly*/ CProxy_Main mainProxy;
/*readonly*/ int Total_iterations;
/*readonly*/ int cellDimension;
/*readonly*/ int pixelsPerCell;
class Main : public CBase_Main {
public:
  CProxy_PixelChare pixel;
  Main(CkArgMsg* arg) {
    int image_l = 0, image_b = 0;
    char *objectsFileName;
    //Process command-line arguments
    if( arg->argc > 0 )
    { 
	image_l = atoi(arg->argv[0]);
	image_b = atoi(arg->argv[1]);
	printf("\n l = %d, b = %d", image_l, image_b);
	cellDimension = 8;
	pixelsPerCell = (image_l * image_b) / (cellDimension * cellDimension);
    }
    else
    {
	CkPrintf("Invalid number of arguments\n");
	CkExit();
    }
    delete arg;
    Total_iterations = ITERATIONS;
    //TODO: Read file and create shape objects
    
    //Create the image pixel chares based on image size
    pixel = CProxy_PixelChare::ckNew(image_l, image_b);
   
    //Run!
    //
    //
   
    CkArrayOptions opts(cellDimension,cellDimension);
    CkCallback cb(CkIndex_PixelChare::liveVizDump(NULL), pixel);
    liveVizConfig cfg(liveVizConfig::pix_color, true);
    liveVizInit(cfg, pixel, cb, opts);

    CkPrintf("\n");
    CkExit();
  };
};

/*array [2D]*/
class PixelChare : public CBase_PixelChare {
public:
PixelChare_SDAG_CODE

int x, y;
int iteration;

float xValue(float x) {
		return (x - thisIndex.x/cellDimension) * cellDimension;
	}
	
float yValue(float y) {
                return (y - thisIndex.y/cellDimension) * cellDimension;
	}


void liveVizDump(liveVizRequestMsg *m) {
           int arrayDim = 256/cellDimension;
           int xCar, yCar;
	
	   int Cal;
           typedef struct { byte r, g, b; } rgb;
           rgb* imageBuff = new rgb[arrayDim * arrayDim];
           CkAssert(sizeof(rgb) == 3);
	   for(int i =0;i<arrayDim * arrayDim;i++) {
		imageBuff[i].r=0;
		imageBuff[i].g=0;
		imageBuff[i].b=0;
	   }
       for (int index = 0; index < particles.size();index++) {
         xCar =(int) ((float) xValue(particles[index].x) * (float)arrayDim) ;
         yCar = (int) ((float) yValue(particles[index].y) * (float)arrayDim) ;
	
	 Cal = ((yCar * arrayDim) + xCar);
         if(particles[index].color == 'R')
         imageBuff[Cal%(arrayDim*arrayDim)].r = 255 ;
         else if(particles[index].color == 'G')
         imageBuff[Cal%(arrayDim*arrayDim)].g = 255;
         else if(particles[index].color == 'B')
         imageBuff[Cal%(arrayDim*arrayDim)].b = 255;
        }

           liveVizDeposit(m, thisIndex.x * arrayDim, thisIndex.y * arrayDim,
                         arrayDim, arrayDim, reinterpret_cast<byte*>(imageBuff),
                                            this, max_image_data);
        delete [] imageBuff;
   }

PixelChare(void) {
__sdag_init();
iteration = 0;
};


PixelChare(CkMigrateMessage *m)
{
__sdag_init();
};


};

#include "RTCharm.def.h"
