#include <iostream>
#include "CImg.h"
#include "Snap.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using namespace cimg_library;



vector<Snap*>* makeJobListFromFile(char* filePath)
{
    vector<Snap*>* ret = new vector<Snap*>();
    Snap* current;
    Snap* previous = NULL;
    ifstream infile(filePath);
    string line;
    getline(infile, line);
    int i = 0;

    while (getline(infile, line))
    {
        current = new Snap();
        current->n = i;
        i++;
        istringstream streamLine(line);
        if(!(streamLine >> current->position[0]>> current->position[1]>> current->position[2]))
        {
            cout<<"endfile"<<endl;
            free(current);
            break;
        }
        if(ret->size()>0)
        {
            for(int i = 0 ; i < 3 ; i++)
            {
                ret->back()->direction[i] = current->position[i] - ret->back()->position[i];
            }
        }
        current->previous = previous;
        previous = current;
        ret->push_back(current);
    }
    for(int i = 0 ; i < 3 ; i++)
    {
        ret->back()->direction[i] = ret->at(ret->size()-2)->direction[i];
    }
    infile.close();
    ret->at(0)->up[0] = 0.0;
    ret->at(0)->up[0] = 1.0;
    ret->at(0)->up[0] = 0.0;
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
    imageResult = new CImg<unsigned short>(maxCoord/2,maxCoord/2,jobList->size());
    for(int i = 0 ; i < jobList->size();i++)
    {
        jobList->at(i)->work(image,imageResult);
        free(jobList->at(i));
    }
    free(jobList);
    imageResult->save_analyze("result.img");
    return 0;
}
