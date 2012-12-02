#ifndef MAIN_H
#define MAIN_H
#include "pup_stl.h"
#include "main.decl.h"
#include "pixelchare.decl.h"

class Main : public CBase_Main {
    public:
        //Main_SDAG_CODE;
        vector<Shape> myShapes;
        vector<lightSrc> myLights;
        Main(CkArgMsg* msg);
        Main(CkMigrateMessage *msg);
        void done();
        void startVis();
    private:
        CProxy_PixelChare pixel;
        CkArrayOptions myOpts;
        
};

#endif //MAIN_H 


