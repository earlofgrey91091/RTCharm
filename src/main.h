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
        vector<lightSrc> myLights;
        Main(CkArgMsg* msg);
        Main(CkMigrateMessage *msg);
        //void done();
        void startVis();
        CProxy_PixelChare pixel;
        CkArrayOptions myOpts;
    private:
        
        
};

#endif //MAIN_H 


