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

#include <Guier/Control/Button.hpp>
#include <Guier/Control/VerticalGrid.hpp>
#include <Guier/Control/Text.hpp>

namespace Guier
{

    Button::Button(Parent * parent, const String & label) :
        Control(this, parent, Index::Last, Size::Fit),
        Parent(),
        m_Size(Size::Fit)
    {
        CreateText(label);
    }

    Button::Button(Parent * parent, const Index & index, const String & label) :
        Control(this, parent, index, Size::Fit),
        Parent(),
        m_Size(Size::Fit)
    {
        CreateText(label);
    }

    Button::Button(Parent * parent, const Index & index, const Vector2i & size, const String & label) :
        Control(this, parent, index, size),
        Parent(),
        m_Size(size)
    {
        CreateText(label);
    }

    Button::Button(Parent * parent, const Vector2i & size, const String & label) :
        Control(this, parent, Index::Last, size),
        Parent(),
        m_Size(size)
    {
        CreateText(label);
    }

    Button::~Button()
    {

    }

    unsigned int Button::Type() const
    {
        return static_cast<unsigned int>(Types::Button);
    }

    bool Button::AddChild(Control * child, const Index & index)
    {
        if (child == nullptr)
        {
            return false;
        }

        if (m_pChild)
        {
            delete m_pChild;
        }
        m_pChild = child;

        return true;
    }

    bool Button::RemoveChild(Control * child)
    {
        if (child == nullptr || m_pChild == nullptr)
        {
            return false;
        }

        m_pChild = nullptr;

        return true;
    }

    Control * Button::RemoveChild(const Index & index)
    {
        Control * pOldChild = m_pChild;
        m_pChild = nullptr;

        return pOldChild;
    }

    void Button::CreateText(const String & label)
    {
        // Create text control if label length != 0.
        const std::wstring & text = label.Get();
        if (text.size())
        {
            Add(new Text(this, label));
        }
    }

}