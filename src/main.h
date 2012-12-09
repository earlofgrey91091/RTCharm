#ifndef MAIN_H
#define MAIN_H
#include "pup_stl.h"
#include "main.decl.h"
#include "pixelchare.decl.h"

class Main : public CBase_Main {
    public:
        Main_SDAG_CODE;
        int count;
        int iterations;
        vector<Shape> myShapes;
        vector<Shape> emptyVec;
        vector<Direction> shapeDirection;
        vector<lightSrc> myLights;
        Main(CkArgMsg* msg);
        Main(CkMigrateMessage *msg);
        //void done();
        void startVis();
        CProxy_PixelChare pixel;
        CkArrayOptions myOpts;
    private:
        void rotateLights();
        
        
};

#endif //MAIN_H 


