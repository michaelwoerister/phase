#ifndef _PADDLE_ENTITY_H_
#define _PADDLE_ENTITY_H_

#include <cassert>
#include <SFML/Graphics.hpp>
#include <Phase.h>

#include "Util.h"
#include "PongEntity.h"

namespace Pong
{


class Paddle : public PongEntity {
public:

    enum { 
        SIZE_X = 20, 
        SIZE_Y = 100, 
        MIN_POS_Y = 2, 
        MAX_POS_Y = Pong::FIELD_SIZE_Y - MIN_POS_Y - SIZE_Y
    };

    enum SideType { Left, Right };
    const SideType Side;
    
    Phase::Prop<sf::Vector2f> Position;    
    Phase::Prop<float> Velocity;

    sf::FloatRect GetBounds() const { return sf::FloatRect(Current(Position), sf::Vector2f(SIZE_X, SIZE_Y)); }

    Paddle(PongContext *const context, const SideType side): 
        PongEntity(context),
        Side(side),
        Position(GetInitialPosition(side)),
        Velocity(0),
        m_shape(sf::Vector2f(SIZE_X, SIZE_Y))
    {}

    void Update(const PongUpdateParams& params) const override
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
        
        if (nextPosYNoClamp > MIN_POS_Y && nextPosYNoClamp < MAX_POS_Y)
        {
            const float dec = sgn(Current(Velocity)) != sgn(movement) ? 0.86f : 0.98f;
            Next(Velocity) = (Current(Velocity) + movement * GetAccelerationFor(Current(Velocity)) * params.dt) * dec;
            Next(Position) = sf::Vector2f(GetPositionX(), nextPosYNoClamp);
        }
        else
        {
            Next(Velocity) = movement * GetAccelerationFor(Current(Velocity)) * params.dt;
            Next(Position).y = clamp(nextPosYNoClamp, (float)MIN_POS_Y, (float)MAX_POS_Y);
        }
    }

    void PostUpdate() override { m_shape.setPosition(Current(Position)); }

    void Draw(sf::RenderTarget& rt) const override
    {
        rt.draw(m_shape);
    }

private:

    float GetPositionX() const
    {
        return this->Side == Left ? SIZE_X * 1.4f : Pong::FIELD_SIZE_X - SIZE_X * 2.4f;
    }

    static float GetAccelerationFor(const float currentVelocity)
    {
        const float MAX_VELOCITY = 1000;
        const float MAX_ACC = 3500;

        const float absCurrentVelocity = abs(currentVelocity);

        if (absCurrentVelocity >= MAX_VELOCITY)
            return 0;

        return MAX_ACC * (1.0f - absCurrentVelocity / MAX_VELOCITY);
    }

    static sf::Vector2f GetInitialPosition(SideType side)
    {
        if (side == Left)
        {
            return sf::Vector2f(SIZE_X, (Pong::FIELD_SIZE_Y - SIZE_Y) / 2);
        }
        else
        {
            assert(side == Right);
            return sf::Vector2f(Pong::FIELD_SIZE_X - SIZE_X * 2, (Pong::FIELD_SIZE_Y - SIZE_Y) / 2);
        }
    }

    sf::RectangleShape m_shape;
};


}

#endif
