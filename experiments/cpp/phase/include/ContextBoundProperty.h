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

#ifndef _PHASE_CONTEXT_BOUND_PROPERTY_H_
#define _PHASE_CONTEXT_BOUND_PROPERTY_H_

#include "Context.h"

namespace Phase
{

class Context;
class Entity;
template<typename T> class Prop;

namespace Internal
{

template<typename T>
class ContextBoundProperty {
public:
    void operator=(const T& value) const
    {
        m_context.ScheduleUpdate(const_cast<Prop<T>&>(m_property).m_value, value);
    }

    void operator=(T&& value) const
    {
        m_context.ScheduleUpdate(const_cast<Prop<T>&>(m_property).m_value, std::move(value));
    }

private:
    friend Entity;
    const Prop<T>& m_property;
    Context& m_context;

    ContextBoundProperty(const Prop<T>& p, Context& c) : m_property(p), m_context(c) {}
};

}}

#endif