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

#ifndef _PHASE_CONTEXT_H_
#define _PHASE_CONTEXT_H_

#include <memory>
#include <vector>
#include <cassert>

#include "EntityContainer.h"
#include "UpdateParams.h"

namespace Phase
{

enum UpdateState 
{
    COLLECTING_CHANGES,
    POST_UPDATE
};


template<typename Domain>
class Context {
public:

    
    Context() : m_current(0), m_next(1) {}

    void Update(const float dt, const typename Domain::UpdateParamExtensions& params)
    {
        const UpdateParams<Domain> fullParams(dt, m_entities, params);

        m_state = COLLECTING_CHANGES;

        // Collect Changes
        for (const Entity<Domain> * e : m_entities)
        {
            e->Update(fullParams);
        }

        std::swap(m_current, m_next);
        m_state = POST_UPDATE;

        // Apply Updates
        for (const Entity<Domain> * e : m_entities)
        {
            const_cast<Entity<Domain> *>(e)->PostUpdate();
        }
    }

    const EntityContainer<Domain> & GetEntities() const { return m_entities; }
    EntityContainer<Domain> & GetEntities() { return m_entities; }

    const std::size_t GetCurrent() const { return m_current; }
    const std::size_t GetNext() const { return m_next; }
    const UpdateState GetState() const { return m_state; }

private:
    std::size_t m_current;
    std::size_t m_next;
    UpdateState m_state;
    EntityContainer<Domain> m_entities;
};



}

#endif
