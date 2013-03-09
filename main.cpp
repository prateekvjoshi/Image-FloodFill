// Flood fills the region around the selected point

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nFloodFill\n"
    "Call:\n"
    "./main inputImage.jpg\n" << endl;
    
    cout << "Hot keys: \n"
    "\tESC - quit the program\n"
    "\tr - restore the original image\n" << endl;
}

Mat image0, image, gray, mask;
int ffillMode = 1;
int loDiff = 20, upDiff = 20;
int connectivity = 4;
int isColor = true;
bool useMask = false;
int newMaskVal = 255;

static void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
        return;
    
    Point seed = Point(x,y);
    int lo = ffillMode == 0 ? 0 : loDiff;
    int up = ffillMode == 0 ? 0 : upDiff;
    int flags = connectivity + (newMaskVal << 8) +
    (ffillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
    int b = (unsigned)theRNG() & 255;
    int g = (unsigned)theRNG() & 255;
    int r = (unsigned)theRNG() & 255;
    Rect ccomp;
    
    Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
    Mat dst = isColor ? image : gray;
    int area;
    
    if( useMask )
    {
        threshold(mask, mask, 1, 128, CV_THRESH_BINARY);
        area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
                         Scalar(up, up, up), flags);
        imshow( "mask", mask );
    }
    else
    {
        area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
                         Scalar(up, up, up), flags);
    }
    
    imshow("image", dst);
}


int main( int argc, char** argv )
{
    char* filename = argc >= 2 ? argv[1] : (char*)"inputImage.jpg";
    image0 = imread(filename, 1);
    
    if( image0.empty() )
    {
        cout << "Image empty. Usage: ./main <image_name>\n";
        return 0;
    }
    help();
    image0.copyTo(image);
    cvtColor(image0, gray, CV_BGR2GRAY);
    mask.create(image0.rows+2, image0.cols+2, CV_8UC1);
    
    namedWindow( "image", 0 );
    
    setMouseCallback( "image", onMouse, 0 );
    
    
    for(;;)
    {
        imshow("image", isColor ? image : gray);
        
        int c = waitKey(0);
        
        if( (c & 255) == 27 )
        {
            cout << "Exiting ...\n";
            break;
        }
        
        if(c == 'r')
        {
            cout << "Original image is restored\n";
            image0.copyTo(image);
            cvtColor(image, gray, CV_BGR2GRAY);
            mask = Scalar::all(0);
        }
    }
    
    return 0;
}
