#include "PathRenderer.h"

PathRenderer::PathRenderer()
{
    //ctor
}

PathRenderer::~PathRenderer()
{
    //dtor
}


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


double hermiteF1(double u)
{
    return (2.0*u*u*u) - (3.0 * u * u ) + 1.0;
}
double hermiteF2(double u)
{
    return -(2.0*u*u*u) + (3.0 * u * u );
}
double hermiteF3(double u)
{
    return (u*u*u) - (2.0 * u * u ) + u;
}
double hermiteF4(double u)
{
    return (u*u*u) - (u * u );
}

void makeHermitVector(Point *result,Point *prev,Point *cur,Point *next)
{
    double vect[3];
    double dist[3];

    if(prev != NULL && next != NULL)
    {
        vect[0] = next->GetX()-prev->GetX();
        vect[1] = next->GetY()-prev->GetY();
        vect[2] = next->GetZ()-prev->GetZ();
        normalized(vect);
        dist[0] = next->GetX()-cur->GetX();
        dist[1] = next->GetY()-cur->GetY();
        dist[2] = next->GetZ()-cur->GetZ();
        multVector(norm(dist)/3.0,vect,vect);
        result->SetX(vect[0]);
        result->SetY(vect[1]);
        result->SetZ(vect[2]);

    }else
    {
        if(prev == NULL)
        {
            result->SetX(next->GetX()-cur->GetX()/3.0);
            result->SetY(next->GetY()-cur->GetY()/3.0);
            result->SetZ(next->GetZ()-cur->GetZ()/3.0);
        }
        else
        {
            result->SetX(cur->GetX()-prev->GetX()/3);
            result->SetY(cur->GetY()-prev->GetY()/3);
            result->SetZ(cur->GetZ()-prev->GetZ()/3);
        }
    }
}

vector<Snap*>* HermiteCubicCurve(Point p1,Point p2, Point v1 , Point v2, long nbU,vector<Snap*>* ret, long *number)
{
    Snap* current;
    double f1, f2 , f3 , f4;
    long i = 0;

    for(long i = 0; i < nbU ; i++)
    {
        current = new Snap();
            f1 = hermiteF1(((double)i)/(((double)nbU)-1.0));
            f2 = hermiteF2(((double)i)/(((double)nbU)-1.0));
            f3 = hermiteF3(((double)i)/(((double)nbU)-1.0));
            f4 = hermiteF4(((double)i)/(((double)nbU)-1.0));
       current->position[0] =(f1*p1.GetX()+f2*p2.GetX()+f3*v1.GetX()+f4*v2.GetX());
       current->position[1] =(f1*p1.GetY()+f2*p2.GetY()+f3*v1.GetY()+f4*v2.GetY());
       current->position[2] =(f1*p1.GetZ()+f2*p2.GetZ()+f3*v1.GetZ()+f4*v2.GetZ());
       current->n = *number;
       if(ret->size() == 0 || (ret->size() > 0 && (ret->back()->position[0] != current->position[0] ||ret->back()->position[1] != current->position[1] ||ret->back()->position[2] != current->position[2])))
       {
            (*number)++;
            //cout<< tab[i].GetX() << " - "<< tab[i].GetY() << " - "<< tab[i].GetZ() << endl;
            ret->push_back(current);
       }
       else{
        free(current);
       }
    }
    return ret;
}

vector<Snap*>* hermit(Point* tabControl,vector<Snap*>* ret,long nCp, long nbU)
{
    long cnt = 0;
    double norm1 = 0;
    double currentNorm = 0;
    double vect[3];
    Point v1,v2;
    for(long i = 0; i < nCp-1 ; i++)
    {
        vect[0] = tabControl[i+1].GetX() - tabControl[i].GetX();
        vect[1] = tabControl[i+1].GetY() - tabControl[i].GetY();
        vect[2] = tabControl[i+1].GetZ() - tabControl[i].GetZ();
        norm1 += norm(vect);
    }

    for(long i = 0; i < nCp - 1; i++)
    {
        vect[0] = tabControl[i+1].GetX() - tabControl[i].GetX();
        vect[1] = tabControl[i+1].GetY() - tabControl[i].GetY();
        vect[2] = tabControl[i+1].GetZ() - tabControl[i].GetZ();
        currentNorm = norm(vect);
        makeHermitVector(&v1,i>0?&tabControl[i-1]:NULL,&tabControl[i],&tabControl[i+1]);
        makeHermitVector(&v2,i<nCp-2?&tabControl[i+2]:NULL,&tabControl[i+1],&tabControl[i]);
        ret = HermiteCubicCurve(tabControl[i],tabControl[i+1],v1,v2
                                ,max(2,(int)((currentNorm/norm1) * nbU))
                                ,ret,&cnt);
    }
    return ret;
}

