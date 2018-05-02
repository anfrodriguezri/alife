main:
	g++ ./project/Figure.cpp \
		./project/Turtle.cpp \
		./project/oglhelpers.cpp \
		./project/LSystem.cpp \
		./project/main.cpp -std=c++11 -o \
	./project/main -lglut -lGL -lGLEW -lGLU \
	 && ./project/main
lsystems:
	g++ ./LSystems/lsystems.cpp -std=c++11 -o ./LSystems/lsystems -lglut -lGL -lGLEW -lGLU && ./LSystems/lsystems
affineTransform:
	g++ -ggdb ./AffineTransform/affineTransform.cpp -o ./AffineTransform/affineTransform \
				`pkg-config --cflags --libs opencv` && ./AffineTransform/affineTransform $(file)
fractalDim:
	g++ -ggdb ./FractalDim/fractalDim.cpp -o ./FractalDim/fractalDim \
				`pkg-config --cflags --libs opencv` && ./FractalDim/fractalDim $(file)