main:
	g++ ./project/helpers/oglhelpers.cpp \
		./project/Base/Vector2d.cpp \
		./project/Base/Figure.cpp \
		./project/Base/Turtle.cpp \
		./project/LSystems/LSystem.cpp \
		./project/Flocking/Boid.cpp \
		./project/PredatorPrey/PredatorPrey.cpp \
		./project/PredatorPrey/Predator.cpp \
		./project/Sugarscape/Sandpile.cpp \
		./project/Sugarscape/Sugarscape.cpp \
		./project/main.cpp -std=c++11 -o \
	./project/main -lglut -lGL -lGLEW -lGLU -Wfatal-errors\
	 && ./project/main
lsystems:
	g++ ./LSystems/lsystems.cpp -std=c++11 -o ./LSystems/lsystems -lglut -lGL -lGLEW -lGLU && ./LSystems/lsystems
affineTransform:
	g++ -ggdb ./AffineTransform/affineTransform.cpp -o ./AffineTransform/affineTransform \
				`pkg-config --cflags --libs opencv` && ./AffineTransform/affineTransform $(file)
triangle: triangle.o
	g++ triangle.cpp -o triangle -std=c++11 -lglut -lGL -lGLEW -lGLU -lSOIL && ./triangle
