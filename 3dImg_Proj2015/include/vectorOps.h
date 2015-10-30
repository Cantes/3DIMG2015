#ifndef VECTOROPS_H_INCLUDED
#define VECTOROPS_H_INCLUDED


void crossProduct(double v1[3],double v2[3],double v3[3]);
double dotProduct(double v1[3],double v2[3]);
void addVectors(double v1[3],double v2[3],double v3[3]);
void subVectors(double v1[3],double v2[3],double v3[3]);
void multVector(double n,double v2[3],double v3[3]);
double norm(double v1[3]);
void normalized(double v1[3]);


#endif // VECTOROPS_H_INCLUDED
