CC = g++
FLAGS = -std=c++11 -lglut -lGL -lGLEW -lGLU -Wfatal-errors

all: main

main: main.o oglhelpers.o Vector2d.o Figure.o Turtle.o LSystem.o Boid.o PredatorPrey.o Predator.o Sandpile.o Sugarscape.o
	$(CC) oglhelpers.o \
		Vector2d.o \
		Figure.o \
		Turtle.o \
		LSystem.o \
		Boid.o \
		PredatorPrey.o \
		Predator.o \
		Sandpile.o \
		Sugarscape.o \
		main.o $(FLAGS) -o \
		main 

main.o: main.cpp
	$(CC) -c $(FLAGS) main.cpp

oglhelpers.o: ./helpers/oglhelpers.cpp
	$(CC) -c $(FLAGS) ./helpers/oglhelpers.cpp

Vector2d.o: ./Base/Vector2d.cpp
	$(CC) -c $(FLAGS) ./Base/Vector2d.cpp

Figure.o: ./Base/Figure.cpp
	$(CC) -c $(FLAGS) ./Base/Figure.cpp

Turtle.o: ./Base/Turtle.cpp
	$(CC) -c $(FLAGS) ./Base/Turtle.cpp

LSystem.o: ./LSystems/LSystem.cpp
	$(CC) -c $(FLAGS) ./LSystems/LSystem.cpp

Boid.o: ./Flocking/Boid.cpp
	$(CC) -c $(FLAGS) ./Flocking/Boid.cpp

PredatorPrey.o: ./PredatorPrey/PredatorPrey.cpp
	$(CC) -c $(FLAGS) ./PredatorPrey/PredatorPrey.cpp

Predator.o: ./PredatorPrey/Predator.cpp
	$(CC) -c $(FLAGS) ./PredatorPrey/Predator.cpp

Sandpile.o: ./Sugarscape/Sandpile.cpp
	$(CC) -c $(FLAGS) ./Sugarscape/Sandpile.cpp

Sugarscape.o: ./Sugarscape/Sugarscape.cpp
	$(CC) -c $(FLAGS) ./Sugarscape/Sugarscape.cpp

run:
	./main

clean:
	rm -f *o main