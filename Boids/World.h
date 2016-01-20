#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Boid.h"

class World {
    public:
        World(int, std::pair<int, int>);
        std::vector<Boid> Boids;
        std::vector<Boid> new_Boids_state;
        void moveAllBoidsToNewPosition(void);
        sf::Vector2i target;
    private:
        sf::Vector2i firstRule(const Boid&);
        sf::Vector2i secondRule(const Boid&);
        sf::Vector2i thirdRule(const Boid&);
        sf::Vector2i fourthRule(const Boid&);
        sf::Vector2i limitVelocity(Boid&, int velocityLimit);
        int numberOfBoids;
        std::pair<int, int> worldSize;
};

#endif // WORLD_H
