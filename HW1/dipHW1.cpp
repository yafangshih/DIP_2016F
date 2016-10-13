#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdio>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 6){
     cout <<"*error* Usage: FilePath scalingFactorCol scalingFactorRow interpolationMethod" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   
    if(! image.data ){
        cout <<  "*error* Could not open or find the image" << std::endl ;
        return -1;
    }

    float outC=1.0, outR=1.0;
    bool r = sscanf(argv[2], "%f", &outC);
    bool r2 = sscanf(argv[3], "%f", &outR);
    if(! (r2*r)){
    	cout<<"*error* Wrong format of output image size."<<endl;
    	return -1;
    }

    int interpolationMethod=INTER_LINEAR;
    r = sscanf(argv[4], "%d", &interpolationMethod);
    if(!r || !(interpolationMethod==0 || interpolationMethod==1)){
    	cout<<"*error* Wrong format of interpolation method."<<endl;
    	cout<<"        0 for bilinear, 1 for bicubic."<<endl;
    	return -1;
    }
    interpolationMethod= interpolationMethod==0 ? INTER_LINEAR:INTER_CUBIC;

    Mat imageout;
    resize( image, imageout, Size(), outC, outR, interpolationMethod );

    try {
        imwrite(argv[5], imageout);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "%s\n", ex.what());
        return -1;
    }

    namedWindow( "Resized image", WINDOW_AUTOSIZE );
    imshow( "Resized image", imageout );               

    waitKey(3000);                                          
    return 0;
}