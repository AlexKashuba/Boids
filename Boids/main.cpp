#include <SFML/Graphics.hpp> //SFML VERSION 2.2
#include "World.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#define sgn(x) (x > 0) - (x < 0)


int numberOfBoids = 20;
std::vector<sf::CircleShape> boidsShapes(numberOfBoids);
std::pair<int, int> windowSize (2200, 1300);
World world(numberOfBoids, windowSize);
sf::RenderWindow window(sf::VideoMode(windowSize.first, windowSize.second), "Boids");

void drawBoids(){
    world.moveAllBoidsToNewPosition();
    
    for(int j = 0; j<5; j++){
        window.clear(sf::Color::White);
        for(int i = 0; i<numberOfBoids; i++){
            int x_velocity = world.Boids[i].velocity.x;
            int x = (sgn(x_velocity))*abs(x_velocity/5);
            
            int y_velocity = world.Boids[i].velocity.y;
            int y = (sgn(y_velocity))*abs(y_velocity/5);
            
            boidsShapes[i].setPosition(boidsShapes[i].getPosition().x+x, boidsShapes[i].getPosition().y+y);
            window.draw(boidsShapes[i]);
        }
        window.display();
    }
    /*
    
    
    window.clear(sf::Color::White);
    for(int i = 0; i<numberOfBoids; i++){
        boidsShapes[i].setPosition(world.Boids[i].position.x, world.Boids[i].position.y);
        window.draw(boidsShapes[i]);
    }
    window.display();
     */
    
}

int main()
{
    world.moveAllBoidsToNewPosition();
    
    for(int i = 0; i<numberOfBoids; i++){
        boidsShapes[i] = *new sf::CircleShape(10.f, 3);
        boidsShapes[i].setFillColor(sf::Color::Blue);
        boidsShapes[i].setPosition(world.Boids[i].position.x, world.Boids[i].position.y);
        if(i==numberOfBoids-1)
            boidsShapes[i].setFillColor(sf::Color::Red);
    }
    
    sf::Clock clock;
    window.setVerticalSyncEnabled(true);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved){
                world.target = sf::Mouse::getPosition(window);
            }
        }

        drawBoids();
        
        sf::Int32 t = clock.restart().asMilliseconds();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000-t)/48);
    }

    return 0;
}
