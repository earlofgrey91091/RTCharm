#ifndef PIXELCHARE_H
#define PIXELCHARE_H
#include <pup_stl.h>

class PixelChare : public CBase_PixelChare 
{
    private:
    typedef struct { byte r, g, b; } rgb;
    vector<rgb> pixelArray;
    double *tmpBuffer;
    int x, y, w, h;
    int iteration;

    public:
    PixelChare_SDAG_CODE;    
    PixelChare(int width, int height); 
    PixelChare(CkMigrateMessage *m);
    ~PixelChare(); 
    void doWork();
    void liveVizDump(liveVizRequestMsg *m); 


};

#endif //PIXELCHARE_H 
