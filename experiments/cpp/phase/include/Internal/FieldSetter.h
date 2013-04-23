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

#ifndef _PHASE_INTERNAL_FIELD_SETTER_H_
#define _PHASE_INTERNAL_FIELD_SETTER_H_

#include "IMutator.h"

namespace Phase {
namespace Internal {

template <typename T>
class FieldSetter : public IMutator {
public:

    FieldSetter(T& target, const T& value) :
        m_target(target),
        m_value(value)
    {}

    FieldSetter(T& target, T&& value) :
        m_target(target),
        m_value(std::move(value))
    {}

    void Invoke()// override
    {
        m_target = m_value;
    }

private:
    T& m_target;
    T m_value;
};

}}

#endif
