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
 
#include <Entity.h>
#include <Context.h>

// from: http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T> T clamp(T val, const T min, const T max) {
    assert(min <= max);

    if (val < min) val = min;
    else if (val > max) val = max;

    return val;
}


class PongEntity;

struct Pong 
{
    typedef PongEntity EntityType;
 
    struct UpdateParamExtensions
    {
       bool InputLeftUp;
       bool InputLeftDown;
       bool InputRightUp;
       bool InputRightDown;
    };
};

typedef Phase::Context<Pong> PongContext;
typedef Phase::EntityContainer<Pong> PongEntityContainer;
typedef Phase::UpdateParams<Pong> PongUpdateParams;

class PongEntity : public Phase::Entity<Pong> {
public:
    PongEntity(PongContext &ctx): Entity(ctx) {}
    virtual void Draw(sf::RenderTarget& rt) const = 0;
};


class PaddleEntity : public PongEntity {
public:

    static const sf::Vector2f Size;
    static const float MinPosY;
    static const float MaxPosY;

    enum SideType { Left, Right };
    
    const SideType Side;
    
    Phase::Prop<sf::Vector2f> Position;    
    Phase::Prop<float> Velocity;

    PaddleEntity(PongContext& context, const SideType side): 
        PongEntity(context),
        Side(side),
        Position(GetInitialPosition(side)),
        Velocity(0),
        m_shape(Size)
    {}

    virtual void Update(const PongUpdateParams& params) const override
    {
        float movement = 0;
        
        if (this->Side == Left)
        {
            if (params.InputLeftUp) movement -= 1;
            if (params.InputLeftDown) movement += 1;
        }
        else
        {
            assert(this->Side == Right);

            if (params.InputRightUp) movement -= 1;
            if (params.InputRightDown) movement += 1;
        }

        const float nextPosYNoClamp = Current(Position).y + Current(Velocity) * params.dt;
        
        if (nextPosYNoClamp > MinPosY && nextPosYNoClamp < MaxPosY)
        {
            const float dec = sgn(Current(Velocity)) != sgn(movement) ? 0.9f : 0.97f;
            Next(Velocity) = (Current(Velocity) + movement * GetAccelerationFor(Current(Velocity)) * params.dt) * dec;
            Next(Position) = sf::Vector2f(GetPositionX(), nextPosYNoClamp);
        }
        else
        {
            Next(Velocity) = movement * GetAccelerationFor(Current(Velocity)) * params.dt;
            Next(Position) = sf::Vector2f(GetPositionX(), clamp(nextPosYNoClamp, MinPosY, MaxPosY));
        }
    }

    void Draw(sf::RenderTarget& rt) const
    {
        m_shape.setPosition(this->Position);
        rt.draw(m_shape);
    }

private:

    float GetPositionX() const
    {
        return this->Side == Left ? Size.x * 1.4 : 800 - Size.x * 2.4;
    }

    static float GetAccelerationFor(const float currentVelocity)
    {
        const float MAX_VELOCITY = 800;
        const float MAX_ACC = 3000;

        const float absCurrentVelocity = abs(currentVelocity);

        if (absCurrentVelocity >= MAX_VELOCITY)
            return 0;

        return MAX_ACC * (1.0f - absCurrentVelocity / MAX_VELOCITY);
    }

    static sf::Vector2f GetInitialPosition(SideType side)
    {
        if (side == Left)
        {
            return sf::Vector2f(Size.x, 300 - Size.y / 2);
        }
        else
        {
            assert(side == Right);
            return sf::Vector2f(800 - Size.x * 2, 300 - Size.y / 2);
        }
    }

    mutable sf::RectangleShape m_shape;
};

const sf::Vector2f PaddleEntity::Size(20, 100);
const float PaddleEntity::MinPosY = 2;
const float PaddleEntity::MaxPosY = 600 - 2 - PaddleEntity::Size.y;

const sf::Int64 TARGET_FRAME_TIME = 1000000 / 60;
      

int main()
{ 
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Phase - Pong Example");
    sf::Clock clock;

    PongContext ctx; 
    ctx.GetEntities().Add(new PaddleEntity(ctx, PaddleEntity::Left));
    ctx.GetEntities().Add(new PaddleEntity(ctx, PaddleEntity::Right));

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
            Pong::UpdateParamExtensions updateParams;

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
            static_cast<const PongEntity*>(entity)->Draw(window);
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}