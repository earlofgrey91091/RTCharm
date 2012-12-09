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
    


    if(ANTI_ALIASING) {
    for(int j = 0; j < w; j++) 
    {
        for(int i = 0; i < h; i++) 
        {
            
            
            index = (j * w) + i;
            pixel_x = position_x + i;
            pixel_y = position_y + j;
            float red = 0, green = 0, blue = 0;
            for(float fragmentx = pixel_x; fragmentx < pixel_x + 1.0f; fragmentx += 0.5f)
            {
                for(float fragmenty = pixel_y; fragmenty < pixel_y + 1.0f; fragmenty += 0.5f)
                {
                    ray viewRay(float(fragmentx), float(fragmenty),-1000.0f, 0.0f, 0.0f, 1.0f);
            		coef = 1.0f;
                    float sampleRatio=0.25f;
            		level = 0;
            		pixelArray[index].r = 0;
            		pixelArray[index].g = 0;
            		pixelArray[index].b = 0;
            		do
            		{
                		hitIndex = shoot(viewRay, dist);
                
                		if(hitIndex == NEGINF) break;
                		if(DEBUG_CODE)
                		{
                    			CkPrintf("******************************************\n");
                    			CkPrintf(" Lucky pixel = [%d, %d] hitindex = %d\n", pixel_x, pixel_y, hitIndex);
                    			CkPrintf("level = %d\n", level);
                    			CkPrintf("******************************************\n");
                		}
                		draw(index, viewRay, hitIndex, dist, coef, level); 
                    } while((coef > 0.0f) && (level < 10));
                    if(EXPOSURE){
                        float exposure = -1.00f;
                        pixelArray[index].r = (1.0f - expf(pixelArray[index].r * exposure));
                        pixelArray[index].g = (1.0f - expf(pixelArray[index].g * exposure));
                        pixelArray[index].b = (1.0f - expf(pixelArray[index].b * exposure));
                    }
                    pixelArray[index].r += pixelArray[index].r * sampleRatio;
                    pixelArray[index].g += pixelArray[index].g * sampleRatio;
                    pixelArray[index].b += pixelArray[index].b * sampleRatio;
                }
            }

        }
    }
    }


    else {
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
                		if(hitIndex == NEGINF) break;
                		if(DEBUG_CODE)
                		{
                    			CkPrintf("******************************************\n");
                    			CkPrintf(" Lucky pixel = [%d, %d] hitindex = %d\n", pixel_x, pixel_y, hitIndex);
                    			CkPrintf("level = %d\n", level);
                    			CkPrintf("******************************************\n");
                		}
                		draw(index, viewRay, hitIndex, dist, coef, level); // this is wrong for multipl.e levels we should have DIFFRENT RAYS
            		}
            		while((coef > 0.0f) && (level < 10));
                if(EXPOSURE){
                    float exposure = -1.00f;
                    pixelArray[index].r = (1.0f - expf(pixelArray[index].r * exposure));
                    pixelArray[index].g = (1.0f - expf(pixelArray[index].g * exposure));
                    pixelArray[index].b = (1.0f - expf(pixelArray[index].b * exposure));
                }

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
    // check if parallel
    
    float NdotRayDirection = myShapes[index].N * r.dir; 
    if (NdotRayDirection == 0) return false; 

    float d = myShapes[index].N * myShapes[index].v0; 

    t = -(myShapes[index].N*r.start + d) / NdotRayDirection; 
    if(t < 0) return false; // triangle is behind

    // compute the intersection point using equation 1 
    vec3D P = r.start + t * r.dir;

    // // Step 2: inside-outside test // 
    vec3D C; // vector perpendicular to triangle's plane 
    // edge 0 
    vec3D edge0 = myShapes[index].v1 - myShapes[index].v0; 
    vec3D VP0 = P - myShapes[index].v0; 
    C = cross(edge0, VP0); 
    if (myShapes[index].N * C < 0) return false; // P is outside 
    // edge 1 
    vec3D edge1 = myShapes[index].v2 - myShapes[index].v1; 
    vec3D VP1 = P - myShapes[index].v1; 
    C = cross(edge1, VP1); 
    if (myShapes[index].N * C < 0) return false; // P is outside 
    // edge 2 
    vec3D edge2 = myShapes[index].v0 -myShapes[index].v2; 
    vec3D VP2 = P - myShapes[index].v2; 
    C = cross(edge2, VP2); 
    if (myShapes[index].N * C < 0) return false; // P is outside 
    return true; 
}

void PixelChare::draw(int index, ray &theRay, int hitIndex, float ti, float &coef, int &level)
{
    vec3D newStart = theRay.start + ti * theRay.dir;
    vec3D n; 
    //figuring out the normal vector at the point of intersection
    if(false)//myShapes[hitIndex].type == TRIANGLE)
    {
        //if
    }
    else n = newStart - myShapes[hitIndex].loc;
    float temp = n * n;
    float dummy;
    float lambert;

    
    
    if (temp == 0.0f) return;

    temp = 1.0f / sqrtf(temp);
    n = temp * n;

    
    for(int j = 0; j < myLights.size(); ++j)
    {
        lightSrc current = myLights[j];
        vec3D dist = current.loc - newStart;

        if(n * dist <= 0.0f) continue;

        float t = sqrtf(dist * dist);
        if (t <= 0.0f) continue;
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
                //CkPrintf("current lightray.dir = %f, n = %f coef = %f", lightRay.dir, n, coef);
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
        }
    }

    liveVizDeposit(m, thisIndex.x * w, thisIndex.y * h,
                    w, h, (byte*)(imageBuff), this);
}
#include "pixelchare.def.h" 
