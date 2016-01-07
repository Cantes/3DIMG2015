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
///CHOIX DE LA SOURCE
//DICOMS_cochlee_specimen_02_0.03.img
//    pr.SetinImgFilePath("analyse_cochlee_specimen_02_0.02.img");
    pr.SetinImgFilePath("DICOMS_cochlee_specimen_02_0.03.img");
//    pr.SetinImgFilePath("cochlee_resample.img");
/// ////////////

///fichier sortie
    pr.SetoutImgFilePath("renderOut.img");
/// fichiers points source
    pr.SetinPointsFilePath("landmarks.ldk");

/// écrire les points iterpolé et nom du fichier
    pr.SetoutPointsFilePath("testTraj.points");
    pr.SetoutputPath(true);
///

/// nombre de pas : si step length != 0 --> utilise step length en prio , sinon utilise setp count
    //pr.SetstepCount(500);
    pr.SetstepLength(0.05);
/////

/// taille sortie X et Y
    pr.SetoutX(200);
    pr.SetoutY(200);
///

/// type d'interpolation des voxels

/// VOX_INTERP_LINEAR 0
/// VOX_INTERP_CUBIC 1

    pr.SetVoxelInterpolationMethod(VOX_INTERP_LINEAR);
///

/// type interpolation chemin
/// INTERP_DIRECT 0
/// INTERP_BEZIER 1
/// INTERP_HERMIT 2

    pr.SetpathInterpolationMethod(INTERP_BEZIER);
///

/// trier les poitns par distance euclidienne
    pr.SetSortPoints(true);
///

    pr.renderToFile();

    return 0;
}