vector<Snap*>* direct(Point* tabControl,vector<Snap*>* ret,long nCp)
{
     Snap* current;

    for(long i = 0; i < nCp-1 ; i++)
    {

        current = new Snap();
        current->position[0] =tabControl[i].GetX();
        current->position[1]  =tabControl[i].GetY();
        current->position[2] =tabControl[i].GetZ();
        current->n = i;
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

void sortPoints(Point* tabControl,int ncp)
{
    Point temp;
    double selNorm = 0;
    int selJ;
    double vect[3];
    for(int i =0 ; i < ncp ; i++)
    {
        selJ = i+1;
        selNorm = 0;
        for(int j = i+1; j<ncp;j++)
        {
            vect[0] = tabControl[j].GetX()-tabControl[i].GetX();
            vect[1] = tabControl[j].GetY()-tabControl[i].GetY();
            vect[2] = tabControl[j].GetZ()-tabControl[i].GetZ();
            if(selNorm ==0 || norm(vect) < selNorm)
            {
                selNorm = norm(vect);
                selJ = j;
            }
        }
        if(selJ != i+1)
        {
            temp.setPoint(&tabControl[selJ]);
            tabControl[selJ].setPoint(&tabControl[i+1]);
            tabControl[i+1].setPoint(&temp);
        }
    }
}

vector<Snap*>* makeJobListFromFile(string filePath, int interpMethod, bool doSortPoint, int nPoints)
{
    vector<Snap*>* ret = new vector<Snap*>();
    Snap* current;
    Snap* previous = NULL;
    ifstream infile(filePath.c_str());
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
            break;
        }
        tabControl[i].SetX(x*1);
        tabControl[i].SetY(y*1);
        tabControl[i].SetZ(z*1);
        i++;
    }
    infile.close();
    if(doSortPoint)
        sortPoints(tabControl,sizeCp);
    switch(interpMethod){
    case INTERP_DIRECT:
        {
            ret = direct(tabControl,ret,sizeCp);
            break;
        }
    case INTERP_BEZIER:
        {
            ret = BezierCurveByBernstein(tabControl,ret,sizeCp,nPoints);
            break;
        }
    case INTERP_HERMIT:
        {
            ret = hermit(tabControl,ret,sizeCp,nPoints);
            break;
        }
    }
    free(tabControl);
    for(int j = 0 ; j < ret->size()-1 ; j++)
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            ret->at(j)->direction[i] = ret->at(j+1)->position[i] - ret->at(j)->position[i];
        }
        ret->at(j)->normalize(ret->at(j)->direction);
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

void printMarks( vector<Snap*>* jobList, string outPath)
{
    ofstream file;
    file.open (outPath.c_str());
    file << "# frame 0"<<endl;
    for(int i =0 ; i < jobList->size(); i++)
    {
        file << "\"point"<< i+1 <<"\": [ "<<jobList->at(i)->position[0]<<","<<jobList->at(i)->position[1]<<","<<jobList->at(i)->position[2]<<"]"<<endl;
    }
    file.close();
}

bool PathRenderer::render()
{
    CImg<unsigned short> *imageResult;
    vector<Snap*>* jobList;
    int maxCoord = 0;

    jobList = makeJobListFromFile(inPointsFilePath.c_str(),GetpathInterpolationMethod(),GetSortPoints(),GetstepCount());
    maxCoord = max(sourceImage->width(),max(sourceImage->height(),sourceImage->depth()));
    imageResult = new CImg<unsigned short>(maxCoord/2,maxCoord/2,jobList->size());
    if(outputPath)
        printMarks(jobList, outPointsFilePath);
    for(int i = 0 ; i < jobList->size();i++)
    {
        jobList->at(i)->work(sourceImage,imageResult,voxtabsize);
        free(jobList->at(i));
    }
    free(jobList);
    imageResult->save_analyze(outImgFilePath.c_str());
    return true;
}

void PathRenderer::SetinImgFilePath(string val)
{
    inImgFilePath = val;
    if(sourceImage != 0)
        delete sourceImage;
    sourceImage = new CImg<unsigned short>();
    sourceImage->load_analyze(inImgFilePath.c_str(),voxtabsize);
}

