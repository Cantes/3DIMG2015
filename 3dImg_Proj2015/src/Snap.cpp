#include "Snap.h"
#include "..\include\vectorOps.h"

Snap::Snap()
{
   previous = NULL;
}

void Snap::normalize(double v1[3])
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

void Snap::initFirstSnap()
{
    normalize(direction);normalize(up);
    crossProduct(direction,up,cross);
    crossProduct(cross,direction,up);
    normalize(direction);normalize(up);normalize(cross);
}

int Snap::work(CImg<unsigned short> *imageSource,CImg<unsigned short> *imageResult)
{
    double point[3];
    double xComp[3];
    double yComp[3];

/*
    if(previous != NULL)
        for(int i =0 ; i < 3 ;i++)
            up[i] = previous->up[i];
*/
    //showVector(position);
    /*
    normalize(direction);normalize(up);
    crossProduct(direction,up,cross);
    crossProduct(cross,direction,up);
    normalize(direction);normalize(up);normalize(cross);if(n == 0)showVectors();
*/
    normalize(direction);normalize(up);normalize(cross);

    for(int x = 0; x < imageResult->width();x++)
    {
        //multVector((double)(x),cross,xComp);
        multVector((double)(-(imageResult->width()/2) + x) ,cross,xComp);
        for(int y = 0; y < imageResult->height();y++)
        {
            //multVector((double)(y),up,yComp);
            multVector((double)( (imageResult->height()/2) - y) ,up,yComp);
            addVectors(xComp,yComp,point);


            addVectors(position,point,point);
            //showVector(point);
            /*
            if(y <imageResult->height()/2 &&cross[0]!=0)
            {
                cout <<"new"<<endl;
                 showVector(position);
                 showVector(point);
                showVector(xComp);
                 showVector(yComp);
                 showVector(cross);
                 showVector(up);
            }*/

            (*imageResult)(x,y,n,0) = imageSource->linear_atXYZ(point[0],point[1],point[2],0,0);
        }
    }

    return 0;
}


Snap::~Snap()
{
    //dtor
}

