#ifndef PATHRENDERER_H
#define PATHRENDERER_H

#include <cstddef>
#include <iostream>
#include "..\CImg.h"
#include "Snap.h"
#include "Point.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "vectorOps.h"

#define INTERP_DIRECT 0
#define INTERP_BEZIER 1
#define INTERP_HERMIT 2

using namespace std;

class PathRenderer
{
    public:
        PathRenderer();
        virtual ~PathRenderer();
        int GetpathInterpolationMethod() { return pathInterpolationMethod; }
        void SetpathInterpolationMethod(int val) { pathInterpolationMethod = val; }
        bool GetoutputPath() { return outputPath; }
        void SetoutputPath(bool val) { outputPath = val; }
        bool GetSortPoints() { return doSortPoints; }
        void SetSortPoints(bool val) { doSortPoints = val; }
        string GetinImgFilePath() { return inImgFilePath; }
        void SetinImgFilePath(string val);
        string GetoutImgFilePath() { return outImgFilePath; }
        void SetoutImgFilePath(string val) { outImgFilePath = val; }
        string GetinPointsFilePath() { return inPointsFilePath; }
        void SetinPointsFilePath(string val) { inPointsFilePath = val; }
        string GetoutPointsFilePath() { return outPointsFilePath; }
        void SetoutPointsFilePath(string val) { outPointsFilePath = val; }
        double GetstepSize() { return stepSize; }
        void SetstepSize(double val) { stepSize = val; }
        int GetstepCount() { return stepCount; }
        void SetstepCount(int val) { stepCount = val; }
        bool render();

    protected:
    private:
        float voxtabsize[3];
        CImg<unsigned short> *sourceImage = 0;
        int pathInterpolationMethod = 0;
        bool outputPath = false;
        bool doSortPoints = false;
        string inImgFilePath;
        string outImgFilePath;
        string inPointsFilePath;
        string outPointsFilePath;
        double stepSize;
        int stepCount;
};

#endif // PATHREDERER_H
