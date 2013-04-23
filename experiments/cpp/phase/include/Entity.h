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

#ifndef _PHASE_ENTITY_H_
#define _PHASE_ENTITY_H_

#include "ConstAddress.h"
#include "Prop.h"
#include "ContextBoundProperty.h"

namespace Phase {

// Forward Declarations
class Context;
class EntityContainer;

class Entity : private Internal::ConstAddress {
public:
    Entity(Context &context) : m_context(context) {}

    virtual void Update(const EntityContainer& entities) const = 0;

    template<typename T>
    Internal::ContextBoundProperty<T> Next(const Prop<T>& p) const { return Internal::ContextBoundProperty<T>(p, m_context); }

private:
    Context& m_context;
};

}

#endif
