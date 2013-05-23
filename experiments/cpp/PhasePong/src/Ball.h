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
        RADIUS = 10,
        MAX_SPEED = 500
    };

public:
    Phase::Prop<sf::Vector2f> Position;
    Phase::Prop<sf::Vector2f> Velocity;

    Ball(PongContext *const ctx): 
        PongEntity(ctx), 
        Position(sf::Vector2f(400, 300)), 
        Velocity(sf::Vector2f(400, 100)), 
        m_shape(RADIUS) 
    {}

    void Update(const PongUpdateParams& params) const override
    {
        auto nv = Current(Velocity);
        
        if (CollidingWithTop())
            nv.y = abs(nv.y);
        
        if (CollidingWithBottom())
            nv.y = -abs(nv.y);
        
        auto paddle = FindPaddle(params);

        if (CollidingWithPaddle(paddle))
        {
            nv.x = paddle->Side == Paddle::Left ? abs(nv.x) : -abs(nv.x);
            nv.y += Current(paddle->Velocity);
        }

        ClampSpeed(&nv);

        Next(Velocity) = nv;
        Next(Position) = Current(Position) + Current(Velocity) * params.dt;
    }

    void Draw(sf::RenderTarget& rt) const override
    {
        rt.draw(m_shape);
    }

    void PostUpdate() override { m_shape.setPosition(Current(this->Position) - sf::Vector2f(RADIUS, RADIUS)); }

private:

    bool CollidingWithTop() const { return (Current(Position).y - RADIUS <= 0); }
    bool CollidingWithBottom() const { return (Current(Position).y + RADIUS >= Pong::FIELD_SIZE_Y); }
    
    const Paddle* const FindPaddle(const PongUpdateParams& params) const 
    {
        auto side = Current(Velocity).x > 0 ? Paddle::Right : Paddle::Left;

        for (const PongEntity*const  e : params.Entities)
        {
            const Paddle* const paddle = dynamic_cast<const Paddle* const>(e);

            if (paddle != nullptr && paddle->Side == side) 
                return paddle;
        }

        return nullptr;
    }

    bool CollidingWithPaddle(const Paddle* const paddle) const 
    {
        return paddle->GetBounds().contains(Current(Position));
    }

    static void ClampSpeed(sf::Vector2f* v)
    {
        const float len = sqrtf(v->x * v->x + v->y * v->y);

        if (len > MAX_SPEED)
        {
            *v *= MAX_SPEED / len;
        }
    }

    sf::CircleShape m_shape;
};

}

#endif
