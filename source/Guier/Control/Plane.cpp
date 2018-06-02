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
        Control(this, parent, Index::Last, Size::Fit),
        Parent()
    {

    }
        Plane::Plane(Parent * parent, const Vector2i & position, const Vector2i & size) :
        Control(this, parent, Index::Last, Size::Fit),
        Parent()
    {

    }

    Plane::~Plane()
    {

    }

    unsigned int Plane::Type() const
    {
        return static_cast<unsigned int>(Types::Plane);
    }

    bool Plane::AddChild(Control * child, const Index & index)
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

    bool Plane::RemoveChild(Control * child)
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

    Control * Plane::RemoveChild(const Index & index)
    {
        const int pos = index.GetSingleInteger();

        if (pos > m_Childs.size())
        {
            return nullptr;
        }

        auto it = m_Childs.begin();
        std::advance(it, pos);
        Control * pControl = *it;
        m_Childs.erase(it);

        return pControl;
    }

    void Plane::Render(Core::Renderer::Interface * renderInterface)
    {
        for (auto it = m_Childs.begin(); it != m_Childs.end(); it++)
        {
            renderInterface->RenderControl(*it, { {},{} });
        }
    }

}