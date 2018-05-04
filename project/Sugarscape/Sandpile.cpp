#include <iostream>

#include "../helpers/oglhelpers.h"
#include "Sandpile.h"

Sandpile::Sandpile(){
  position.setXY(400, 400);
  size = 16;
  capacity = 20;
  grainResource = capacity / 10;
  initializeMatrix();
  calculateGrainLocations();
  calculateRadious();
}
Sandpile::Sandpile(float x, float y, int size, float capacity){
  position.setXY(x, y);
  
  this->size = size;
  this->capacity = capacity;

  grainResource = capacity / 5;
  
  initializeMatrix();
  calculateGrainLocations();
  calculateRadious();
};
Sandpile::Sandpile(Vector2d position, int size, float capacity){
  float x, y;
  tie(x, y) = position.getTuple();
  
  this->position = Vector2d(x, y);
  this->size = size;
  this->capacity = capacity;

  grainResource = capacity / 5;
  
  initializeMatrix();
  calculateGrainLocations();
  calculateRadious();
};
void Sandpile::initializeMatrix(){
  sandpile2d = vector<vector<int>>(size, std::vector<int>(size));

  for(int i = 0; i < size * capacity; i++){
      dropGrain();
      collapseGrains();
  }
}
void Sandpile::calculateGrainLocations(){
  grainLocations = vector<vector<Vector2d>>(size, std::vector<Vector2d>(size));

  float centerX = size / 2.0;
  float centerY = size / 2.0;

  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j){
      int diffX = i - centerX;
      int diffY = j - centerY;

      float x = position.getX() + diffX * (0.2*capacity);
      float y = position.getY() + diffY * (0.2*capacity);
      
      grainLocations[i][j] = Vector2d(x, y);
    }
  }
}
void Sandpile::calculateRadious(){
  float centerX = size / 2.0;
  float centerY = size / 2.0;

  int farthestDistanceX = (size-1 - centerX) * (0.2*capacity);
  int farthestDistanceY = (size-1 - centerY) * (0.2*capacity);
  
  radious = sqrt( pow(farthestDistanceX, 2) + pow(farthestDistanceY, 2) );
}
Vector2d Sandpile::getPosition(){
  return position;
}
float Sandpile::getRadious(){
  return radious;
};
float Sandpile::getCapacity(){
  return capacity;
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

    for (int i = 0; i < size; ++i){
          for (int j = 0; j < size; ++j){
            if( sandpile2d[i][j] >= capacity ){
                sandpile2d[i][j] = 0;

                updateNeighbours(i, j);

                somethingCollapsed = true;
                break;
              }
          }
          if( somethingCollapsed ) break;
      }
  } while( somethingCollapsed );
}
Vector2d Sandpile::getBestGrainLocation(Vector2d position){
  float minDistance = 2000;
  Vector2d bestLocation;
  int currentI, currentJ;
  bool anyBest = false;

  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j){
      Vector2d location = grainLocations[i][j];
      float distance = Vector2d::dist(location, position);

      if( anyBest && distance <= minDistance ){
        int currentResource = sandpile2d[currentI][currentJ];
        
        int tentativeI = i;
        int tentativeJ = j;

        int tentativeResource = sandpile2d[tentativeI][tentativeJ];

        if( tentativeResource > currentResource ){
          bestLocation = location;
        }
      }else if( distance < minDistance ){
        minDistance = distance;
        bestLocation = location;
      } 
    }
  }
  
  return bestLocation;
}
int Sandpile::getResource(Vector2d foodPosition){
  float x, y;
  tie(x, y) = foodPosition.getTuple();

  float centerX = size / 2.0;
  float centerY = size / 2.0;

  int i = (( x - position.getX() ) / (0.2*capacity)) + centerX;
  int j = (( y - position.getY() ) / (0.2*capacity)) + centerY;

  int resource = sandpile2d[i][j];
  
  sandpile2d[i][j] = 0;

  return resource;
}
void Sandpile::update(){
  dropGrain();
  collapseGrains();
}
void Sandpile::render(float r, float g, float b){
  glColor3f(r, g, b);
  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j){
      drawCircle(grainLocations[i][j].getX(), 
                  grainLocations[i][j].getY()
                  , sandpile2d[i][j] / 10);
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
void Sandpile::run(){
  update();
  //print();
  render(1, 1, 0);
}
Sandpile::~Sandpile() {}
