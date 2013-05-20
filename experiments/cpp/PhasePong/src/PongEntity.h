#ifndef _PONG_ENTITY_H_
#define _PONG_ENTITY_H_

#include <SFML/Graphics.hpp>
#include <Phase.h>

namespace Pong
{

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

    enum 
    {
        FIELD_SIZE_X = 800,
        FIELD_SIZE_Y = 600
    };
};

typedef Phase::Context<Pong> PongContext;
typedef Phase::EntityContainer<Pong> PongEntityContainer;
typedef Phase::UpdateParams<Pong> PongUpdateParams;

class PongEntity : public Phase::Entity<Pong> {
public:
    PongEntity(PongContext *const ctx): Entity(ctx) {}
    virtual void Draw(sf::RenderTarget& rt) const = 0;
};

}

#endif
