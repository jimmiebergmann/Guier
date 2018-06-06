/*
* MIT License
*
* Copyright(c) 2018 Jimmie Bergmann
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#include <Guier/Control/Plane.hpp>

namespace Guier
{

    Plane::Plane(Parent * parent, const Vector2i & size) :
        ParentControl(parent, Index::Last, Size::Fit)
    {

    }
        Plane::Plane(Parent * parent, const Vector2i & position, const Vector2i & size) :
            ParentControl(parent, Index::Last, Size::Fit)
    {

    }

    Plane::~Plane()
    {

    }

    unsigned int Plane::type() const
    {
        return static_cast<unsigned int>(Types::Plane);
    }

    bool Plane::addChild(Control * child, const Index & index)
    {
        for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
        {
            if (*it == child)
            {
                return false;
            }
        }

        m_Childs.push_back(child);

        return true;
    }

    bool Plane::removeChild(Control * child)
    {
        for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
        {
            if (*it == child)
            {
                m_Childs.erase(it);
                return true;
            }
        }

        return false;
    }

    Control * Plane::removeChild(const Index & index)
    {
        const int pos = index.singleInteger();

        if (pos < 0 || pos > static_cast<int>(m_Childs.size()))
        {
            return nullptr;
        }

        auto it = m_Childs.begin();
        std::advance(it, pos);
        Control * pControl = *it;
        m_Childs.erase(it);

        return pControl;
    }

    void Plane::render(Core::Renderer::Interface * renderInterface, const Vector2i & position, const Vector2i & size)
    {
        for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
        {
            renderInterface->renderControl(*it, position, size);
        }
    }

}