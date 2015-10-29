#include "vectorOps.h"


void crossProduct(double v1[3],double v2[3],double v3[3])
{
    v3[0] = v1[1]*v2[2] - v1[2]*v2[1];
    v3[1] = v1[2]*v2[0] - v1[0]*v2[2];
    v3[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

double dotProduct(double v1[3],double v2[3])
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] ;
}

void addVectors(double v1[3],double v2[3],double v3[3])
{
    v3[0] = v1[0]+v2[0];
    v3[1] = v1[1]+v2[1];
    v3[2] = v1[2]+v2[2];
}

void subVectors(double v1[3],double v2[3],double v3[3])
{
    v3[0] = v1[0]-v2[0];
    v3[1] = v1[1]-v2[1];
    v3[2] = v1[2]-v2[2];
}

void multVector(double n,double v2[3],double v3[3])
{
    v3[0] = n*v2[0];
    v3[1] = n*v2[1];
    v3[2] = n*v2[2];
}
