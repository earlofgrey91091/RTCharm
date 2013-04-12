#ifndef MAIN_H
#define MAIN_H
#include "pup_stl.h"
#include "main.decl.h"
#include "pixelchare.decl.h"

class Main : public CBase_Main {
    public:
        Main_SDAG_CODE;
        Main(CkArgMsg* msg);
        Main(CkMigrateMessage *msg);
        //void done();
        void startVis();
        CProxy_PixelChare pixel;
        CkArrayOptions myOpts;
    private:
        int count;
        int iterations;
        int chareDimension;
        int numShapes;
        int image_w;
        int image_h;
        vector<Shape> myShapes;
        vector<Shape> sendShape;
        vector<vec3d> shapeDirection;
        vector<lightSrc> myLights;
        void rotateLights();
        
        
        
};

#endif //MAIN_H 


