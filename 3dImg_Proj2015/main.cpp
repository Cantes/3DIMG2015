#include <iostream>
#include "CImg.h"
#include "Snap.h"
#include "Point.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "include\vectorOps.h"
#include "include\PathRenderer.h"

using namespace std;
using namespace cimg_library;

int main()
{
    PathRenderer pr;

    pr.SetinImgFilePath("cochlee_resample.img");
    pr.SetoutImgFilePath("renderOut.img");
    pr.SetinPointsFilePath("landmarks.ldk");
    pr.SetstepCount(200);
    pr.SetpathInterpolationMethod(INTERP_BEZIER);
    pr.SetSortPoints(true);

    pr.render();

    return 0;
}
