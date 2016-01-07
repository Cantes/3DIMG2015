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

#define VOX_INTERP_LINEAR 0
#define VOX_INTERP_CUBIC 1

using namespace std;

class PathRenderer
{
    public:
        PathRenderer();
        virtual ~PathRenderer();
        int GetpathInterpolationMethod() { return pathInterpolationMethod; }
        void SetpathInterpolationMethod(int val) { pathInterpolationMethod = val; }
        int GetVoxelInterpolationMethod() { return voxelInterpolation; }
        void SetVoxelInterpolationMethod(int val) { voxelInterpolation = val; }
        int GetoutX() { return outX; }
        void SetoutX(int val) { outX = val;}
        int GetoutY() { return outY; }
        void SetoutY(int val) { outY = val; }
        float GetstepLength() { return stepLength; }
        void SetstepLength(float val) { stepLength = val; }
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
        bool renderToFile();
        CImg<unsigned short> *render();

    protected:
    private:
        float voxtabsize[3];
        CImg<unsigned short> *sourceImage = 0;
        int pathInterpolationMethod = 0;
        int voxelInterpolation = 0;
        bool outputPath = false;
        bool doSortPoints = false;
        string inImgFilePath;
        string outImgFilePath;
        string inPointsFilePath;
        string outPointsFilePath;
        double stepSize;
        int stepCount;
        int outX = 0;
        int outY = 0;
        float stepLength = 0.0;
};

#endif // PATHREDERER_H
