#include <liveViz.h>
#include "pup_stl.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "vecmath.h"
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
        numShapes = atoi(arg->argv[4]);
        
        //force fit inputs
        image_w -= image_w % chareDimension;
        image_h -= image_h % chareDimension;
        if(image_w == 0 || image_h == 0)
        {
            CkPrintf("Invalid image size\n");
            CkExit();
        }

        CkPrintf("\npicture will be %d pixels in height,\n", image_h);
        CkPrintf("picture will be %d pixels in width,\n", image_w);
        CkPrintf("there will be %d cells\n", chareDimension * chareDimension);
        CkPrintf("there will be %d shapes\n", numShapes);
    }
    else
    {
        image_w = LIMIT;
        image_h = LIMIT;
        chareDimension = DEFAULT_CHAREDIM;
        numShapes = DEFAULT_SHAPES; //misnameed need fix
        CkPrintf("\npicture will be %d pixels in height,\n", image_h);
        CkPrintf("picture will be %d pixels in width,\n", image_w);
        CkPrintf("there will be %d cells\n", chareDimension * chareDimension);
        CkPrintf("there will be %d shapes\n", numShapes);
    }
    delete arg;

    CkArrayOptions opts(chareDimension, chareDimension);
    myOpts = opts;
    

    lightSrc l(1.0, 1.0, 1.0, 0.0, image_h/2, -100.0);
    lightSrc l1(1.0, 0.5, 0.5, image_w/2, 0.0, -10000.0);
    myLights.push_back(l);
    myLights.push_back(l1);
    //positive z is going twards the viewer
    // positive x is 
    float zdiff = 0; //70
    //vec3d v0(268.0, 178.0, 276.0), v1( 178.0,268.0, 276.0 - zdiff), v2(268.0,268.0, 276.0 - zdiff*1.5), mod(-50, -50, 90);
    //vec3d v0(0.0, 0.0, 0), v1( -100.0,0.0, 0 -zdiff), v2(0.0,100.0, 0 - zdiff*1.5), mod(-50, -50, 90);  
    /*for(int i = 0; i < numShapes ; i++)
    {
        
	    Shape s(v0, v1, v2, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 1.0);
	    myShapes.push_back(s);
	    v0+=mod; v1+=mod; v2+=mod;
	            
    }*/
    
    vec3d v0(-1.000000, -1.000000, 1.000000);
    vec3d v1(-1.000000, 1.000000, 1.000000);
    vec3d v2(1.000000, 1.000000, 1.000000);
    vec3d v3(1.000000, -1.000000, 1.000000);
    vec3d v4(-1.000000, -1.000000, -1.000000);
    vec3d v5(-1.000000, 1.000000, -1.000000);
    vec3d v6(1.000000, 1.000000, -1.000000);
    vec3d v7(1.000000, -1.000000, -1.000000);
    
    double rx = 0.75000;
    double ry = -0.5000;
    double rz = 0.0000;
    
    Shape s = Shape(v4, v7, v6, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v6, v5, v4, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v0, v3, v2, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v2, v1, v0, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v4, v0, v1, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v1, v5, v4, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v7, v3, v2, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v2, v6, v7, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v7, v3, v0, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v0, v4, v7, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v6, v2, v1, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    s = Shape(v1, v5, v6, vec3d(0.3, 0.4, 0.5), vec3d(0.3775, 0.3775, 0.5775), vec3d(0.911, 0.911, 0.911), 0.0);
    s.rot_x(rx); s.rot_y(ry); myShapes.push_back(s);
    


    /*
    if(MOVE_SHAPE)
    {
        for (int i=0; i<myShapes.size(); i++)
        {
            vec3d d(drand48()*10*pow(-1.0, i));
            shapeDirection.push_back(d);
        }
    }*/
    //Create the image pixel chares based on image size
    pixel = CProxy_PixelChare::ckNew(image_w/chareDimension, 
                                        image_h/chareDimension, opts);
    CkPrintf("\nEach chare will have (%d * %d) pixels \n", 
                image_w/chareDimension, image_h/chareDimension);
    CkPrintf("MyShapes.size() = %d", myShapes.size());
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
            //vec3d v= myShapes[i].loc;
            
            //fortriangles
            myShapes[i].v1 += vec3d(0.0,0.0, 100.0);
            myShapes[i].v1 += vec3d(0.0,0.0, 100.0);
            myShapes[i].v2 += vec3d(0.0,0.0, 100.0);
            
            //CkAssert(myShapes[i].loc == (v+vec3d(60.0,0.0, 20.0)));
        }
        sendShape = myShapes;
    }
    */
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
