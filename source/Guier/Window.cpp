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

#include <Guier/Window.hpp>
#include <Guier/Core/WindowImpl.hpp>

namespace Guier
{

    Window::Window(const Vector2i & size, const String & title) :
        WindowBase(size, title, {})
    {
    }

    Window::Window(const Vector2i & size, const String & title, const std::initializer_list<Style> & styles) :
        WindowBase(size, title, styles)
    {

    }

    Window::~Window()
    {
       
    }

    const Vector2i & Window::Size() const
    {
        return m_pImpl->Size();
    }

    Window * Window::Size(const Vector2i & size)
    {
        m_pImpl->Size(size);
        return this;
    }

    const Vector2i & Window::Position() const
    {
        return m_pImpl->Position();
    }

    Window * Window::Position(const Vector2i & position)
    {
        m_pImpl->Position(position);
        return this;
    }
    
    const String & Window::Title() const
    {
        return m_pImpl->Title();
    }

    Window * Window::Title(const String & title)
    {
        m_pImpl->Title(title);
        return this;
    }

    Window * Window::SetStyle(const Style style)
    {
        m_pImpl->SetStyle(style);
        return this;
    }

    Window * Window::SetStyle(const std::initializer_list<Style> & styles)
    {
        m_pImpl->SetStyle(styles);
        return this;
    }

    Window * Window::AddStyle(const Style style)
    {
        m_pImpl->AddStyle(style);
        return this;
    }

    Window * Window::AddStyle(const std::initializer_list<Style> & styles)
    {
        m_pImpl->AddStyle(styles);
        return this;
    }

    Window * Window::RemoveStyle(const Style style)
    {
        m_pImpl->RemoveStyle(style);
        return this;
    }

    Window * Window::RemoveStyle(const std::initializer_list<Style> & styles)
    {
        m_pImpl->RemoveStyle(styles);
        return this;
    }
   
    Window * Window::Show()
    {
        m_pImpl->Show();
        return this;
    }

    Window * Window::Hide()
    {
        m_pImpl->Hide();
        return this;
    }
    
    Window * Window::Minimize()
    {
        m_pImpl->Minimize();
        return this;
    }

    Window * Window::Maximize()
    {
        m_pImpl->Maximize();
        return this;
    }

    Window * Window::Close()
    {
        m_pImpl->Close();
        return this;
    }

}