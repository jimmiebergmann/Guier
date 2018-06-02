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
#include <Guier/Core/RenderInterface.hpp>

namespace Guier
{

    Button::Button(Parent * parent, const String & label) :
        Control(this, parent, Index::Last, Size::Fit),
        Parent(),
        m_pVerticalGrid(new VerticalGrid(this))
    {
        AddLabel(label);
    }

    Button::Button(Parent * parent, const Index & index, const String & label) :
        Control(this, parent, index, Size::Fit),
        Parent(),
        m_pVerticalGrid(new VerticalGrid(this))
    {
        AddLabel(label);
    }

    Button::Button(Parent * parent, const Index & index, const Vector2i & size, const String & label) :
        Control(this, parent, index, size),
        Parent(),
        m_pVerticalGrid(new VerticalGrid(this))
    {
        AddLabel(label);
    }

    Button::Button(Parent * parent, const Vector2i & size, const String & label) :
        Control(this, parent, Index::Last, size),
        Parent(),
        m_pVerticalGrid(new VerticalGrid(this))
    {
        AddLabel(label);
    }

    Button::~Button()
    {
        delete m_pVerticalGrid;
    }

    unsigned int Button::Type() const
    {
        return static_cast<unsigned int>(Types::Button);
    }

    bool Button::AddChild(Control * child, const Index & index)
    {
        if (m_pVerticalGrid)
        {
            return m_pVerticalGrid->Add(child, index);
        }
        
        return false;
    }

    bool Button::RemoveChild(Control * child)
    {
        return m_pVerticalGrid->Remove(child);
    }

    Control * Button::RemoveChild(const Index & index)
    {
        return m_pVerticalGrid->Remove(index);
    }

    void Button::Render(Core::Renderer::Interface * renderInterface)
    {
        renderInterface->RenderRectangle(Vector2i(40, 40), Vector2i(100, 40), Color::Red);
    }

    void Button::AddLabel(const String & label)
    {
        // Create text control if label length != 0.
        const std::wstring & text = label.Get();
        if (text.size())
        {
            Add(new Text(this, label));
        }
    }

}