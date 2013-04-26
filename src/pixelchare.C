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


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


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



void PixelChare::doWork()
{
    int pixel_x, pixel_y, hitIndex, level, index;
    int position_x = thisIndex.x * w;
    int position_y = thisIndex.y * h; 
    
    

    for(int i = 0; i < w; i++)
    {
        pixel_x = GetCoord(0, w, -2.5, 2.5, i);
        for(int j = 0; j < h; j++)
        {
            index = (j * w) + i;
            pixel_y = GetCoord(0, h, 2.5, -2.5, j);
            //pixel_x = position_x + i;
            //pixel_y = position_y + j;

            

            float mindist = 1.0E10;
            int HitIndex = -1;

            //we dont use getcoordinates I dont think we need to 

            //not correct
            //ray viewRay(float(pixel_x), float(pixel_y), 10.0f, 0.0f, 0.0f, -10.0f);
            
            //make sense because our view comes from a point not form a plane
            ray viewRay(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, -100.0f); 

            //gets the unit vector of the direction 
            viewRay.modv();

            for(int s = 0; s < myShapes.size(); s++)
            {
                float taux = myShapes[s].GetInterSect(viewRay.start, vec3d(pixel_x, pixel_y, 0.0));
                if (taux < 0) continue;
                if (taux > 0 && taux < mindist)
                {
                    mindist = taux;
                    HitIndex = s;
                }
            }
            if (HitIndex != -1)
            {
                //double intersx = px + t * vx;
                //double intersy = py + t * vy;
                //double intersz = pz + t * vz;

                vec3d intersection = viewRay.dir * mindist;
                intersection += viewRay.start;

                //double l2px = intersx - px, l2py = intersy - py, l2pz = intersz - pz;

                vec3d l2p = intersection - viewRay.start;
                l2p.norm();

                //double vNormalX = triangleHit.tnormalX, vNormalY = triangleHit.tnormalY, vNormalZ = triangleHit.tnormalZ;
                vec3d vNormal = myShapes[HitIndex].getNormal();
                vNormal.norm();

                float cost = dot(l2p, vNormal);
                if (cost < 0) cost = 0;

                //float reflx = myShapes[HitIndex].r;
                //vec3d vRefl(reflx, reflx, reflx);

                vec3d vRefl = reflect(l2p, vNormal);
                vRefl.norm();
            
                vec3d vEye2Inters = intersection - viewRay.start;
                vEye2Inters.norm();

                float cosf = dot(vRefl, vEye2Inters);

                if (cosf < 0) cosf = 0;

                float result1 = cost * 255.0;
                float result2 = pow(cosf, myShapes[HitIndex].r) * 255.0;;

                pixelArray[index].r = (myShapes[HitIndex].c_Amb.x * 255.0) + 
                                        (myShapes[HitIndex].c_Dif.x * result1) +
                                        (myShapes[HitIndex].c_Spk.x * result2);
                pixelArray[index].g = (myShapes[HitIndex].c_Amb.y * 255.0) + 
                                        (myShapes[HitIndex].c_Dif.y * result1) +
                                        (myShapes[HitIndex].c_Spk.y * result2);
                pixelArray[index].b = (myShapes[HitIndex].c_Amb.z * 255.0) + 
                                        (myShapes[HitIndex].c_Dif.z * result1) +
                                        (myShapes[HitIndex].c_Spk.z * result2);


                pixelArray[index].r = MIN(pixelArray[index].r, 255);
                pixelArray[index].g = MIN(pixelArray[index].g, 255);
                pixelArray[index].b = MIN(pixelArray[index].b, 255);
                pixelArray[index].r = MAX(pixelArray[index].r, 0);
                pixelArray[index].g = MAX(pixelArray[index].g, 0); 
                pixelArray[index].b = MAX(pixelArray[index].b, 0);
            }

        }

    }

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
