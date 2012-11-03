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
        void startVis();
    private:
        CProxy_PixelChare pixel;
        CkArrayOptions myOpts;
        
};

#endif //MAIN_H 


