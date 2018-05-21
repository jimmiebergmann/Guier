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
    Button::Button(Core::ControlParent * parent, const String & label) :
        ControlParent::VerticalGrid(this, this, parent),
        m_Size(Size::Fit)
    {
        CreateText(label);
    }

    Button::Button(Core::ControlParent * parent, const Index & parentIndex, const String & label) :
        ControlParent::VerticalGrid(this, this, parent),
        m_Size(Size::Fit)
    {
        CreateText(label);
    }

    Button::Button(Core::ControlParent * parent, const Vector2i & size, const String & label ) :
        ControlParent::VerticalGrid(this, this, parent),
        m_Size(size)
    {
        CreateText(label);

    }

    Button::Button(Core::ControlParent * parent, const Vector2i & size, const Index & parentIndex, const String & label) :
        ControlParent::VerticalGrid(this, this, parent),
        m_Size(size)
    {
        CreateText(label);
    }

    Button::~Button()
    {

    }

    bool Button::AddChild(Core::Control * control, const Index & index)
    {
        return ControlParent::VerticalGrid::Add(control, index);
    }

    bool Button::RemoveChild(Core::Control * control)
    {
        return ControlParent::VerticalGrid::RemoveChild(control);
    }

    Core::Control * Button::RemoveChild(const Index & index)
    {
        return ControlParent::VerticalGrid::RemoveChild(index);
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