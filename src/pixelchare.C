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
    //CkPrintf("doingwork\n");
    if(ANTI_ALIASING) antiAliasWork();
    else normalWork();
}

void PixelChare::antiAliasWork()
{
    //CkPrintf("antialiaswork\n");
    int pixel_x, pixel_y, hitIndex, level, index;
    int position_x = thisIndex.x * w;
    int position_y = thisIndex.y * h;
    float dist, coef /*, correction*/;
    for(int j = 0; j < w; j++) 
    {
        for(int i = 0; i < h; i++) 
        {
            index = (j * w) + i;
            pixel_x = position_x + i;
            pixel_y = position_y + j;
            for(float fragmentx = pixel_x; fragmentx < pixel_x + 1.0f; fragmentx += SAMPLE_RATIO * 2)
            {
                for(float fragmenty = pixel_y; fragmenty < pixel_y + 1.0f; fragmenty += SAMPLE_RATIO * 2)
                {
                    clearPixel(index);
                    ray viewRay(float(fragmentx), float(fragmenty),-1000.0f, 0.0f, 0.0f, 1.0f);
                    
                    coef = 1.0f;
                    level = 0;
                    do
                    {
                        hitIndex = shoot(viewRay, dist);
                        if(hitIndex == NEGINF) break;
                        draw(index, viewRay, hitIndex, dist, coef, level); 
                    } while((coef > 0.0f) && (level < 10));
                    
                    if(EXPOSURE)exposePixel(index);
                    //average in samples
                    pixelArray[index].r += pixelArray[index].r * SAMPLE_RATIO;
                    pixelArray[index].g += pixelArray[index].g * SAMPLE_RATIO;
                    pixelArray[index].b += pixelArray[index].b * SAMPLE_RATIO;
                }
            }
        }
    }
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
        //CkPrintf("normalwork\n");
    int pixel_x, pixel_y, hitIndex, level, index;
    int position_x = thisIndex.x * w;
    int position_y = thisIndex.y * h;
    float dist, coef; //, correction;

    for(int i = 0; i < w; i++) 
    {
        for(int j = 0; j < h; j++) 
        {
            //if(thisIndex.x == 0 && thisIndex.y == 0) CkPrintf("[%d][%d]\n", position_x + i, position_y + j);
            //Creating ray passing through each pixel in this chare
            index = (j * w) + i;
            pixel_x = position_x + i;
            pixel_y = position_y + j;
            ray viewRay(float(pixel_x), float(pixel_y), -1000.0f, 0.0f, 0.0f, 1.0f);
            //see what the closest hit is             
            coef = 1.0f;
            level = 0;
            clearPixel(index);
            
            do
            {
                //correction = sqrtf(1/(pow(viewRay.dir.x, 2)  + pow(viewRay.dir.y, 2) + pow(viewRay.dir.z, 2)));
                //viewRay.dir.x *= correction;
                //viewRay.dir.y *= correction;
                //viewRay.dir.z *= correction;
                //if(thisIndex.x == 0 && thisIndex.y == 0) CkPrintf("in while before shoot\n");
                hitIndex = shoot(viewRay, dist);
                if(hitIndex == NEGINF) break;
                if(DEBUG_CODE)
                {
                    CkPrintf("******************************************\n");
                    CkPrintf(" Lucky pixel = [%d, %d] hitindex = %d\n", pixel_x, pixel_y, hitIndex);
                    CkPrintf("level = %d\n", level);
                    CkPrintf("******************************************\n");
                }
                //if(thisIndex.x == 0 && thisIndex.y == 0) CkPrintf("in while before draw\n");
                draw(index, viewRay, hitIndex, dist, coef, level);  
                //if(thisIndex.x == 0 && thisIndex.y == 0) CkPrintf("in while after draw on pixel %d %d, and iteration %d with level %d and coeff %f \n",i,j,iteration, level, coef);
            }
            while((coef > 0.0f) && (level < 10));
            if(EXPOSURE)exposePixel(index);
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
        case TRIANGLE: result = triHit( index, theRay, n); break;
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
}


bool PixelChare::triHit(int index, ray r, float &t)
{
    // triangle hit function
    //CkPrintf("int tri\n");   
    bool one = true,two= true, three = true; 

    //CkPrintf("v1 = {%f, %f, %f} \n", myShapes[index].v1.x, myShapes[index].v1.y, myShapes[index].v1.z);
    //CkPrintf("v0 = {%f, %f, %f} \n", myShapes[index].v0.x, myShapes[index].v0.y, myShapes[index].v0.z);

    //CkPrintf("v2 = {%f, %f, %f} \n", myShapes[index].v2.x, myShapes[index].v2.y, myShapes[index].v2.z);


    vec3D edge1 = myShapes[index].v1 - myShapes[index].v0;
    vec3D edge2 = myShapes[index].v2 - myShapes[index].v0;
    vec3D pvec = cross(r.dir, edge2);
    float det = edge1 * pvec;

    //CkPrintf("det = %f \n", det);

    if (det == 0) 
    {
	//CkPrintf("ray and plane are parallel\n");
        return false; // ray and plane are parallel
    }
    float invDet = 1 / det;
    
    vec3D tvec = r.start - myShapes[index].v0;
    //vec3D tvec = r.start - (myShapes[index].v0 + myShapes[index].loc);
    float u = (tvec * pvec) * invDet;
   
    //CkPrintf("u = %f \n", u);  

    if (u < 0 || u > 1) 
    {
        return false; //out of bounds
    }
    vec3D qvec = cross(tvec, edge1);
    float v = (r.dir * qvec) * invDet;

    //CkPrintf("v = %f and u+v = %f \n", v , v+u);

    if (v < 0 || u + v > 1) 
    {
        return false;//out of bounds
    }
    
	
    t = (edge2*qvec) * invDet;
   // CkPrintf("Tri is true\n");
    return true;

}

void PixelChare::draw(int index, ray &theRay, int hitIndex, float ti, float &coef, int &level)
{
    vec3D newStart = theRay.start + ti * theRay.dir;
    vec3D n; 
    vec3D dist;
    float det;
    float dummy;
    float lambert;
    float magDist;
    ray lightRay;
    
    //figuring out the normal vector at the point of intersection
    if(myShapes[hitIndex].type == TRIANGLE)
    {
        //if(abs(theRay.dir * myShapes[hitIndex].N / mag(theRay.dir)) < COS_ENOUGH)
        //    n = myShapes[hitIndex].N;
        //else n = myShapes[hitIndex].N * -1;

        vec3D edge1 = myShapes[hitIndex].v1 - myShapes[hitIndex].v0;
        vec3D edge2 = myShapes[hitIndex].v2 - myShapes[hitIndex].v0;
        vec3D pvec = cross(theRay.dir, edge2);
	//n = cross(edge1, edge2);
	n = newStart - myShapes[hitIndex].loc;
        //det = n * n;
        //n = cross(edge1, edge2);
	det = edge1 * pvec;
        


        //pixelArray[index].r = 255;
        //pixelArray[index].g = 255;
        //pixelArray[index].b = 255; 
    }
    else 
    {
	n = newStart - myShapes[hitIndex].loc;
        det = n * n;
    }

    if (det == 0.0f)
    {
        level = 10;
        return; // if the ray is parallel with the viewer
    }

    if(myShapes[hitIndex].type == TRIANGLE)
    {
	//det = 1.0f / det;
        //n = det * n;	
    }
    else
    {
    	det = 1.0f / sqrtf(det);
    	n = det * n;
    }

    
    for(int j = 0; j < myLights.size(); ++j)
    {
        lightSrc current = myLights[j];
        dist = current.loc - newStart;
        if(n * dist <= 0.0f) continue; //out of sight
        magDist = mag(dist);
        if (magDist <= 0.0f) continue; // covered
        lightRay.start = newStart;
        lightRay.dir = (1/magDist)*dist;
        if(shoot(lightRay, dummy) == NEGINF)
        {
            lambert = (lightRay.dir * n) * (coef);
            pixelArray[index].r += lambert * current.r * myShapes[hitIndex].red;
            pixelArray[index].g += lambert * current.g * myShapes[hitIndex].green;
            pixelArray[index].b += lambert * current.b * myShapes[hitIndex].blue;
	    
	    //pixelArray[index].r += current.r * myShapes[hitIndex].red;
            //pixelArray[index].g += current.g * myShapes[hitIndex].green;
            //pixelArray[index].b += current.b * myShapes[hitIndex].blue;


            if(DEBUG_CODE) 
            {
                //CkPrintf("current lightray.dir = %f, n = %f coef = %f", lightRay.dir, n, coef);
                CkPrintf("lambert = %f   current(%f,%f,%f)\n", lambert, current.r, current.g, current.b);
                CkPrintf("hitindex = %d shape.color(%f,%f,%f)\n", hitIndex, myShapes[hitIndex].red, myShapes[hitIndex].green, myShapes[hitIndex].blue);
                CkPrintf("pixelarray(%f,%f,%f\n",pixelArray[index].r,pixelArray[index].g,pixelArray[index].b);
                //myShapes[hitIndex].print();
                //CkAssert(lambert <= 1);
            }
        }
    }
	
    if (pixelArray[index].r == 0 && pixelArray[index].b == 0 && pixelArray[index].g == 0)
    {        
    	//CkPrintf("pixelarray[%d] = %f, %f, %f \n", index, pixelArray[index].r, pixelArray[index].g, pixelArray[index].b);
    }

    //CkAssert(pixelArray[index].r == 0 && pixelArray[index].b == 0 && pixelArray[index].g == 0); 

    float reflect = 2.0f * (theRay.dir * n);
    //modify return vars
    coef *= myShapes[hitIndex].reflection;
    theRay.start = newStart;
    theRay.dir = theRay.dir - reflect * n;   
    level++; 
}

void PixelChare::liveVizFunc(liveVizRequestMsg *m) 
{        
    rgb_byte* imageBuff = (rgb_byte*)tmpBuffer;
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
	if((x+thisIndex.x * w) == 100 && (y+ thisIndex.y*h)== 400) 
	{
		c->r= 0;c->g = 0; c->b = 255;
	}
        }
    }

    liveVizDeposit(m, thisIndex.x * w, thisIndex.y * h,
                    w, h, (byte*)(imageBuff), this);
}
#include "pixelchare.def.h" 
