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

#ifndef _PHASE_ENTITY_CONTAINER_H_
#define _PHASE_ENTITY_CONTAINER_H_

#include <vector>

#include "Entity.h"

namespace Phase 
{

class Context;

class EntityContainer {
public:
    typedef std::vector<Entity*> EntityVector;
    typedef std::vector<const Entity*> ConstEntityVector;
    typedef ConstEntityVector::const_iterator ConstIterator;

    ConstIterator begin() const { return this->const_view().cbegin(); }
    ConstIterator end() const { return this->const_view().cend(); }
    
    EntityContainer(Context &ctx): m_context(ctx) {}

private:
    EntityVector m_entities;
    Context &m_context;

    const ConstEntityVector& const_view() const { return *reinterpret_cast<const ConstEntityVector*>(&m_entities); }

    friend void operator>>(const Entity* const, const EntityContainer&);
};

void operator>>(const Entity* const, const EntityContainer&);

}

#endif
