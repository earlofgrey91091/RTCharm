#include <liveViz.h>
#include "pup_stl.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "math.h"
using namespace std;
#include "main.h"
//#include "ShapeMsg.h"

/*readonly*/ CProxy_Main mainProxy;


Main::Main(CkArgMsg* arg) 
{
    __sdag_init();
    iterations = 0;
    //Process command-line arguments
    if( arg->argc == 5 )
    { 
        image_w = atoi(arg->argv[1]);
        image_h = atoi(arg->argv[2]);
        chareDimension = atoi(arg->argv[3]);
        numSpheres = atoi(arg->argv[4]);
        
        //force fit inputs
        image_w -= image_w % chareDimension;
        image_h -= image_h % chareDimension;
        if(image_w == 0 || image_h == 0)
        {
            CkPrintf("Invalid image size\n");
            CkExit();
        }

        //CkPrintf(" w is %d h is %d pw is %d ph is %d", image_w, image_h, pixel_w, pixel_h); 
        CkPrintf("\npicture will be %d pixels in height,\ncells will be %d pixels in width,\nthere will be %d cells\nthere will be %dspheres\n", 
                    image_h, image_w, chareDimension * chareDimension, numSpheres);
    }
    else
    {
        image_w = LIMIT;
        image_h = LIMIT;
        chareDimension = DEFAULT_CHAREDIM;
        numSpheres = DEFAULT_SPHERES;
        CkPrintf("\npicture will be %d pixels in height,\ncells will be %d pixels in width,\nthere will be %d cells\nthere will be %dspheres\n", 
                    image_h, image_w, chareDimension * chareDimension,numSpheres);
    }
    delete arg;

    CkArrayOptions opts(chareDimension, chareDimension);
    myOpts = opts;
    

    lightSrc l(1.0, 1.0, 1.0, 0.0, image_h/2, -100.0);
    lightSrc l1(1.0, 0.5, 0.5, image_w/2, 0.0, -10000.0);
    //lightSrc l2(1.0, 1.0, 1.0, 300.0, 100.0, -100.0);
    myLights.push_back(l);
    myLights.push_back(l1);
    //myLights.push_back(l2);
    /*for(int i = 0; i < numSpheres ; i++)
    {
        Shape s(drand48()*60.0, drand48()*image_w, drand48()*image_h, drand48()*image_w, .5, drand48(), drand48(), drand48());//sphere
        myShapes.push_back(s);
    }
    */
    for(int i = 0; i < numSpheres ; i++)
    {
	Shape s(drand48()*image_w, drand48()*image_h, drand48()*image_w, drand48()*image_w, drand48()*image_h, drand48()*image_w, drand48()*image_w, drand48()*image_h, drand48()*image_w, 2.0, drand48(), drand48(), drand48());

        //Shape s(200, 200, 0, 400, 200, 0, 300, 0, 0, .5, drand48(), drand48(), drand48());//triangle
        myShapes.push_back(s);
	//Shape s1(0, 200, 0, 200, 200, 0, 100, 0, 0, .5, drand48(), drand48(), drand48());//triangle
        //myShapes.push_back(s1);
    }
    if(MOVE_SHAPE)
    {
        for (int i=0; i<myShapes.size(); i++)
        {
            vec3D d(drand48()*10*pow(-1.0, i));
            shapeDirection.push_back(d);
        }
    }
    //Create the image pixel chares based on image size
    pixel = CProxy_PixelChare::ckNew(image_w/chareDimension, image_h/chareDimension, opts);
    CkPrintf("\nEach chare will have (%d * %d) pixels \n", image_w/chareDimension, image_h/chareDimension);
    startVis();
    pixel.startStep(myShapes, myLights);
    mainProxy.run();
}

Main::Main(CkMigrateMessage *msg){ }

//Rotates all lightsources about the Z-axis
void Main::rotateLights()
{
    /*
    int x,y;
    for(int i = 0; i < myLights.size(); i++)
    {
        x = myLights[i].loc.x - image_w/2;
        y = myLights[i].loc.y - image_h/2;
        myLights[i].loc.x = x*cos(ROT_RAD*(i+1)) + y*sin(ROT_RAD*(i+1)) + image_w/2;
        myLights[i].loc.y = x*sin(-(ROT_RAD*(i+1))) + y*cos(ROT_RAD*(i+1)) + image_h/2;
    }
    if(MOVE_SHAPE){
        for(int i = 0; i < myShapes.size(); i++)
        {
            myShapes[i].loc.x = myShapes[i].loc.x + shapeDirection[i].x;
            myShapes[i].loc.y = myShapes[i].loc.y + shapeDirection[i].y;
            myShapes[i].loc.z = myShapes[i].loc.z + shapeDirection[i].z;
            
            if ((myShapes[i].loc.x + myShapes[i].size > image_w) || 
                (myShapes[i].loc.x - myShapes[i].size < 0))
            {
                shapeDirection[i].x*=-1;
            }
            if((myShapes[i].loc.y + myShapes[i].size > image_h) || 
                (myShapes[i].loc.y - myShapes[i].size < 0))
            {
                shapeDirection[i].y*=-1;
            }
            if((myShapes[i].loc.z + myShapes[i].size > image_w) || 
                (myShapes[i].loc.y - myShapes[i].size < 0))
            {
                shapeDirection[i].z*=-1;
            }
        }
        sendShape = myShapes;
    }*/
}


void Main::startVis()
{
    int funcIndex = CkIndex_PixelChare::liveVizFunc(NULL);
    CkCallback cb0(funcIndex, pixel);

    // Create a liveViz configuration object
    liveVizConfig lvConfig(liveVizConfig::pix_color, true);

    // Initialize the liveViz library
    liveVizInit(lvConfig, pixel, cb0, myOpts);

    /*double resumeTime = CmiWallTimer() + PAUSE_TIME;     // Pause for PAUSE_TIME seconds
     
    CkPrintf("Stalling after setup for %f s\n", PAUSE_TIME);
    int j = 0;
    while(CmiWallTimer() < resumeTime) j++;
    CkPrintf("Starting\n");*/

}
    
#include "main.def.h"
