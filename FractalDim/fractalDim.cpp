#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const char* source_window = "Source image";

Mat& ScanImageAndReduceIterator(Mat&);

int main( int argc, char** argv ){;
	Mat src;

	CommandLineParser parser( argc, argv, "{@input | ../data/lena.jpg | input image}" );
	src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );
	if( src.empty() )
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}


	ScanImageAndReduceIterator(src, 2);
	namedWindow( source_window, WINDOW_AUTOSIZE );
	imshow( source_window, src );
	moveWindow( source_window, 100,20);

	waitKey(0);

	return 0;
}

Mat& ScanImageAndReduceIterator(Mat& src, int scale){
    // accept only char type matrices
	CV_Assert(src.depth() == CV_8U);    

	int count_black = 0;
	int count_white = 0;
	
	for( int y = 0; y < src.rows; y++ ) {
		for( int x = 0; x < src.cols; x++ ) {
			if( src.at<uchar>(y,x) != 0 ) {
				// change this to to 'src.atuchar>(y,x) == 255' 
				// if your img has only 1 channel
				if( src.at<cv::Vec3b>(y,x) == cv::Vec3b(255,255,255) ) {
					count_white++;
				}else if( src.at<cv::Vec3b>(y,x) == cv::Vec3b(0,0,0) ) {
					count_black++;
				} 
			}
		}
	}
	cout << count_black << endl;
	cout << count_white << endl;
	return src;
}