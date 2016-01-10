#include <iostream>
#include "CImg.h"
#include "include/Snap.h"
#include "include/Point.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "include/vectorOps.h"
#include "include/PathRenderer.h"

using namespace std;
using namespace cimg_library;

int main(int argc,  char** argv){

	if(argc != 4){
		std::cout << "Syntax incorrect img_name VOX_INTERP_TYPE( 0 = Linear, 1 = Cubic  ) INTERP_TYPE( 0 = Direct, 1 = Bezier, 2 = Hermit )" << std::endl;
		exit(0);
	}
    PathRenderer pr;

    pr.SetinImgFilePath(argv[1]);

///fichier sortie
    pr.SetoutImgFilePath("renderOut.img");
/// fichiers points source
    pr.SetinPointsFilePath("landmarks.ldk");

/// écrire les points iterpolé et nom du fichier
    pr.SetoutPointsFilePath("testTraj.points");
    pr.SetoutputPath(true);

/// nombre de pas : si step length != 0 --> utilise step length en prio , sinon utilise setp count
    //pr.SetstepCount(500);
    pr.SetstepLength(0.05);

/// taille sortie X et Y
    pr.SetoutX(200);
    pr.SetoutY(200);

/// type d'interpolation des voxels

/// VOX_INTERP_LINEAR 0
/// VOX_INTERP_CUBIC 1
	
	if(atoi(argv[2]) == 1){
		pr.SetVoxelInterpolationMethod(VOX_INTERP_CUBIC);
	}else{
		pr.SetVoxelInterpolationMethod(VOX_INTERP_LINEAR);
	}


/// type interpolation chemin
/// INTERP_DIRECT 0
/// INTERP_BEZIER 1
/// INTERP_HERMIT 2

	if(atoi(argv[3]) == 0){
		pr.SetpathInterpolationMethod(INTERP_DIRECT);
	}else if(atoi(argv[3]) == 2){
		pr.SetpathInterpolationMethod(INTERP_HERMIT);
	}else{
		pr.SetpathInterpolationMethod(INTERP_BEZIER);
	}


/// trier les poitns par distance euclidienne
    pr.SetSortPoints(true);

   pr.renderToFile();

    return 0;
}
