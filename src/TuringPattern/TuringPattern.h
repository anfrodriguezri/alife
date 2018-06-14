#ifndef TURING_PATTERN_H_
#define TURING_PATTERN_H_

#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <SOIL.h>
#include "../helpers/helpers.h"

using namespace cv;
using namespace std;

class TuringPattern {
    protected:
        int size;
        vector< vector<float> > activator;
        vector< vector<float> > inhibitor;
        float s; // autocatalysis
        float Da; // diffusion constants
        float Di; // diffusion constants
        float ra; // decay rates
        float ri; // decay rates
        float ba; // basic production
        float bi; // basic production

        void set_random_params();
        void fill(vector< vector<float> >& ca);
        float diffusion_value(vector< vector<float> > ca, size_t i, size_t j);
        void update_reaction();
        void create_mat(Mat &mat, vector< vector<float> > activator, vector< vector<float> > inhibitor);
        string writeFile();
        GLuint loadGLTexture(string filename);
    public:
        TuringPattern();
        TuringPattern(int size);
        GLuint create();
        virtual ~TuringPattern();
};

#endif /* TURING_PATTERN_H_ */

