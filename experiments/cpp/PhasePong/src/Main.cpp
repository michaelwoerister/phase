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

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
 
#include <Entity.h>
#include <Context.h>

class PaddleEntity : public Phase::Entity {
public:

    const sf::Vector2f Size;
    Phase::Prop<sf::Vector2f> Position;    

    PaddleEntity(Phase::Context& context): 
        Entity(context),
        Size(20, 100),
        m_shape(sf::Vector2f(20, 100))
    {}

    void Update(const Phase::EntityContainer& entities) const override 
    {
            
    }

    void Draw(sf::RenderTarget& rt)
    {
        rt.draw(m_shape);
    }

private:

    sf::RectangleShape m_shape;
};

const sf::Int64 TARGET_FRAME_TIME = 1000000 / 60;
      

int main()
 {
     // Create the main window
     sf::RenderWindow window(sf::VideoMode(800, 600), "Phase - Pong Example");
     sf::Clock clock;
     
     Phase::Context ctx;

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
             ctx.Update((float) (TARGET_FRAME_TIME / 1000000.0));
         
             timeAccu -= TARGET_FRAME_TIME;
         }

         // Clear screen
         window.clear();

         // Update the window
         window.display();
     }
 
     return EXIT_SUCCESS;
 }