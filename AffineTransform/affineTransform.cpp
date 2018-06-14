/**
 * @function Geometric_Transforms_Demo.cpp
 * @brief Demo code for Geometric Transforms
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/// Global variables
const char* source_window = "Source image";
const char* warp_window = "Warp";
const char* warp_rotate_window = "Warp + Rotate";

/**
 * @function main
 */
int main( int argc, char** argv ){
    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat rot_mat( 2, 3, CV_32FC1 );
    Mat warp_mat( 2, 3, CV_32FC1 );
    Mat src, warp_dst, warp_rotate_dst;

    CommandLineParser parser( argc, argv, "{@input | ../data/lena.jpg | input image}" );
    src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }

    namedWindow( source_window, WINDOW_AUTOSIZE );
    imshow( source_window, src );
    moveWindow( source_window, 100,20);

    warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

    srcTri[0] = Point2f( 0,0 );
    srcTri[1] = Point2f( src.cols - 1.f, 0 );
    srcTri[2] = Point2f( 0, src.rows - 1.f );

    dstTri[0] = Point2f( src.cols*(pow(0.2f,2)-pow(.5,2)), src.rows*0.25f );
    dstTri[1] = Point2f( src.cols*.5f, src.rows*sin(2*0.5f*.2) );
    dstTri[2] = Point2f( src.cols*sin(0.15f)+cos(.3), src.rows*cos(0.9f) );

    warp_mat = getAffineTransform( srcTri, dstTri );

    warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

    namedWindow( warp_window, WINDOW_AUTOSIZE );
    moveWindow( warp_window, 900,20);
    imshow( warp_window, warp_dst );

    Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
    double angle = -50.0;
    double scale = 0.6;

    rot_mat = getRotationMatrix2D( center, angle, scale );

    warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );

    /*namedWindow( warp_rotate_window, WINDOW_AUTOSIZE );
    imshow( warp_rotate_window, warp_rotate_dst );
    moveWindow( warp_rotate_window, 900,20);*/

    waitKey(0);

    return 0;
}