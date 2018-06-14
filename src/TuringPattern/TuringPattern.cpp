#include "TuringPattern.h"

TuringPattern::TuringPattern(){
	this->size = 40;

	set_random_params();
}

TuringPattern::TuringPattern(int size){
	this->size = size;
	
	set_random_params();
}
void TuringPattern::set_random_params(){
	float factor = 15.0;
    s = randFloat(0, 1) / factor;
    Da = randFloat(0, 1) / factor;
    Di = randFloat(0, 1) / 5;
    ra = randFloat(0, 1) / 50.0;
    ri = randFloat(0, 1) / 5;
    ba = randFloat(0, 1) / factor;
    bi = randFloat(0, 1) / factor;
}
void TuringPattern::fill(vector< vector<float> >& ca){
	ca.resize(size);
	for (size_t i = 0; i < ca.size(); ++i){
		ca[i].resize(size);
        for (size_t j = 0; j < ca[i].size(); ++j){
            ca[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-.5;
        }
    }
}
float TuringPattern::diffusion_value(vector< vector<float> > ca, size_t i, size_t j){
	float diffusion_value = 0.0;
	float t_value = ca[i][j];

	int count = 0;
	if( i != 0 ){
		diffusion_value += ca[i-1][j];
		count++;
	}
	if( i != size - 1 ){
		diffusion_value += ca[i+1][j];
		count++;
	}
	if( j != 0 ){
		diffusion_value += ca[i][j-1];
		count++;
	}
	if( j != size - 1 ){
		diffusion_value += ca[i][j+1];
		count++;
	}

	diffusion_value -= count * t_value;

	return diffusion_value;
}
void TuringPattern::update_reaction(){
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
        }
    }

    activator = next_activator;
    inhibitor = next_inhibitor;
}
GLuint TuringPattern::create(){
	fill(activator);
	fill(inhibitor);

	for( int i = 0; i < 20; i++ ){
    	update_reaction();
    }
    string filename = writeFile();
    return loadGLTexture(filename);
}
void TuringPattern::create_mat(Mat &mat, vector< vector<float> > activator, vector< vector<float> > inhibitor){
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
string TuringPattern::writeFile(){
	Mat mat(size, size, CV_8UC3);
    create_mat(mat, activator, inhibitor);
	
	string filename = "./skins/alpha.png";
    
    // namedWindow( "warp_rotate_window", WINDOW_AUTOSIZE );
    // imshow( "warp_rotate_window", mat );
    // moveWindow( "warp_rotate_window", 900,20);
    // waitKey(0);
    
    try {
    	vector<int> compression_params;
	    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	    compression_params.push_back(9);
        imwrite(filename, mat, compression_params);

        return filename;
    }catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
}
GLuint TuringPattern::loadGLTexture(string filename){
    GLuint texture = SOIL_load_OGL_texture(
        filename.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if(texture == 0)
        return 0;

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return texture;
}
TuringPattern::~TuringPattern(){}