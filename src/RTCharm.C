#include "liveViz.h"
#include "shape.h"
#include "pup_stl.h"
#include <stdio.h>
using namespace std;
#include "RTCharm.decl.h"



#define ITERATIONS 1000
#define loc(x,y, width)  (x + (y*width))


/*readonly*/ CProxy_Main mainProxy;
/*readonly*/ int Total_iterations;
/*readonly*/ int chareDimension;
class Main : public CBase_Main {
    public:
        Main_SDAG_CODE;
        CProxy_PixelChare pixel;
        CkArrayOptions myOpts;
        
        Main(CkArgMsg* arg) 
        {
            __sdag_init();
            int image_w, image_h, pixel_w, pixel_h; 
            string filename = "objects.txt";

            //Process command-line arguments
            if( arg->argc > 0 )
            { 
                image_w = atoi(arg->argv[0]);
                image_h = atoi(arg->argv[1]);
                
                //force fit inputs
                if(image_w % 8 != 0) image_w += image_w % 8;
                if(image_h % 8 != 0) image_h += image_h % 8;

                chareDimension = 8;
                pixel_w = image_w/8;
                pixel_h = image_h/8;

                CkPrintf("\n [l]: cells will be %d pixels in height,\ncells will be %d pixels in width,\nthere will be %d cells\n", 
                            pixel_h, pixel_w, chareDimension * chareDimension);
            }
            else
            {
                CkPrintf("Invalid number of arguments\n");
                CkExit();
            }
            delete arg;
            Total_iterations = ITERATIONS;
            CkArrayOptions opts(chareDimension, chareDimension);
            myOpts = opts;
            //TODO: Read file and create shape objects

            //Create the image pixel chares based on image size
            pixel = CProxy_PixelChare::ckNew(pixel_w, pixel_h, opts);
            startVis();
            mainProxy.run();

        };
        
        void startVis()
        {
	        int funcIndex = CkIndex_PixelChare::liveVizDump(NULL);
	        CkCallback cb0(funcIndex, pixel);

	        // Create a liveViz configuration object
	        liveVizConfig lvConfig(liveVizConfig::pix_color, true);

	        // Initialize the liveViz library
	        liveVizInit(lvConfig, pixel, cb0, myOpts);

	        /*double resumeTime = CmiWallTimer() + PAUSE_TIME + PAUSE_TIME;     // Pause for PAUSE_TIME seconds
	         
	        CkPrintf("Stalling after setup for %f s\n", PAUSE_TIME + PAUSE_TIME);
	        int j = 0;
	        while(CmiWallTimer() < resumeTime) j++;*/
	
        }
    

};


class PixelChare : public CBase_PixelChare 
{
    public:
    PixelChare_SDAG_CODE;    
    typedef struct { byte r, g, b; } rgb;
    vector<rgb> pixelArray;
    double *tmpBuffer;
    int x, y, w, h;
    int iteration;

    PixelChare(int width, int height) 
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

    PixelChare(CkMigrateMessage *m)
    {
        __sdag_init();
    };

    ~PixelChare() 
    {
        if(tmpBuffer != NULL) delete [] tmpBuffer;
    };
    
    void doWork()
    {
        //Do work
        
        
    }


    void liveVizDump(liveVizRequestMsg *m) 
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


          /*  for (int index = 0; index < pixelArray.size();index++) 
            {
                xCar =(int) ((float) xValue(index%w) * (float)arrayDim) ;
                yCar = (int) ((float) yValue(index/w) * (float)arrayDim) ;

                Cal = ((yCar * arrayDim) + xCar);
                imageBuff[index].r = pixelArray[index].r;
                imageBuff[Cal%(arrayDim*arrayDim)].g = pixelArray[index].g;
                imageBuff[Cal%(arrayDim*arrayDim)].b = pixelArray[index].b;
            }*/

    }




};

#include "RTCharm.def.h"
