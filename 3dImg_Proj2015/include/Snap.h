#ifndef SNAP_H
#define SNAP_H
#include "../CImg.h"
#include <iostream>



using namespace std;
using namespace cimg_library;

class Snap
{
    public:
        Snap();
        virtual ~Snap();
        double position[3];
        double direction[3];
        double up[3];
        double cross[3];
        Snap* previous;
        int n;
        void showVectors();
        void normalize(double v1[3]);
        void initFirstSnap();
        int work(CImg<unsigned short> *imageSource,CImg<unsigned short> *imageResult);
    protected:
};
#endif // SNAP_H
