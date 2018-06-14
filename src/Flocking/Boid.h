#ifndef BOID_H_
#define BOID_H_

#include <vector>

#include "../Base/Vector2d.h"
#include "../Base/Turtle.h"
#include "../PredatorPrey/Predator.h"
#include "../Sugarscape/Sugarscape.h"
#include "../Sugarscape/Sandpile.h"
#include "../helpers/helpers.h"

using namespace std;

class Predator;

class Boid: public Turtle {
    using Turtle::Turtle;
	protected:
        bool alreadyReproduced;
        float reproductionProb;
    public:
        static float fit_value(Boid);
        static string encode(Boid);
        static Boid decode(string dna, float x, float y, GLuint texture);
        Boid();
        Boid(float x, float y, float r, float g, float b, GLuint texture);
        Boid(float x, float y, float r, float g, float b, GLuint texture, int life, float vision, float maxSpeed);
        virtual ~Boid();
        bool getAlreadyReproduced();
        void setAlreadyReproduced(bool);
        Vector2d separate(vector<Boid>);
        Vector2d align(vector<Boid>);
        Vector2d seek(Vector2d);
        Vector2d cohere(vector<Boid>);
        Vector2d escape(vector<Predator>);
        void eat(Vector2d foodPosition, Sandpile sandpile);
        Vector2d search_food(Sugarscape);
        static vector<string> crossover(string dna1, string dna2);
        static void mutate(string& dna);
        void reproduce(vector<Boid>& boids, int mate_index);
        Vector2d mate_selection(vector<Boid>& boids, bool& reproduced);
        void flock(vector<Boid>& boids, vector<Predator>& predators, Sugarscape sugarscape, bool reproducing, bool& reproduced);
        bool run(vector<Boid>& boids, vector<Predator>& predators, Sugarscape sugarscape,
                                float velocityFactor, float maxWidth, float maxHeight, bool death, bool reproducing, bool& reproduced);
        string toString();
};
#endif /* BOID_H_ */

