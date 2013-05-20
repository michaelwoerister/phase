/*
Copyright (c) 2013 Michael Woerister

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <cassert>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <Phase.h>

#include "Paddle.h"
#include "Ball.h"
 
const sf::Int64 TARGET_FRAME_TIME = 1000000 / 60;

int main()
{ 
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Phase - Pong Example");
    sf::Clock clock;

    Pong::PongContext ctx;
    
    ctx.GetEntities().Add(new Pong::PaddleEntity(&ctx, Pong::PaddleEntity::Left));
    ctx.GetEntities().Add(new Pong::PaddleEntity(&ctx, Pong::PaddleEntity::Right));
    ctx.GetEntities().Add(new Pong::Ball(&ctx));

    sf::Int64 timeAccu = 0;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return EXIT_SUCCESS;
            }
        }

        timeAccu += clock.restart().asMicroseconds();

        if (timeAccu < TARGET_FRAME_TIME)
            continue;

        while (timeAccu >= TARGET_FRAME_TIME)
        {
            // Collect Input
            Pong::Pong::UpdateParamExtensions updateParams;

            updateParams.InputLeftUp = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            updateParams.InputLeftDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            updateParams.InputRightUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            updateParams.InputRightDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

            // Update Game State
            ctx.Update((float) (TARGET_FRAME_TIME / 1000000.0), updateParams);
            timeAccu -= TARGET_FRAME_TIME;
        }

        // Clear screen
        window.clear();

        for (auto entity : ctx.GetEntities())
        {
            static_cast<const Pong::PongEntity*>(entity)->Draw(window);
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
} 