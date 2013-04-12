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

PixelChare::PixelChare(int width, int height) 
{
    //CkPrintf("\nPixelChare [%d][%d]", thisIndex.x, thisIndex.y);
    __sdag_init();
    usesAtSync = CmiTrue;
    setMigratable(CmiTrue);
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


float PixelChare::gamma(float c)
{
    if (c <= 0.0031308f)
    {
        return 12.92f * c; 
    }
    else
    {
        return 1.055f * powf(c, 0.4166667f) - 0.055f; // Inverse gamma 2.4
    }
};


PixelChare::PixelChare(CkMigrateMessage *m)
{
    __sdag_init();
};


void PixelChare::pup(PUP::er &p)
{
    CBase_PixelChare::pup(p);
    __sdag_pup(p);
    p|myShapes;
    p|myLights;
    p|pixelArray;
    p|iteration;
    p|x;
    p|y;
    p|w;
    p|h;
    if (p.isUnpacking()) tmpBuffer = new double[w*h];
    p(tmpBuffer,w*h); 
}

PixelChare::~PixelChare() 
{
    if(tmpBuffer != NULL) delete [] tmpBuffer;
};

void PixelChare::doWork()
{

}

void PixelChare::antiAliasWork()
{
    
}

void PixelChare::clearPixel(int index)
{
    pixelArray[index].r = 0;
    pixelArray[index].g = 0;
    pixelArray[index].b = 0;
}

void PixelChare::exposePixel(int index)
{
    pixelArray[index].r = (1.0f - expf(pixelArray[index].r * EXPOSURE_CONST));
    pixelArray[index].g = (1.0f - expf(pixelArray[index].g * EXPOSURE_CONST));
    pixelArray[index].b = (1.0f - expf(pixelArray[index].b * EXPOSURE_CONST));
}



void PixelChare::normalWork()
{

}

void PixelChare::ResumeFromSync()
{
    mainProxy.done();
}

void PixelChare::startStep(vector<Shape> shapes, vector<lightSrc> lights)
{
    //CkPrintf("\n runStep::Pixelchare [%d][%d]", thisIndex.x, thisIndex.y);
    myShapes.insert(myShapes.end(), shapes.begin(), shapes.end());
    myLights.insert(myLights.end(), lights.begin(), lights.end());

    run();
}


void PixelChare::runStep(vector<Shape> shapes, vector<lightSrc> lights)
{
    if(shapes.size() > 0)
    {
        myShapes.clear();
        myShapes.insert(myShapes.end(), shapes.begin(), shapes.end());
        
    }
    if(lights.size() > 0)
    {
        myLights.clear();
        myLights.insert(myLights.end(), lights.begin(), lights.end());

    }
    run();
}

//returns index of closest hit, NEGINF otherwise
int PixelChare::shoot(ray theRay, float &dist)
{
    
}

bool PixelChare::hit(int index, ray theRay, float &n)
{
    
}


bool PixelChare::triHit(int index, ray r, float &t)
{
    
    vec3d edge1 = myShapes[index].v1 - myShapes[index].v0;
    vec3d edge2 = myShapes[index].v2 - myShapes[index].v0;
    vec3d pvec = cross(r.dir, edge2);
    float det = dot(edge1, pvec);
    if (det == 0) return false;
    float invDet = 1 / det;
    vec3d tvec = r.start - myShapes[index].v0;
    float u = dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return false;
    vec3d qvec = cross(tvec, edge1);
    float v = dot(r.dir, qvec) * invDet;
    if (v < 0 || u + v > 1) return false;
    t = (float)(float(dot(edge2, qvec)) * invDet);
    if(t == 0) t = INF; 
    //CkPrintf("in tri-hit returned t is %f\n dot(e2,qvec) was %f, and invdet was %f", t, dot(edge2, qvec), invDet);
    return true;

}

void PixelChare::draw(int index, ray &theRay, int hitIndex, float ti, float &coef, int &level)
{
    
}

void PixelChare::liveVizFunc(liveVizRequestMsg *m) 
{        
    rgb_byte* imageBuff =  (rgb_byte*)tmpBuffer;
    //if(thisIndex.x == thisIndex.y && thisIndex.x == 0) CkPrintf("liveViz[%d][%d]\n", thisIndex.x, thisIndex.y);
    int imgIndex;
    rgb_byte* c;
    for (int x = 0; x < w; x++) 
    {
        for (int y = 0; y < h; y++) 
        {
            imgIndex = (y * w) + x;
            c = &(imageBuff[imgIndex]);
            /*c->r = 255;
            c->g = 255;
            c->b = 255;*/
            byte red, blue, green;
            if (pixelArray[imgIndex].r * 255.0 < 255.0) {
                if(GAMMA) c->r = (byte)(gamma(pixelArray[imgIndex].r) * 255.0);
                else  c->r = (byte)(pixelArray[imgIndex].r * 255.0);
            } else {
                c->r = (byte)255.0;
            }
            if (pixelArray[imgIndex].g * 255.0 < 255.0) {
                if(GAMMA) c->g = (byte)(gamma(pixelArray[imgIndex].g) * 255.0);
                else c->g = (byte)(pixelArray[imgIndex].g * 255.0);
            } else {
                c->g = (byte)255.0;
            }
            if (pixelArray[imgIndex].b * 255.0 < 255.0) {
                if(GAMMA) c->b = (byte)(gamma(pixelArray[imgIndex].b) * 255.0);
                else c->b = (byte)(pixelArray[imgIndex].b * 255.0);
            } else {
                c->b = (byte)255.0;
            }
     //c->r= 0;c->g = 0; c->b = 0;
    /*if((x+thisIndex.x * w) == 100 && (y+ thisIndex.y*h)== 400) 
    {
        c->r= 0;c->g = 0; c->b = 255;
    }*/
        }
    }

    liveVizDeposit(m, thisIndex.x * w, thisIndex.y * h,
                    w, h, (byte*)(imageBuff), this);
}
#include "pixelchare.def.h" 
