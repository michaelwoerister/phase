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

#include "EntityContainer.h"
#include "Internal\FieldSetter.h"

namespace Phase 
{

class Context {
public:
    Context() : m_entities(*this) {}

    void Update(const float dt);

    template<typename T> void ScheduleUpdate(T& target, const T& value) { m_updates.push_back(new Internal::FieldSetter<T>(target, value));  }
    template<typename T> void ScheduleUpdate(T& target, T&& value)
    {
        auto setter = new Internal::FieldSetter<T>(target, std::move(value));
        m_updates.push_back(std::unique_ptr<Internal::IMutator>(setter)); 
    }

private:
    EntityContainer m_entities;
    std::vector<std::unique_ptr<Internal::IMutator>> m_updates;
    
};

}

#endif
