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
        WindowBase(nullptr, size, title, { Style::Default })
    {
    }

    Window::Window(const Vector2i & size, const String & title, const std::initializer_list<Style> & styles) :
        WindowBase(nullptr, size, title, styles)
    {

    }

    Window::Window(Skin * skin, const Vector2i & size, const String & title) :
        WindowBase(skin, size, title, { Style::Default })
    {

    }
    Window::Window(Skin * skin, const Vector2i & size, const String & title, const std::initializer_list<Style> & styles) :
        WindowBase(skin, size, title, styles)
    {

    }

    Window::~Window()
    {
       
    }

    const Vector2i & Window::size() const
    {
        return m_pImpl->size();
    }

    Window * Window::size(const Vector2i & size_in)
    {
        m_pImpl->size(size_in);
        return this;
    }

    const Vector2i & Window::position() const
    {
        return m_pImpl->position();
    }

    Window * Window::position(const Vector2i & position_in)
    {
        m_pImpl->position(position_in);
        return this;
    }
    
    const String & Window::title() const
    {
        return m_pImpl->title();
    }

    Window * Window::title(const String & title_in)
    {
        m_pImpl->title(title_in);
        return this;
    }

    Window * Window::setStyle(const Style style)
    {
        m_pImpl->setStyle(style);
        return this;
    }

    Window * Window::setStyle(const std::initializer_list<Style> & styles)
    {
        m_pImpl->setStyle(styles);
        return this;
    }

    Window * Window::addStyle(const Style style)
    {
        m_pImpl->addStyle(style);
        return this;
    }

    Window * Window::addStyle(const std::initializer_list<Style> & styles)
    {
        m_pImpl->addStyle(styles);
        return this;
    }

    Window * Window::removeStyle(const Style style)
    {
        m_pImpl->removeStyle(style);
        return this;
    }

    Window * Window::removeStyle(const std::initializer_list<Style> & styles)
    {
        m_pImpl->removeStyle(styles);
        return this;
    }
   
    Window * Window::show()
    {
        m_pImpl->show();
        return this;
    }

    Window * Window::hide()
    {
        m_pImpl->hide();
        return this;
    }
    
    Window * Window::minimize()
    {
        m_pImpl->minimize();
        return this;
    }

    Window * Window::maximize()
    {
        m_pImpl->maximize();
        return this;
    }

    Window * Window::close()
    {
        m_pImpl->close();
        return this;
    }

}