#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>

class Boid {
    public:
        Boid();
        Boid(sf::Vector2i positionOfBoid);
        sf::Vector2i position;
        sf::Vector2i velocity;
};


#endif // BOID_H
