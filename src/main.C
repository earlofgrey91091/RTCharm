#include <liveViz.h>
#include "pup_stl.h"
#include "common.h"
#include <stdio.h>
#include "shape.h"
using namespace std;
#include "main.h"
//#include "ShapeMsg.h"





/*class ShapeMsg : public CMessage_ShapeMsg {
public:
  Shape *s;
  int size;

  ShapeMsg(int z)
  {
    size = z;
  }
};*/






/*readonly*/ CProxy_Main mainProxy;
/*readonly*/ int Total_iterations;
/*readonly*/ int chareDimension;
/*readonly*/ int size;

Main::Main(CkArgMsg* arg) 
{
    //__sdag_init();
    int image_w, image_h, pixel_w, pixel_h; 
    string filename = "objects.txt";
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
    
	//Shape s;
    
   	
	CkPrintf("\n*************");
	for(int i = 0; i<size; i++)
	{
		//myShapes
        //sp[i].printShape();
		//s[i] = new Sphere(); 
	}
	CkPrintf("\n*************");
    

    //Create the image pixel chares based on image size
    pixel = CProxy_PixelChare::ckNew(pixel_w/chareDimension, pixel_h/chareDimension, opts);
	CkPrintf("\nEach chare will have (%d * %d) pixels ", pixel_w/chareDimension, pixel_h/chareDimension);
    //startVis();
    //pixel.runStep(myShapes, myLights);

}

Main::Main(CkMigrateMessage *msg){ }

void Main::done()
{
	CkExit();
}

void Main::startVis()
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
    
#include "main.def.h"
