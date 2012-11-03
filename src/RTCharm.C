#include "liveViz.h"
#include "shape.h"
#include "pup_stl.h"
#include <stdio.h>
#include "RTCharm.decl.h"
#define ITERATIONS 1000

/*readonly*/ CProxy_Main mainProxy;
/*readonly*/ int Total_iterations;
/*readonly*/ int chareDimension;
class Main : public CBase_Main {
    public:
        CProxy_PixelChare pixel;
        CkOpts myOpts
    void run();
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

                CkPrintf("\n [l]: cells will be %d pixels in height," +
                            "\n cells will be %d pixels in width,\n " + 
                            "there will be %d cells\n", image_h, image_w, 
                            chareDimension * chareDimesion);
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
            run();

        };

    void startVis()
    {
	    int funcIndex = CkIndex_Skittish::liveVizDump(NULL);
	    CkCallback cb0(funcIndex, skitArray);

	    // Create a liveViz configuration object
	    liveVizConfig lvConfig(liveVizConfig::pix_color, true);

	    // Initialize the liveViz library
	    liveVizInit(lvConfig, skitArray, cb0, myOpts);

	    /*double resumeTime = CmiWallTimer() + PAUSE_TIME + PAUSE_TIME;     // Pause for PAUSE_TIME seconds
	     
	    CkPrintf("Stalling after setup for %f s\n", PAUSE_TIME + PAUSE_TIME);
	    int j = 0;
	    while(CmiWallTimer() < resumeTime) j++;*/
	
    }
    

};

/*array [2D]*/
class PixelChare : public CBase_PixelChare 
{
    public:
    PixelChare_SDAG_CODE    
    typedef struct { byte r, g, b; } rgb;
    vector<rgb> pixels;
    int x, y, w, h;
    int iteration;

    PixelChare(int width, int height) 
    {
        __sdag_init();
        iteration = 0;
        w = width;
        h = height;
    };

    PixelChare(CkMigrateMessage *m)
    {
        __sdag_init();
    };
    
    void doWork()
    {
        //Do work
        
        
    }

    float xValue(float x) 
    {
        return (x - thisIndex.x/chareDimension) * chareDimension;
    }

    float yValue(float y) 
    {
        return (y - thisIndex.y/chareDimension) * chareDimension;
    }


    void liveVizDump(liveVizRequestMsg *m) 
    {
        int arrayDim = 256/chareDimension;
        int xCar, yCar;
        int Cal;
        
        rgb* imageBuff = new rgb[arrayDim * arrayDim];
        CkAssert(sizeof(rgb) == 3);
        
        for(int i =0;i<arrayDim * arrayDim;i++) 
        {
            imageBuff[i].r=0;
            imageBuff[i].g=0;
            imageBuff[i].b=0;
        }
        
        for (int index = 0; index < pixels.size();index++) 
        {
            xCar =(int) ((float) xValue(pixels[index].x) * (float)arrayDim) ;
            yCar = (int) ((float) yValue(pixels[index].y) * (float)arrayDim) ;

            Cal = ((yCar * arrayDim) + xCar);
            if(pixels[index].color == 'R')
                imageBuff[Cal%(arrayDim*arrayDim)].r = 255 ;
            else if(pixels[index].color == 'G')
                imageBuff[Cal%(arrayDim*arrayDim)].g = 255;
            else if(pixels[index].color == 'B')
                imageBuff[Cal%(arrayDim*arrayDim)].b = 255;
        }

        liveVizDeposit(m, thisIndex.x * arrayDim, thisIndex.y * arrayDim,
        arrayDim, arrayDim, reinterpret_cast<byte*>(imageBuff),
        this, max_image_data);
        delete [] imageBuff;
    }




};

#include "RTCharm.def.h"
