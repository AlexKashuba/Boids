#include "Boid.h"
#include <SFML/Graphics.hpp>


Boid:: Boid(sf::Vector2i positionOfBoid){
    position = positionOfBoid;
    velocity.x = 0;
    velocity.y = 0;
}

Boid:: Boid(){
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
}
