#include <pup_stl.h>
#include <liveViz.h>
#include "ray.h"
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
   if(DEBUG_CODE) CkPrintf("Chare created!\n");
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
    float dist;
    int hitIndex;
    float coef = 1.0f;
    int level = 0;
    int index;

    // pixels will go from position_x -> position_x + w -1
    // pixels will go from position_y -> position_x + h -1
    //CkPrintf("\nDoing work [%d][%d] [%d][%d]-[%d][%d]", thisIndex.x, thisIndex.y, position_x,position_y, position_x+w-1, position_y+h-1);
    for(int i = 0; i < w; i++) 
    {
        for(int j = 0; j < h; j++) 
        {
            //CkPrintf("\n[%d][%d]", position_x + i, position_y + j);
            //Creating ray passing through each pixel in this chare
            index = (j * w) + i;
            pixel_x = position_x + i;
            pixel_y = position_y + j;
            ray viewRay(float(pixel_x), float(pixel_y), -1000.0f, 0.0f, 0.0f, 1.0f);
            //see what the closest hit is             
            coef = 1.0f;
            level = 0;
            pixelArray[index].r = 0;
            pixelArray[index].g = 0;
            pixelArray[index].b = 0;
            do
            {
                hitIndex = shoot(viewRay, dist);
                //DRAW!
                if(hitIndex == NEGINF)
                {
                    break;
                }
             if(DEBUG_CODE)   CkPrintf("******************************************\n");
             if(DEBUG_CODE)   CkPrintf(" Lucky pixel = [%d, %d] hitindex = %d\n", pixel_x, pixel_y, hitIndex);
                draw(index, viewRay, hitIndex, dist, coef, level);

                //CkPrintf("\n level = %d", level);
              if(DEBUG_CODE)  CkPrintf("******************************************\n");
                
            }
            while((coef > 0.0f) && (level < 10));
        }
    }
        
}


void PixelChare::runStep(vector<Shape> shapes, vector<lightSrc> lights)
{
    //CkPrintf("\n runStep::Pixelchare [%d][%d]", thisIndex.x, thisIndex.y);
    myShapes.insert(myShapes.end(), shapes.begin(), shapes.end());
    myLights.insert(myLights.end(), lights.begin(), lights.end());

    run();

}

//returns index of closest hit, NEGINF otherwise
int PixelChare::shoot(ray theRay, float &dist)
{
    int minIndex = NEGINF;
    float minVal = INF;
    float n = INF;    
    for(int i = 0; i < myShapes.size(); i++)
    {
        hit(i, theRay, n);
        if(n < minVal)
        {
            minVal = n;
            minIndex = i;
        }
    }
    dist = minVal;
    return minIndex;
}

bool PixelChare::hit(int index, ray theRay, float &n)
{
    bool result = false;
    switch(myShapes[index].type)
    {
        case SPHERE: result = sphereHit( index, theRay, n); break;
        default: CkPrintf("Attempted to compute hit for unrecognised shape with type id %d\n", myShapes[index].type);
    }
    return result;
}

bool PixelChare::sphereHit(int index, ray r, float &t)
{
    // sphere hit function
    vec3D dist = myShapes[index].loc - r.start;

    float B = r.dir * dist;
    float D = B*B - dist * dist + myShapes[index].size * myShapes[index].size;

    if (D < 0.0f) 
    {
        return false; 
    }

    float t0 = B - sqrtf(D); 
    float t1 = B + sqrtf(D);
    bool retvalue = false;

    if ((t0 > 0.1f) && (t0 < t)) 
    {
        t = t0;
        retvalue = true; 
    } 
    if ((t1 > 0.1f) && (t1 < t)) 
    {
        t = t1; 
        retvalue = true; 
    }
    return retvalue; 


    //*n = NEGINF;
    //return false;
}


void PixelChare::draw(int index, ray theRay, int hitIndex, float t, float &coef, int &level)
{
    coord3D newStart = theRay.start + t * theRay.dir;
    vec3D n = newStart - myShapes[hitIndex].loc; //figuring out the normal vector at the point of intersection
    float temp = n * n;
    float dummy;
    float lambert;

    
    
    if (temp == 0.0f)
    {
    //it could fail here!!!!
        //break;
        return;
    }

    temp = 1.0f / sqrtf(temp);
    n = temp * n;

    
    for(int j = 0; j < myLights.size(); ++j)
    {
        lightSrc current = myLights[j];
        //current.print();
        vec3D dist = current.loc - newStart;

        if(n * dist <= 0.0f)
        {
            continue;
        }
        float t = sqrtf(dist * dist);
        if ( t <= 0.0f )
            continue;
        ray lightRay;
        lightRay.start = newStart;
        lightRay.dir = (1/t)*dist;



        if(shoot(lightRay, dummy) == NEGINF)
        {
            lambert = (lightRay.dir * n) * (coef);
            
            pixelArray[index].r += lambert * current.r * myShapes[hitIndex].red;
            pixelArray[index].g += lambert * current.g * myShapes[hitIndex].green;
            pixelArray[index].b += lambert * current.b * myShapes[hitIndex].blue;
            if(DEBUG_CODE) 
            {
                CkPrintf("current lightray.dir = %f, n = %f coef = %f", lightRay.dir, n, coef);
                CkPrintf("lambert = %f   current(%f,%f,%f)\n", lambert, current.r, current.g, current.b);
                CkPrintf("hitindex = %d shape.color(%f,%f,%f)\n", hitIndex, myShapes[hitIndex].red, myShapes[hitIndex].green, myShapes[hitIndex].blue);
                CkPrintf("pixelarray(%f,%f,%f\n",pixelArray[index].r,pixelArray[index].g,pixelArray[index].b);
                //myShapes[hitIndex].print();
            }
            //CkAssert(lambert <= 1);
        }
    }        

    coef *= myShapes[hitIndex].reflection;
    float reflect = 2.0f * (theRay.dir * n);
    theRay.start = newStart;
    theRay.dir = theRay.dir - reflect * n;
    
    level++; 
}

void PixelChare::liveVizFunc(liveVizRequestMsg *m) 
{        
    rgb_byte* imageBuff = (rgb_byte*)tmpBuffer;
   // CkPrintf("\nliveViz[%d][%d]", thisIndex.x, thisIndex.y);
    int imgIndex;
    rgb_byte* c;
    for (int x = 0; x < w; x++) 
    {
        for (int y = 0; y < h; y++) 
        {
            imgIndex = (y * w) + x;
            c = &(imageBuff[imgIndex]);
            byte red, blue, green;
            if (pixelArray[imgIndex].r * 255.0 < 255.0) {
                c->r = (byte)(pixelArray[imgIndex].r * 255.0);
            } else {
                c->r = (byte)255.0;
            }
            if (pixelArray[imgIndex].g * 255.0 < 255.0) {
                c->g = (byte)(pixelArray[imgIndex].g * 255.0);
            } else {
                c->g = (byte)255.0;
            }
            if (pixelArray[imgIndex].b * 255.0 < 255.0) {
                c->b = (byte)(pixelArray[imgIndex].b * 255.0);
            } else {
                c->b = (byte)255.0;
            }
        }
    }

    liveVizDeposit(m, thisIndex.x * w, thisIndex.y * h,
                    w, h, (byte*)(imageBuff), this);
}
#include "pixelchare.def.h" 
