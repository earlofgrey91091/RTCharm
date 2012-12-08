#include <liveViz.h>
#include "pup_stl.h"
#include "common.h"
#include <stdio.h>
#include "ray.h"
using namespace std;
#include "main.h"
//#include "ShapeMsg.h"

/*readonly*/ CProxy_Main mainProxy;
/*readonly*/ int Total_iterations;
/*readonly*/ int chareDimension;
/*readonly*/ int size;
Main::Main(CkArgMsg* arg) 
{
    __sdag_init();
    iterations = 0;
    int image_w, image_h, pixel_w, pixel_h; 
    //string filename = "objects.txt";
    size = SHAPES;
    chareDimension = 8;
    //Process command-line arguments
    if( arg->argc > 2 )
    { 
        image_w = atoi(arg->argv[1]);
        image_h = atoi(arg->argv[2]);
        
        //force fit inputs
        image_w -= image_w % chareDimension;
        image_h -= image_h % chareDimension;
        if(image_w == 0 || image_h == 0)
        {
            CkPrintf("Invalid image size\n");
            CkExit();
        }

        pixel_w = image_w;
        pixel_h = image_h;

        //CkPrintf(" w is %d h is %d pw is %d ph is %d", image_w, image_h, pixel_w, pixel_h); 
        CkPrintf("\ncells will be %d pixels in height,\ncells will be %d pixels in width,\nthere will be %d cells\n", 
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
    
    lightSrc l(1.0, 1.0, 1.0, 0.0, 240.0, -100.0);
    lightSrc l1(1.0, .5, 0.5, 640.0, 0.0, -10000.0);
    //lightSrc l2(1.0, 1.0, 1.0, -100.0, 0.0, -100.0);
    //lightSrc l3(1.0, 1.0, 1.0, 100.0, 100.0, -100.0);
    
    l.print();
    CkPrintf("\n*************\n");
    for(int i = 0; i<size; i++)
    {
        //myShapes
    
        //sp[i].printShape();
        //s[i] = new Sphere();
        
    }
    Shape s(100.0, 0, 233.0, 290.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    Shape s2(100.0, 0, 407.0, 290.0, 0.0, 0.5, 1.0, 0.0, 0.0);
    Shape s3(100.0, 0, 320.0, 140.0, 0.0, 0.5, 0.0, 1.0, 0.0);

    s.print();
    s2.print();
    s3.print();

    myShapes.push_back(s);
    myShapes.push_back(s2);
    myShapes.push_back(s3);
    myLights.push_back(l);
    myLights.push_back(l1);
    l.print();
    l1.print();
    //myLights.push_back(l2);
    //myLights.push_back(l3);
    CkPrintf("\n*************\n");
    //Create the image pixel chares based on image size
    pixel = CProxy_PixelChare::ckNew(pixel_w/chareDimension, pixel_h/chareDimension, opts);
    CkPrintf("\nEach chare will have (%d * %d) pixels \n", pixel_w/chareDimension, pixel_h/chareDimension);
    startVis();
    pixel.startStep(myShapes, myLights);
    mainProxy.run();
}

Main::Main(CkMigrateMessage *msg){ }


void Main::startVis()
{
    int funcIndex = CkIndex_PixelChare::liveVizFunc(NULL);
    CkCallback cb0(funcIndex, pixel);

    // Create a liveViz configuration object
    liveVizConfig lvConfig(liveVizConfig::pix_color, true);

    // Initialize the liveViz library
    liveVizInit(lvConfig, pixel, cb0, myOpts);

    double resumeTime = CmiWallTimer() + PAUSE_TIME;     // Pause for PAUSE_TIME seconds
     
    CkPrintf("Stalling after setup for %f s\n", PAUSE_TIME);
    int j = 0;
    while(CmiWallTimer() < resumeTime) j++;
    CkPrintf("Starting\n");

}
    
#include "main.def.h"
