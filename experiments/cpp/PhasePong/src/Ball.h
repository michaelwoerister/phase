#ifndef _PONG_BALL_H_
#define _PONG_BALL_H_

#include "PongEntity.h"
#include "Paddle.h"

#include <SFML/Graphics.hpp>

namespace Pong 
{

class Ball : public PongEntity {
private:
    enum {
        RADIUS = 10
    };

public:
    Phase::Prop<sf::Vector2f> Position;
    Phase::Prop<sf::Vector2f> Velocity;

    Ball(PongContext *const ctx): 
        PongEntity(ctx), 
        Position(sf::Vector2f(400, 300)), 
        Velocity(sf::Vector2f(100, 400)), 
        m_shape(RADIUS) 
    {}

    void Update(const PongUpdateParams& params) const override
    {
        sf::Vector2f nextVelocity = Current(Velocity);

        if (CollidingWithTop())
            nextVelocity.y = abs(nextVelocity.y);
        
        if (CollidingWithBottom())
            nextVelocity.y = -abs(nextVelocity.y);

        Next(Velocity) = nextVelocity;
        Next(Position) = Current(Position) + Current(Velocity) * params.dt;
    }

    void Draw(sf::RenderTarget& rt) const override
    {
        m_shape.setPosition(Current(this->Position) - sf::Vector2f(RADIUS, RADIUS));
        rt.draw(m_shape);
    }

private:

    bool CollidingWithTop() const { return (Current(Position).y - RADIUS <= 0); }
    bool CollidingWithBottom() const { return (Current(Position).y + RADIUS >= Pong::FIELD_SIZE_Y); }

    

    mutable sf::CircleShape m_shape;
};

}

#endif
