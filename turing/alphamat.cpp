#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

const int SIZE = 40;

float s; // autocatalysis

float Da, Di; // diffusion constants

float ra, ri; // decay rates
float ba, bi; // basic production


void constraint(float& value, float min, float max){
	return;
	if( value < min ) value = min;
	else if( value > max ) value = max;
}
void fill(vector< vector<float> >& ca){
	ca.resize(SIZE);
	for (size_t i = 0; i < ca.size(); ++i){
		ca[i].resize(SIZE);
        for (size_t j = 0; j < ca[i].size(); ++j){
            ca[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-.5;
            constraint(ca[i][j], 0, 1);
        }
    }
}
void print(vector< vector<float> > ca){
	printf("%s", string(SIZE, '\n').c_str() );

    for (int i = 0; i < ca.size(); ++i){
        for (int j = 0; j < ca[i].size(); ++j)
            printf("%2.2f ", ca[i][j]);
        printf("\n");
    }
    printf("----------------------------------------\n");
}
float diffusion_value(vector< vector<float> > ca, size_t i, size_t j){
	float diffusion_value = 0.0;
	float t_value = ca[i][j];

	int count = 0;
	if( i != 0 ){
		diffusion_value += ca[i-1][j];
		count++;
	}
	if( i != SIZE - 1 ){
		diffusion_value += ca[i+1][j];
		count++;
	}
	if( j != 0 ){
		diffusion_value += ca[i][j-1];
		count++;
	}
	if( j != SIZE - 1 ){
		diffusion_value += ca[i][j+1];
		count++;
	}

	diffusion_value -= count * t_value;

	return diffusion_value;
}
void update_reaction(vector< vector<float> >& activator, vector< vector<float> >& inhibitor){
	vector< vector<float> > next_activator(activator);
	vector< vector<float> > next_inhibitor(inhibitor);

	for (size_t i = 0; i < activator.size(); ++i){
        for (size_t j = 0; j < activator[i].size(); ++j){
        	float activator_diffusion = Da * diffusion_value(activator, i, j);
        	float inhibitor_diffusion = Di * diffusion_value(inhibitor, i, j);
			
			next_activator[i][j] += s*( (pow(activator[i][j],2) / inhibitor[i][j]) + ba ) - ra*activator[i][j];	
			next_activator[i][j] += activator_diffusion;
        	
        	next_inhibitor[i][j] += s * pow(activator[i][j], 2) - ri * inhibitor[i][j] + bi;
        	next_inhibitor[i][j] += inhibitor_diffusion;

        	constraint(next_activator[i][j], 0, 1);
        	constraint(next_inhibitor[i][j], 0, 1);
        }
    }

    activator = next_activator;
    inhibitor = next_inhibitor;
}
void set_random_parameters(){
	float factor = 15.0;
	s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / factor;
	Da = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / factor;
	Di = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / 5;
	ra = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / 50.0;
	ri = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / 5;
	ba = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / factor;
	bi = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / factor;
}
float randFloat(){
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
void create_mat(Mat &mat, vector< vector<float> > activator, vector< vector<float> > inhibitor){
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
        	Vec3b& rgba = mat.at<Vec3b>(i, j);

        	float diff = (activator[i][j] - inhibitor[i][j]) * 255;
        	float act = activator[i][j] * 255;
        	float inh = inhibitor[i][j] * 255;

        	vector<float> rand_order;
        	rand_order.push_back(diff);
        	rand_order.push_back(diff);
        	rand_order.push_back(diff);

        	std::random_shuffle ( rand_order.begin(), rand_order.end() );
        	
        	for( int i = 0; i < rand_order.size(); i++ ){
        		rgba[i] = rand_order[i];
        	}
        }
    }
}
int main(int argv, char **argc){
	srand(time(NULL));
	set_random_parameters();
	vector< vector<float> > activator;

    vector< vector<float> > inhibitor;

    fill(activator);
    fill(inhibitor);
    
    for( int i = 0; i < 20; i++ ){
    	update_reaction(activator, inhibitor);
    }
    
    Mat mat(SIZE, SIZE, CV_8UC3);
    create_mat(mat, activator, inhibitor);

    namedWindow( "warp_rotate_window", WINDOW_AUTOSIZE );
    imshow( "warp_rotate_window", mat );
    moveWindow( "warp_rotate_window", 900,20);
    waitKey(0);

    try {
    	vector<int> compression_params;
	    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	    compression_params.push_back(9);
        imwrite("alpha.png", mat, compression_params);
    }catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
        return 1;
    }
    
    fprintf(stdout, "Saved PNG file with alpha data.\n");
    return 0;
}