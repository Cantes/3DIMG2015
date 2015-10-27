#include "Snap.h"

Snap::Snap()
{
   previous = NULL;
}

void crossProduct(double v1[3],double v2[3],double v3[3])
{
    v3[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v3[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v3[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

void addVectors(double v1[3],double v2[3],double v3[3])
{
    v3[0] = v1[0]+v2[0];
    v3[1] = v1[1]+v2[1];
    v3[2] = v1[2]+v2[2];
}

void multVector(double n,double v2[3],double v3[3])
{
    v3[0] = n*v2[0];
    v3[1] = n*v2[1];
    v3[2] = n*v2[2];
}

void normalize(double v1[3])
{
    double norm = sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]);
    v1[0]/=norm;v1[1]/=norm;v1[2]/=norm;
}



void showVector(double v1[3])
{
    cout<<v1[0]<<"\t"<<v1[1]<<"\t"<<v1[2]<<endl;
}

void Snap::showVectors()
{
    cout<<"vectors for "<<n<<endl<<"direction :\t";
    showVector(direction);
    cout<<"up :\t\t";
    showVector(up);
    cout<<"cross :\t\t";
    showVector(cross);
    cout<<endl;
}




int Snap::work(CImg<unsigned short> *imageSource,CImg<unsigned short> *imageResult)
{
    double point[3];
    double xComp[3];
    double yComp[3];


    if(previous != NULL)
        for(int i =0 ; i < 3 ;i++)
            up[i] = previous->up[i];

    normalize(direction);normalize(up);
    crossProduct(direction,up,cross);
    crossProduct(cross,direction,up);
    normalize(direction);normalize(up);normalize(cross);


    for(int x = 0; x < imageResult->width();x++)
    {
        multVector((double)(-(imageResult->width()/2) + x),cross,xComp);
        for(int y = 0; y < imageResult->height();y++)
        {
            multVector((double)(imageResult->height()/2 - y),up,yComp);
            addVectors(xComp,yComp,point);
            addVectors(position,point,point);
            (*imageResult)(x,y,n,0) = imageSource->linear_atXYZ(point[0],point[1],point[2]);
        }
    }

    return 0;
}


Snap::~Snap()
{
    //dtor
}

