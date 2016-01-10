#include <iostream>

using namespace std;

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "CImg.h"

using namespace cimg_library;
using namespace std;


void isolePlage(CImg<unsigned short>* img, CImg<unsigned short>* low , CImg<unsigned short>* high)
{
    for(int x = 0; x < img->width(); x++)
    {
        for(int y = 0; y < img->height(); y++)
        {
            for(int z = 0; z < img->depth(); z++)
            {
               if((*low)(x,y,z) <= 0)
                {
                    (*img)(x,y,z,0) = 0;
                }
                else
                {
                    if((*high)(x,y,z) > 0)
                    {
                        (*img)(x,y,z,0) = 0;
                    }
                }
            }
        }
    }
}

int main()
{
    cout << "Hello world!" << endl;
    CImg<unsigned short> *image = new CImg<unsigned short>();
    image->load_analyze("cochlee_resample.img");
    CImg<unsigned short> low =image->get_threshold(58);
    CImg<unsigned short> high =image->get_threshold(110);
    isolePlage(image,&low,&high);
    image->save_analyze("isolePlage");
    return 0;
}
