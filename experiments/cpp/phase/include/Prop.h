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

#ifndef _PHASE_PROP_H_
#define _PHASE_PROP_H_

#include <memory>

namespace Phase 
{

namespace Internal 
{
class PropBase {
protected:
  //  virtual void CopyNextValueToCurrent() = 0;

    template<typename Domain> friend class Entity;
};
}

template<typename T>
class Prop : public Internal::PropBase {
public:
    Prop(const T& initialValue) 
    {
        m_value[0] = initialValue;
        m_value[1] = initialValue;
    }

protected:
//    virtual void CopyNextValueToCurrent() override { m_current = m_next; }

private:
    template<typename Domain> friend class Entity;
    
    T m_value[2];
    /*T m_current;
    T m_next;*/
};

}

#endif
