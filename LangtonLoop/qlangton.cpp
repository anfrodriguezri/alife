#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include<string>
#include <time.h>

#include <chrono>
#include <thread>

#include <vector>
#include <tuple>

#include <unistd.h>

using namespace std;

const int SIZE_H = 30;
const int SIZE_W = 120;

const int MAX = 7;

void fill(int** ca, size_t rows, size_t cols, bool random){
	for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j)
            ca[i][j] = random ? rand() % MAX : 0;
    }
}

void print(int** ca, size_t rows, size_t cols){
	printf("%s", string(50, '\n').c_str() );
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j){
            printf("%d", ca[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
    //sleep();
}

int ruleValue(string r){
	vector<tuple<string, int>> transitionTable;

	transitionTable.push_back( make_tuple("00000", 0) );
	transitionTable.push_back( make_tuple("00001", 2) );
	transitionTable.push_back( make_tuple("00002", 0) );
	transitionTable.push_back( make_tuple("00003", 0) );
	transitionTable.push_back( make_tuple("00005", 0) );
	transitionTable.push_back( make_tuple("00006", 3) );
	transitionTable.push_back( make_tuple("00007", 1) );
	transitionTable.push_back( make_tuple("00011", 2) );
	transitionTable.push_back( make_tuple("00012", 2) );
	transitionTable.push_back( make_tuple("00013", 2) );
	transitionTable.push_back( make_tuple("00021", 2) );
	transitionTable.push_back( make_tuple("00022", 0) );
	transitionTable.push_back( make_tuple("00023", 0) );
	transitionTable.push_back( make_tuple("00026", 2) );
	transitionTable.push_back( make_tuple("00027", 2) );
	transitionTable.push_back( make_tuple("00032", 0) );
	transitionTable.push_back( make_tuple("00052", 5) );
	transitionTable.push_back( make_tuple("00062", 2) );
	transitionTable.push_back( make_tuple("00072", 2) );
	transitionTable.push_back( make_tuple("00102", 2) );
	transitionTable.push_back( make_tuple("00112", 0) );
	transitionTable.push_back( make_tuple("00202", 0) );
	transitionTable.push_back( make_tuple("00203", 0) );
	transitionTable.push_back( make_tuple("00205", 0) );
	transitionTable.push_back( make_tuple("00212", 5) );
	transitionTable.push_back( make_tuple("00222", 0) );
	transitionTable.push_back( make_tuple("00232", 2) );
	transitionTable.push_back( make_tuple("00522", 2) );
	transitionTable.push_back( make_tuple("01232", 1) );
	transitionTable.push_back( make_tuple("01242", 1) );
	transitionTable.push_back( make_tuple("01252", 5) );
	transitionTable.push_back( make_tuple("01262", 1) );
	transitionTable.push_back( make_tuple("01272", 1) );
	transitionTable.push_back( make_tuple("01275", 1) );
	transitionTable.push_back( make_tuple("01422", 1) );
	transitionTable.push_back( make_tuple("01432", 1) );
	transitionTable.push_back( make_tuple("01442", 1) );
	transitionTable.push_back( make_tuple("01472", 1) );
	transitionTable.push_back( make_tuple("01625", 1) );
	transitionTable.push_back( make_tuple("01722", 1) );
	transitionTable.push_back( make_tuple("01725", 5) );
	transitionTable.push_back( make_tuple("01752", 1) );
	transitionTable.push_back( make_tuple("01762", 1) );
	transitionTable.push_back( make_tuple("01772", 1) );
	transitionTable.push_back( make_tuple("02527", 1) );
	transitionTable.push_back( make_tuple("10001", 1) );
	transitionTable.push_back( make_tuple("10006", 1) );
	transitionTable.push_back( make_tuple("10007", 7) );
	transitionTable.push_back( make_tuple("10011", 1) );
	transitionTable.push_back( make_tuple("10012", 1) );
	transitionTable.push_back( make_tuple("10021", 1) );
	transitionTable.push_back( make_tuple("10024", 4) );
	transitionTable.push_back( make_tuple("10027", 7) );
	transitionTable.push_back( make_tuple("10051", 1) );
	transitionTable.push_back( make_tuple("10101", 1) );
	transitionTable.push_back( make_tuple("10111", 1) );
	transitionTable.push_back( make_tuple("10124", 4) );
	transitionTable.push_back( make_tuple("10127", 7) );
	transitionTable.push_back( make_tuple("10202", 6) );
	transitionTable.push_back( make_tuple("10212", 1) );
	transitionTable.push_back( make_tuple("10221", 1) );
	transitionTable.push_back( make_tuple("10224", 4) );
	transitionTable.push_back( make_tuple("10226", 3) );
	transitionTable.push_back( make_tuple("10227", 7) );
	transitionTable.push_back( make_tuple("10232", 7) );
	transitionTable.push_back( make_tuple("10242", 4) );
	transitionTable.push_back( make_tuple("10262", 6) );
	transitionTable.push_back( make_tuple("10264", 4) );
	transitionTable.push_back( make_tuple("10267", 7) );
	transitionTable.push_back( make_tuple("10271", 0) );
	transitionTable.push_back( make_tuple("10272", 7) );
	transitionTable.push_back( make_tuple("10542", 7) );
	transitionTable.push_back( make_tuple("11112", 1) );
	transitionTable.push_back( make_tuple("11122", 1) );
	transitionTable.push_back( make_tuple("11124", 4) );
	transitionTable.push_back( make_tuple("11125", 1) );
	transitionTable.push_back( make_tuple("11126", 1) );
	transitionTable.push_back( make_tuple("11127", 7) );
	transitionTable.push_back( make_tuple("11152", 2) );
	transitionTable.push_back( make_tuple("11212", 1) );
	transitionTable.push_back( make_tuple("11222", 1) );
	transitionTable.push_back( make_tuple("11224", 4) );
	transitionTable.push_back( make_tuple("11225", 1) );
	transitionTable.push_back( make_tuple("11227", 7) );
	transitionTable.push_back( make_tuple("11232", 1) );
	transitionTable.push_back( make_tuple("11242", 4) );
	transitionTable.push_back( make_tuple("11262", 1) );
	transitionTable.push_back( make_tuple("11272", 7) );
	transitionTable.push_back( make_tuple("11322", 1) );
	transitionTable.push_back( make_tuple("12224", 4) );
	transitionTable.push_back( make_tuple("12227", 7) );
	transitionTable.push_back( make_tuple("12243", 4) );
	transitionTable.push_back( make_tuple("12254", 7) );
	transitionTable.push_back( make_tuple("12324", 4) );
	transitionTable.push_back( make_tuple("12327", 7) );
	transitionTable.push_back( make_tuple("12425", 5) );
	transitionTable.push_back( make_tuple("12426", 7) );
	transitionTable.push_back( make_tuple("12527", 5) );
	transitionTable.push_back( make_tuple("20001", 2) );
	transitionTable.push_back( make_tuple("20002", 2) );
	transitionTable.push_back( make_tuple("20004", 2) );
	transitionTable.push_back( make_tuple("20007", 1) );
	transitionTable.push_back( make_tuple("20012", 2) );
	transitionTable.push_back( make_tuple("20015", 2) );
	transitionTable.push_back( make_tuple("20021", 2) );
	transitionTable.push_back( make_tuple("20022", 2) );
	transitionTable.push_back( make_tuple("20023", 2) );
	transitionTable.push_back( make_tuple("20024", 2) );
	transitionTable.push_back( make_tuple("20025", 0) );
	transitionTable.push_back( make_tuple("20026", 2) );
	transitionTable.push_back( make_tuple("20027", 2) );
	transitionTable.push_back( make_tuple("20032", 6) );
	transitionTable.push_back( make_tuple("20042", 3) );
	transitionTable.push_back( make_tuple("20051", 7) );
	transitionTable.push_back( make_tuple("20052", 2) );
	transitionTable.push_back( make_tuple("20057", 5) );
	transitionTable.push_back( make_tuple("20072", 2) );
	transitionTable.push_back( make_tuple("20102", 2) );
	transitionTable.push_back( make_tuple("20112", 2) );
	transitionTable.push_back( make_tuple("20122", 2) );
	transitionTable.push_back( make_tuple("20142", 2) );
	transitionTable.push_back( make_tuple("20172", 2) );
	transitionTable.push_back( make_tuple("20202", 2) );
	transitionTable.push_back( make_tuple("20203", 2) );
	transitionTable.push_back( make_tuple("20205", 2) );
	transitionTable.push_back( make_tuple("20207", 3) );
	transitionTable.push_back( make_tuple("20212", 2) );
	transitionTable.push_back( make_tuple("20215", 2) );
	transitionTable.push_back( make_tuple("20221", 2) );
	transitionTable.push_back( make_tuple("20222", 2) );
	transitionTable.push_back( make_tuple("20227", 2) );
	transitionTable.push_back( make_tuple("20232", 1) );
	transitionTable.push_back( make_tuple("20242", 2) );
	transitionTable.push_back( make_tuple("20245", 2) );
	transitionTable.push_back( make_tuple("20252", 0) );
	transitionTable.push_back( make_tuple("20255", 2) );
	transitionTable.push_back( make_tuple("20262", 2) );
	transitionTable.push_back( make_tuple("20272", 2) );
	transitionTable.push_back( make_tuple("20312", 2) );
	transitionTable.push_back( make_tuple("20321", 6) );
	transitionTable.push_back( make_tuple("20322", 6) );
	transitionTable.push_back( make_tuple("20342", 2) );
	transitionTable.push_back( make_tuple("20422", 2) );
	transitionTable.push_back( make_tuple("20512", 2) );
	transitionTable.push_back( make_tuple("20521", 2) );
	transitionTable.push_back( make_tuple("20522", 2) );
	transitionTable.push_back( make_tuple("20552", 1) );
	transitionTable.push_back( make_tuple("20572", 5) );
	transitionTable.push_back( make_tuple("20622", 2) );
	transitionTable.push_back( make_tuple("20672", 2) );
	transitionTable.push_back( make_tuple("20712", 2) );
	transitionTable.push_back( make_tuple("20722", 2) );
	transitionTable.push_back( make_tuple("20742", 2) );
	transitionTable.push_back( make_tuple("20772", 2) );
	transitionTable.push_back( make_tuple("21122", 2) );
	transitionTable.push_back( make_tuple("21126", 1) );
	transitionTable.push_back( make_tuple("21222", 2) );
	transitionTable.push_back( make_tuple("21224", 2) );
	transitionTable.push_back( make_tuple("21226", 2) );
	transitionTable.push_back( make_tuple("21227", 2) );
	transitionTable.push_back( make_tuple("21422", 2) );
	transitionTable.push_back( make_tuple("21522", 2) );
	transitionTable.push_back( make_tuple("21622", 2) );
	transitionTable.push_back( make_tuple("21722", 2) );
	transitionTable.push_back( make_tuple("22227", 2) );
	transitionTable.push_back( make_tuple("22244", 2) );
	transitionTable.push_back( make_tuple("22246", 2) );
	transitionTable.push_back( make_tuple("22276", 2) );
	transitionTable.push_back( make_tuple("22277", 2) );
	transitionTable.push_back( make_tuple("30001", 3) );
	transitionTable.push_back( make_tuple("30002", 2) );
	transitionTable.push_back( make_tuple("30004", 1) );
	transitionTable.push_back( make_tuple("30007", 6) );
	transitionTable.push_back( make_tuple("30012", 3) );
	transitionTable.push_back( make_tuple("30042", 1) );
	transitionTable.push_back( make_tuple("30062", 2) );
	transitionTable.push_back( make_tuple("30102", 1) );
	transitionTable.push_back( make_tuple("30122", 0) );
	transitionTable.push_back( make_tuple("30251", 1) );
	transitionTable.push_back( make_tuple("40112", 0) );
	transitionTable.push_back( make_tuple("40122", 0) );
	transitionTable.push_back( make_tuple("40125", 0) );
	transitionTable.push_back( make_tuple("40212", 0) );
	transitionTable.push_back( make_tuple("40222", 1) );
	transitionTable.push_back( make_tuple("40232", 6) );
	transitionTable.push_back( make_tuple("40252", 0) );
	transitionTable.push_back( make_tuple("40322", 1) );
	transitionTable.push_back( make_tuple("50002", 2) );
	transitionTable.push_back( make_tuple("50021", 5) );
	transitionTable.push_back( make_tuple("50022", 5) );
	transitionTable.push_back( make_tuple("50023", 2) );
	transitionTable.push_back( make_tuple("50027", 2) );
	transitionTable.push_back( make_tuple("50052", 0) );
	transitionTable.push_back( make_tuple("50202", 2) );
	transitionTable.push_back( make_tuple("50212", 2) );
	transitionTable.push_back( make_tuple("50215", 2) );
	transitionTable.push_back( make_tuple("50222", 0) );
	transitionTable.push_back( make_tuple("50224", 4) );
	transitionTable.push_back( make_tuple("50272", 2) );
	transitionTable.push_back( make_tuple("51212", 2) );
	transitionTable.push_back( make_tuple("51222", 0) );
	transitionTable.push_back( make_tuple("51242", 2) );
	transitionTable.push_back( make_tuple("51272", 2) );
	transitionTable.push_back( make_tuple("60001", 1) );
	transitionTable.push_back( make_tuple("60002", 1) );
	transitionTable.push_back( make_tuple("60212", 0) );
	transitionTable.push_back( make_tuple("61212", 5) );
	transitionTable.push_back( make_tuple("61213", 1) );
	transitionTable.push_back( make_tuple("61222", 5) );
	transitionTable.push_back( make_tuple("70007", 7) );
	transitionTable.push_back( make_tuple("70112", 0) );
	transitionTable.push_back( make_tuple("70122", 0) );
	transitionTable.push_back( make_tuple("70125", 0) );
	transitionTable.push_back( make_tuple("70212", 0) );
	transitionTable.push_back( make_tuple("70222", 1) );
	transitionTable.push_back( make_tuple("70225", 1) );
	transitionTable.push_back( make_tuple("70232", 1) );
	transitionTable.push_back( make_tuple("70252", 5) );
	transitionTable.push_back( make_tuple("70272", 0) );

	for( int i = 0; i < transitionTable.size(); i++ ){
		for( int j = 0; j < r.size(); j++){
			string rotatedRule;
			for( int  k = 0; k < r.size(); k++ ){
				rotatedRule += r[(k+j) % r.size()];
			}

			if( std::get<0>(transitionTable[i]) == rotatedRule )
				return std::get<1>(transitionTable[i]);
		}
		
	}

	return -1;
}

void transition(int** ca, size_t rows, size_t cols){
	for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j){
        	string rule;
        	int center = ca[i][j], top, right, bottom, left;

        	if( i != 0 ) left = ca[i-1][j];
			if( i != cols - 1 ) ca[i+1][j];
			if( j != 0 ) ca[i][j-1];
			if( j != rows - 1 ) ca[i][j+1];

			rule = to_string(center) + to_string(left) + to_string(top) + to_string(right) + to_string(bottom);
			
			int rv = ruleValue(rule);

			if( rv == -1 ) continue;
			ca[i][j] = rv;
        }
        printf("\n");
    }
}

