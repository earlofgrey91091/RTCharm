#include <stdio.h>
#include "RTCharm.decl.h"
#define ITERATIONS 1000

/*readonly*/ CProxy_Main mainProxy;
/*readonly*/ int Total_iterations;
class Main : public CBase_Main {
public:
  CProxy_PixelChare pixel;
  Main(CkArgMsg* arg) {
    int image_l = 0, image_b = 0;
    char *objectsFileName;
    //Process command-line arguments
    if( arg->argc > 0 )
    { 
	image_l = atoi(arg->argv[0]);
	image_b = atoi(arg->argv[1]);
	printf("\n l = %d, b = %d", image_l, image_b);
    }
    else
    {
	CkPrintf("Invalid number of arguments\n");
	CkExit();
    }
    delete arg;
    Total_iterations = ITERATIONS;
    //TODO: Read file and create shape objects
    
    //Create the image pixel chares based on image size
    pixel = CProxy_PixelChare::ckNew(image_l, image_b);
   
    //Run!
    //
    //
    CkPrintf("\n");
    CkExit();
  };
};

/*array [2D]*/
class PixelChare : public CBase_PixelChare {
public:
PixelChare_SDAG_CODE

int x, y;
int iteration;
PixelChare(void) {
__sdag_init();
iteration = 0;
};


PixelChare(CkMigrateMessage *m)
{
__sdag_init();
};


};

#include "RTCharm.def.h"
