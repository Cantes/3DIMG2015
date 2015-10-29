#include <iostream>
#include "CImg.h"
#include "Snap.h"
#include "Point.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "include\vectorOps.h"


using namespace std;
using namespace cimg_library;


double Factoriel(double n)
{
    double ret = 1;

    for(int i = 1 ; i < n +1;i++)
        ret = ret * (double)i;
    return ret;
}

double PolyBernstein(double n,double i, double u)
{
    double ret;
    ret = ((double)Factoriel(n))/(((double)Factoriel(i))*((double)Factoriel(n-i)))*pow(u,i)*pow((1.0-u),n-i);
    return ret;
}

vector<Snap*>* BezierCurveByBernstein(Point* tabControl,vector<Snap*>* ret, long nbCP , long nbU)
{
    Snap* current;


   // double f1, f2 , f3 , f4;
    long i = 0;

    for(long i = 0; i < nbU ; i++)
    {
        current = new Snap();
        current->n = i;
        current->position[0] = 0;
        current->position[1] = 0;
        current->position[2] = 0;

        for(long j = 0; j < nbCP ; j++)
        {

            current->position[0] += (PolyBernstein(nbCP - 1, j, (double)i / (double)(nbU-1))*tabControl[j].GetX());
            current->position[1] += (PolyBernstein(nbCP - 1, j, (double)i / (double)(nbU-1))*tabControl[j].GetY());
            current->position[2] += (PolyBernstein(nbCP - 1, j, (double)i / (double)(nbU-1))*tabControl[j].GetZ());

        }
        //cout<<current->position[0] <<" \t"<<current->position[1] <<" \t"<<current->position[2] <<endl;
        ret->push_back(current);
    }
    return ret;
}

void doubleReflectionAlgorithm(Snap* prev,Snap* cur)
{
    double v1[3];
    double v2[3];
    double c1;
    double c2;
    double rl[3];
    double tl[3];

    subVectors(cur->position,prev->position,v1);
    c1 = dotProduct(v1,v1);
    ///rl
    multVector((-2.0/c1)*dotProduct(v1,prev->up),v1,rl);
    addVectors(prev->up,rl,rl);
    ///tl
    multVector((-2.0/c1)*dotProduct(v1,prev->direction),v1,tl);
    addVectors(prev->direction,tl,tl);
    ///v2
    subVectors(cur->direction,tl,v2);
    c2 = dotProduct(v2,v2);
    /// nouveau up
    multVector((-2.0/c2)*dotProduct(v2,rl),v2,cur->up);
    addVectors(rl,cur->up,cur->up);
    crossProduct(cur->direction,cur->up,cur->cross);
}

vector<Snap*>* makeJobListFromFile(char* filePath)
{
    vector<Snap*>* ret = new vector<Snap*>();
    Snap* current;
    Snap* previous = NULL;
    ifstream infile(filePath);
    string line;
    int i = 0;
    int sizeCp = 0;
    double x,y,z;

    getline(infile, line);
    istringstream streamLine(line);
    streamLine >> sizeCp;
    Point* tabControl = new Point[sizeCp];
    while (getline(infile, line))
    {
        istringstream streamLine(line);
        if(!(streamLine >> x>> y>> z))
        {
            cout<<"endfile"<<endl;
            break;
        }
        tabControl[i].SetX(x*10);
        tabControl[i].SetY(y*10);
        tabControl[i].SetZ(z*10);
        i++;
    }
    infile.close();
    ret = BezierCurveByBernstein(tabControl,ret,sizeCp,200);
    free(tabControl);

    for(int j = 0 ; j < ret->size()-1 ; j++)
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            ret->at(j)->direction[i] = ret->at(j+1)->position[i] - ret->at(j)->position[i];
        }
        ret->at(j)->normalize(ret->at(j)->direction);
        //cout<<ret->at(j)->direction[0] <<" \t"<<ret->at(j)->direction[1] <<" \t"<<ret->at(j)->direction[2] <<endl;
    }
    for(int i = 0 ; i < 3 ; i++)
    {
        ret->back()->direction[i] = ret->at(ret->size()-2)->direction[i];
    }

    ret->at(0)->up[0] = -1.0;
    ret->at(0)->up[0] = 1.0;
    ret->at(0)->up[0] = 1.0;
    ret->at(0)->initFirstSnap();

    for(int j = 0 ; j < ret->size()-1 ; j++)
    {
        doubleReflectionAlgorithm(ret->at(j),ret->at(j+1));
    }
    for(int i = 0 ; i < 3 ; i++)
    {
        ret->back()->up[i] = ret->at(ret->size()-2)->up[i];
        ret->back()->cross[i] = ret->at(ret->size()-2)->cross[i];
    }

    return ret;
}

int main()
{
    CImg<unsigned short> *image = new CImg<unsigned short>();
    CImg<unsigned short> *imageResult;
    float voxtabsize[3];
    vector<Snap*>* jobList;
    int maxCoord = 0;

    cout << "Hello trajectory!" << endl;

    image->load_analyze("cochlee_resample.img", voxtabsize);
    jobList = makeJobListFromFile("landmarks.ldk");

    maxCoord = max(image->width(),max(image->height(),image->depth()));
    imageResult = new CImg<unsigned short>(maxCoord,maxCoord,jobList->size());
    for(int i = 0 ; i < jobList->size();i++)
    {
        jobList->at(i)->work(image,imageResult);
        free(jobList->at(i));
    }
    free(jobList);
    imageResult->save_analyze("result.img");
    return 0;
}
