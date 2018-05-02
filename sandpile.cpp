#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <chrono>
#include <thread>

using namespace std;

const int SIZE = 20;
const int MILLIS = 40;

void fillSandpile(int**, size_t, size_t, bool);
void printSandpile(int**, size_t, size_t);
void dropSandGrain(int**, bool);
void updateNeighbours(int**, size_t, size_t);
void collapseSand(int**, size_t, size_t);
void sleep();

int main(){
    srand(time(NULL));
    
    int** sandpile2d = new int*[SIZE];

    for(size_t i = 0; i < SIZE; i++){
        sandpile2d[i] = new int[SIZE];
    }
    fillSandpile(sandpile2d, SIZE, SIZE, false);
    printSandpile(sandpile2d, SIZE, SIZE);

    while(true){
    	dropSandGrain(sandpile2d, false);
    	printSandpile(sandpile2d, SIZE, SIZE);
    	
    	collapseSand(sandpile2d, SIZE, SIZE );
 		printSandpile(sandpile2d, SIZE, SIZE);
    }       
}
void fillSandpile(int** sandpile2d, size_t rows, size_t cols, bool random){
	for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            sandpile2d[i][j] = random ? rand() % 4 : 0;
    }
}
void printSandpile(int** sandpile2d, size_t rows, size_t cols){
	printf("%s", string(50, '\n').c_str() );
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            printf("%d", sandpile2d[i][j]);
        printf("\n");
    }
    printf("----------------------------------------\n");
    sleep();
}
void dropSandGrain(int** sandpile2d, bool random){
	int i = SIZE / 2;
	int j = SIZE / 2;

	if( random ){
		i = rand() % SIZE;
		j = rand() % SIZE;
	}

	sandpile2d[i][j]++;
}
void updateNeighbours(int** sandpile2d, size_t i, size_t j){
	if( i != 0 ) sandpile2d[i-1][j]++;
	if( i != SIZE - 1 ) sandpile2d[i+1][j]++;
	if( j != 0 ) sandpile2d[i][j-1]++;
	if( j != SIZE - 1 ) sandpile2d[i][j+1]++;
}
void collapseSand(int** sandpile2d, size_t rows, size_t cols){
	bool somethingToCollapse;
	do {
		somethingToCollapse = false;
		//printSandpile(sandpile2d, rows, cols);

		for (size_t i = 0; i < rows; ++i){
	        for (size_t j = 0; j < cols; ++j){
	        	if( sandpile2d[i][j] >= 4 ){
	            	sandpile2d[i][j] = 0;

	            	updateNeighbours(sandpile2d, i, j);

	            	somethingToCollapse = true;

	            	break;
	            }
	        }
	        if( somethingToCollapse ) break;
	    }
	} while( somethingToCollapse );
}
void sleep(){
	this_thread::sleep_for(chrono::milliseconds(MILLIS));
}