#include <iostream>

#include "../helpers/oglhelpers.h"
#include "Sandpile.h"

Sandpile::Sandpile(){
  x = 400;
  y = 400;
  size = 16;
  max = 20;
  grainResource = max / 10;
  initializeMatrix();
}
Sandpile::Sandpile(float x, float y, int size, float max){
  this->x = x;
  this->y = y;
  this->size = size;
  this->max = max;
  grainResource = max / 2;
  initializeMatrix();
};
void Sandpile::initializeMatrix(){
  sandpile2d = vector<vector<int>>(size, std::vector<int>(size));

  for(int i = 0; i < 2 * max; i++){
      dropGrain();
      collapseGrains();
  }
}

void Sandpile::dropGrain(){
  int i = size / 2;
  int j = size / 2;

  sandpile2d[i][j] += grainResource;
};
void Sandpile::updateNeighbours(int i, int j){
  if( i != 0 ) sandpile2d[i-1][j] += grainResource;
  if( i != size - 1 ) sandpile2d[i+1][j] += grainResource;
  if( j != 0 ) sandpile2d[i][j-1] += grainResource;
  if( j != size - 1 ) sandpile2d[i][j+1] += grainResource;
}
void Sandpile::collapseGrains(){
  bool somethingCollapsed;
  do {
    somethingCollapsed = false;

    for (int i = 0; i < sandpile2d.size(); ++i){
          for (int j = 0; j < sandpile2d[0].size(); ++j){
            if( sandpile2d[i][j] >= max ){
                sandpile2d[i][j] = 0;

                updateNeighbours(i, j);

                somethingCollapsed = true;

                break;
              }
          }
          if( somethingCollapsed ) break;
      }
  } while( somethingCollapsed );
};
void Sandpile::update(){
  dropGrain();
  collapseGrains();
}
void Sandpile::render(float r, float g, float b, float space){
  int centerX = size / 2;
  int centerY = size / 2;

  glColor3f(r, g, b);
  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j){
      int diffX = i - centerX;
      int diffY = j - centerY;


      drawCircle(x + diffX * (2*space), y + diffY * (2*space), sandpile2d[i][j]);
    }
  }
}
void Sandpile::print(){
  for( int i = 0; i < size; i++ ){
    for( int j = 0; j < size; j++ ){
      cout << sandpile2d[i][j] << " ";
    }
    cout << endl;
  }
}
void Sandpile::run(float space){
  update();
  print();
  render(1, 1, 0, space);
}
Sandpile::~Sandpile() {}
