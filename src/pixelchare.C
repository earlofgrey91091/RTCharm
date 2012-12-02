#include <pup_stl.h>
#include <liveViz.h>
#include "shape.h"
#include "pup_stl.h"
#include <stdio.h>
#include "common.h"
using namespace std;
#include "pixelchare.decl.h"
#include "pixelchare.h"
//#include "main.decl.h"
//#include "ShapeMsg.h"



extern /*readonly*/ CProxy_Main mainProxy;
extern /*readonly*/ int Total_iterations;
extern /*readonly*/ int chareDimension;


PixelChare::PixelChare(int width, int height) 
{
    //CkPrintf("\nPixelChare [%d][%d]", thisIndex.x, thisIndex.y);
    __sdag_init();
    iteration = 0;
    w = width;
    h = height;
    for(int i = 0; i < width * height; i++)
    {
        rgb p;
        p.r = 0;
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
    //Generate ray for each pixel in this pixel chare.
    int pixel_x;
    int pixel_y;
    int position_x = thisIndex.x * w;
    int position_y = thisIndex.y * h;
    ray viewRay;
    int hitIndex;

    // pixels will go from position_x -> position_x + w -1
    // pixels will go from position_y -> position_x + h -1
    //CkPrintf("\nDoing work [%d][%d] [%d][%d]-[%d][%d]", thisIndex.x, thisIndex.y, position_x,position_y, position_x+w-1, position_y+h-1);
    for(int i = 0; i < w-1 ; i++) 
    {
        for(int j = 0; j < h-1; j++) 
        {
            //CkPrintf("\n[%d][%d]", position_x + i, position_y + j);
            //Creating ray passing through each pixel in this chare
            pixel_x = position_x + i;
            pixel_y = position_y + j;
            viewRay.start.x = float(pixel_x);
            viewRay.start.y = float(pixel_y);
            viewRay.start.z = -1000.0f; 
            viewRay.dir.x = 0.0f;
            viewRay.dir.y = 0.0f;
            viewRay.dir.z = 1.0f;  
            //see what the closest hit is             
            hitIndex = shoot(viewRay);
            //DRAW!
            //draw(i,j, viewRay, hitIndex);
            
        }
    }
        
}


void PixelChare::runStep(vector<Shape> shapes, vector<lightSrc> lights)
{
    CkPrintf("\n runStep::Pixelchare [%d][%d]", thisIndex.x, thisIndex.y);
    myShapes.insert(myShapes.end(), shapes.begin(), shapes.end());
    myLights.insert(myLights.end(), lights.begin(), lights.end());
    
    //Test shape insert
    CkPrintf("All shapes recieved at index (%d,%d) \n", thisIndex.x, thisIndex.y);
    for (int i = 0; i< myShapes.size(); i++ )
    {
        myShapes[i].print();
        CkPrintf("\n ");
    }
    CkPrintf("All lightsources recieved at index (%d,%d) \n", thisIndex.x, thisIndex.y);
    for (int i = 0; i< myLights.size(); i++ )
    {
        myLights[i].print();
        CkPrintf("\n ");
    }
    
    //run();

}
/*
void PixelChare::recvSphere(int s, Sphere *sh)
{

    //CkPrintf("\n runStep::Pixelchare [%d][%d]", thisIndex.x, thisIndex.y);
    spheres = sh;
    for (int i = 0; i< s; i++ )
    {
    //    CkPrintf("\n size = %d %f,%f,%f", i, sh[i].r,sh[i].g,sh[i].b);
        shapes.push_back(sh[i]);
    //    CkPrintf("\n ");
    //    sh[i].printShape();
    }
    for(int i = 0 ; i<shapes.size(); i++)
    {
        shapes[i].printShape();
    }
    //CkPrintf("-%d,%d-", s, shapes.size());
    run();

}*/

//returns index of closest hit, NEGINF otherwise
int PixelChare::shoot(ray theRay)
{
    int minIndex = NEGINF;
    float minVal = INF;
    float n = INF;    
    for(int i = 0; i < myShapes.size(); i++)
    {
        hit(i, theRay, &n);
        if(n < minVal)
        {
            minVal = n;
            minIndex = i;
        }
    }
    return minIndex;
}

bool PixelChare::hit(int index, ray theRay, float *n)
{
    bool result = false;
    switch(myShapes[index].type)
    {
        case SPHERE: result = sphereHit( index, theRay, n); break;
        default: CkPrintf("Attempted to compute hit for unrecognised shape with type id %d", myShapes[index].type);
    }
    return result;
}

bool PixelChare::sphereHit(int index, ray theRay, float *n)
{
    //TODO sphere hit function
    *n = NEGINF;
    return false;
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
