#include <liveViz.h>
#include "pup_stl.h"
#include "common.h"
#include <stdio.h>
#include "ray.h"
#include "math.h"
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
        image_w = LIMIT;
        image_h = LIMIT;
        
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
        //CkPrintf("Invalid number of arguments\n");
        //CkExit();
    }
    delete arg;
    Total_iterations = ITERATIONS;
    CkArrayOptions opts(chareDimension, chareDimension);
    myOpts = opts;


    //TODO: Read file and create shape objects
    /*
    lightSrc l(1.0, 1.0, 1.0, 0.0, 240.0, -100.0);
    lightSrc l1(1.0, 1.0, 1.0, 640.0, 0.0, -10000.0);
    //lightSrc l2(1.0, 1.0, 1.0, -100.0, 0.0, -100.0);
    //lightSrc l3(1.0, 1.0, 1.0, 100.0, 100.0, -100.0);
    
    l.print();
    CkPrintf("\n*************\n");
    /*for(int i = 0; i<size; i++)
    {
        //sp[i].printShape();
        //s[i] = new Sphere();   
    }
    Shape s(100.0, 233.0, 290.0, 0.0, 1.0, 0.0, 0.0, 1.0);
    Shape s2(100.0, 407.0, 290.0, 0.0, 0.5, 1.0, 0.0, 0.0);
    Shape s3(100.0, 320.0, 140.0, 0.0, 0.5, 0.0, 1.0, 0.0);
    Shape s4(30.0, 50.0, 50.0, 50.0, 0.5, 0.0, 1.0, 1.0);
    Shape s5(60.0, 400.0, 400.0, 400.0, 0.5, 1.0, 0.0, 1.0);
    */
    lightSrc l(1.0, 1.0, 1.0, 0.0, 240.0, -100.0);
    lightSrc l1(1.0, 0.5, 0.5, 640.0, 0.0, -10000.0);
    //lightSrc l2(1.0, 1.0, 1.0, -100.0, 0.0, -100.0);
    //lightSrc l3(1.0, 1.0, 1.0, 100.0, 100.0, -100.0);
    
    Shape s(100.0, 233.0, 290.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    Shape s2(100.0, 407.0, 290.0, 0.0, 0.5, 1.0, 0.0, 0.0);
    Shape s3(100.0, 320.0, 140.0, 0.0, 0.5, 0.0, 1.0, 0.0);
    Shape s4(30.0, 50.0, 50.0, 50.0, 0.5, 0.0, 1.0, 1.0);
    Shape s5(60.0, 400.0, 400.0, 400.0, 0.5, 1.0, 0.0, 1.0);
    
    s.print();
    s2.print();
    s3.print();

    myShapes.push_back(s);
    myShapes.push_back(s2);
    myShapes.push_back(s3);
    myShapes.push_back(s4);
    myShapes.push_back(s5);
    
    myLights.push_back(l);
    myLights.push_back(l1);
    
    for (int i=0; i<myShapes.size(); i++)
    {
        vec3D d(pow(-1.0, i));
        shapeDirection.push_back(d);
    }
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
/*
class Direction
{
    public:
    int x_dir, y_dir, z_dir;
    
    Direction()
    {
        this->x_dir = 0;
        this->y_dir = 0;
        this->z_dir = 0;
    }
    Direction(int i)
    {
        this->x_dir = i;
        this->y_dir = i;
        this->z_dir = i;
    }
    void pup(PUP::er &p)
    {
        p | x_dir;
        p | y_dir;
        p | z_dir;
    }
    
};
*/
//Rotates all lightsources about the Z-axis
void Main::rotateLights()
{
    int x,y;
    for(int i = 0; i < myLights.size(); i++)
    {
        x = myLights[i].loc.x - LIMIT/2;
        y = myLights[i].loc.y - LIMIT/2;
        myLights[i].loc.x = x*cos(ROT_RAD*(i+1)) + y*sin(ROT_RAD*(i+1)) + LIMIT/2;
        myLights[i].loc.y = x*sin(-(ROT_RAD*(i+1))) + y*cos(ROT_RAD*(i+1)) + LIMIT/2;
    }
    if(MOVE_SHAPE){
        for(int i = 0; i < myShapes.size(); i++)
        {
        
            myShapes[i].loc.x = myShapes[i].loc.x + (shapeDirection[i].x*(((i + 1)/*%SHAPE_DISP*/)%LIMIT));
            myShapes[i].loc.y = myShapes[i].loc.y + (shapeDirection[i].y*(((i + 1)/*%SHAPE_DISP*/)%LIMIT));
            myShapes[i].loc.z = myShapes[i].loc.z + (shapeDirection[i].z*(((i + 1)/*%SHAPE_DISP*/)%LIMIT));
            
            (myShapes[i].loc.x /*+ myShapes[i].size*/ > LIMIT || myShapes[i].loc.x /*-myShapes[i].size*/ < 0)? shapeDirection[i].x*=-1:shapeDirection[i].x*=1;
            (myShapes[i].loc.y /*+ myShapes[i].size*/ > LIMIT || myShapes[i].loc.y /*-myShapes[i].size*/ < 0) ? shapeDirection[i].y*=-1:shapeDirection[i].y*=1;
            (myShapes[i].loc.z /*+ myShapes[i].size*/ > LIMIT || myShapes[i].loc.y /*-myShapes[i].size*/ < 0) ? shapeDirection[i].z*=-1:shapeDirection[i].z*=1;
        }
        sendShape = myShapes;
    }
}


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
