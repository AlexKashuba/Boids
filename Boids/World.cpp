#include "World.h"
#include "Boid.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

World::World(int numOfBoids, std::pair<int, int> windowSize){
    numberOfBoids = numOfBoids;
    std::srand(std::time(0));
    
    worldSize.first = windowSize.first+50;
    worldSize.second = windowSize.second+50;
    
    target.x = worldSize.first/2;
    target.y = worldSize.second/2;
    
    int rand_x, rand_y;
    sf::Vector2i currentBoidPosition;
    
    Boids.resize(numberOfBoids);
    new_Boids_state.resize(numberOfBoids);

    for(int i = 0; i<numberOfBoids; i++){
        rand_x = rand()%(worldSize.first);
        rand_y = rand()%(worldSize.second);
        currentBoidPosition.x = rand_x;
        currentBoidPosition.y = rand_y;
        Boids[i] = Boid(currentBoidPosition);
    }
}

sf::Vector2i World::firstRule(const Boid &boid){
    sf::Vector2i new_position;
    for(int i = 0; i<numberOfBoids; i++){
        if(Boids[i].position!=boid.position || Boids[i].velocity!=boid.velocity){
            new_position+=Boids[i].position;
        }
    }

    new_position /= numberOfBoids-1;
    
    new_position -= boid.position;

    new_position /= 100;

    return new_position;
}

sf::Vector2i World::secondRule(const Boid &boid){
    sf::Vector2i new_position, dist;
    for(int i = 0; i<numberOfBoids; i++){
        if(Boids[i].position!=boid.position || Boids[i].velocity!=boid.velocity){
            dist = Boids[i].position-boid.position;
            if(sqrt(dist.x*dist.x+dist.y*dist.y)<40){
                new_position-=dist;
            }
        }
    }

    return new_position;
}

sf::Vector2i World::thirdRule(const Boid &boid){
    sf::Vector2i new_velocity;
    for(int i = 0; i<numberOfBoids; i++){
        if(Boids[i].position!=boid.position || Boids[i].velocity!=boid.velocity){
            new_velocity+=Boids[i].velocity;
        }
    }

    new_velocity /= numberOfBoids-1;
    new_velocity -= boid.velocity;
    new_velocity /= 20;

    return new_velocity;
}

sf::Vector2i World::fourthRule(const Boid &boid){
    sf::Vector2i new_velocity = target-boid.position;
    return (new_velocity)/50;
}

sf::Vector2i World::limitVelocity(Boid &boid, int velocityLimit){
    int speed = sqrt(boid.velocity.x*boid.velocity.x+boid.velocity.y*boid.velocity.y);
    sf::Vector2i new_velocity = boid.velocity;
    if(speed>velocityLimit){
        new_velocity.x = ((float)boid.velocity.x/(float)speed)*(velocityLimit);
        new_velocity.y = ((float)boid.velocity.y/(float)speed)*(velocityLimit);
    }
    
    return new_velocity;
}



void World::moveAllBoidsToNewPosition(){
    sf::Vector2i v1, v2, v3, v4;
    for(int j =0; j<numberOfBoids; j++){
        v1 = firstRule(Boids[j]);
        v2 = secondRule(Boids[j]);
        v3 = thirdRule(Boids[j]);
        v4 = fourthRule(Boids[j]);
        
        Boid new_Boid = Boids[j];

        new_Boid.velocity += v1+v2+v3+v4;
        new_Boid.velocity = limitVelocity(new_Boid, 100);
        new_Boid.position+=new_Boid.velocity;
        new_Boids_state[j] = new_Boid;
    }
    
    Boids = new_Boids_state;
}
