cmake_minimum_required(VERSION 3.10)
project(project)

set(CMAKE_CXX_STANDARD 11)

include_directories(Base)
include_directories(Flocking)
include_directories(helpers)
include_directories(LSystems)
include_directories(PredatorPrey)
include_directories(Sugarscape)
include_directories(TuringPattern)

add_executable(project
        Base/Figure.cpp
        Base/Figure.h
        Base/Turtle.cpp
        Base/Turtle.h
        Base/Vector2d.cpp
        Base/Vector2d.h
        Flocking/Boid.cpp
        Flocking/Boid.h
        helpers/helpers.cpp
        helpers/helpers.h
        LSystems/LSystem.cpp
        LSystems/LSystem.h
        PredatorPrey/Predator.cpp
        PredatorPrey/Predator.h
        PredatorPrey/PredatorPrey.cpp
        PredatorPrey/PredatorPrey.h
        Sugarscape/Sandpile.cpp
        Sugarscape/Sandpile.h
        Sugarscape/Sugarscape.cpp
        Sugarscape/Sugarscape.h
        TuringPattern/TuringPattern.cpp
        TuringPattern/TuringPattern.h
        main.cpp)
