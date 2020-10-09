// Snek.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective, glm:vectors
#include "Renderer.h"
#include "io.h"
#include "snake.h"
#include "XInputMapping.h"
using namespace sf; //SFML


int main()
{
    //Configuring SFML window
    sf::ContextSettings window_settings;
    window_settings.depthBits = 24; // Request a 24-bit depth buffer
    window_settings.stencilBits = 8;  // Request an 8-bit stencil buffer
    window_settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing

    // Opening SFML window
    sf::Window window(sf::VideoMode(1280, 720), "Snake3D", sf::Style::Resize | sf::Style::Close, window_settings);
    window.setFramerateLimit(60);
    UINT framecount = 0;

    Renderer::initRenderer(window);
    
    snake mainSnake = snake(glm::vec3(0, 0, 0)); //initial position 0
    mainSnake.setPathLength(1024); //1024 max length for testing
    XInputMapping* Player1 = new XInputMapping(1);

    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    std::cout << "Game has started!\n";
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) //Close window action
            if (event.type == Event::Closed)
                window.close();
        window.display();
        framecount++;
        io::readMainInputs(Player1, framecount); //Read start button for now
        if (Renderer::paused) continue; //skip any game processing if pause is activated
        io::readSnakeInputs(mainSnake, framecount, Player1);
        //Draw snake and grids for testing
        Renderer::Render(window, mainSnake.getPosition());
        mainSnake.drawSnake();
        Renderer::drawGrid(45.f, 45.f, 45, 45, 0.f);
        glPushMatrix();
        glTranslatef(0., 20.f, 45.f);
        glRotatef(90.f, 1.f, 0.f, 0.f);
        Renderer::drawGrid(45.f, 20.f, 45, 20, 0.f);
        glPopMatrix();
    }

    return 0;
}