void initLangton(int** ca, size_t rows, size_t cols){
	int i1 = rows * 1/2, j1 = cols * 1/4;
	vector<string> qlangton;

	qlangton.push_back("02222222200000");
	qlangton.push_back("21701401420000");
	qlangton.push_back("20222222020000");
	qlangton.push_back("27200002120000");
	qlangton.push_back("21200002120000");
	qlangton.push_back("20200002120000");
	qlangton.push_back("27200002120000");
	qlangton.push_back("21222222122222");
	qlangton.push_back("20710710711111");
	qlangton.push_back("02222222222222");
	
	for( int i = 0; i < qlangton.size(); i++ ){
		for( int j = 0; j < qlangton[i].size(); j++){
			ca[i1 + i][j1 + j] = (int)qlangton[i][j] - 48;
			
			//cout << i1 + i << " " << j1 + j;
		}
		//cout << endl;
	}
}

int main(){
	srand(time(NULL));

	int** ca = new int*[SIZE_H];

    for(size_t i = 0; i < SIZE_H; i++){
        ca[i] = new int[SIZE_W];
    }

    fill(ca, SIZE_H, SIZE_W, false);
    initLangton(ca, SIZE_H, SIZE_W);
    print(ca, SIZE_H, SIZE_W);
    while(true){
    	transition(ca, SIZE_H, SIZE_W);
    	print(ca, SIZE_H, SIZE_W);
    }
}