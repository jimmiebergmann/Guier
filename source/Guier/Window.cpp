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
#include <Guier/Context.hpp>
#include <Guier/Core/WindowImpl.hpp>

namespace Guier
{

    static const std::wstring g_EmptyString = L"";
    static const Vector2i g_DefaultSizePosition = {-1, -1};

    const Vector2i & Window::Size() const
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            return m_pImpl->Size();
        }

        return g_DefaultSizePosition;
    }

    Window & Window::Size(const Vector2i & size)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Size(size);
        }
        
        return *this;
    }

    const std::wstring & Window::Title() const
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            return m_pImpl->Title();
        }
       
        return g_EmptyString;
    }

    Window & Window::Title(const std::wstring & title)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Title(title);
        }
        
        return *this;
    }

    Window & Window::Title(const std::string & title)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Title(title);
        }

        return *this;
    }

    const Vector2i & Window::Position() const
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            return m_pImpl->Position();
        }

        return g_DefaultSizePosition;
    }

    Window & Window::Position(const Vector2i & position)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Position(position);
        }

        return *this;
    }

    Window & Window::Show()
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Show();
        }

        return *this;
    }

    Window & Window::Minimize()
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Minimize();
        }

        return *this;
    }

    Window & Window::Maximize()
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Maximize();
        }

        return *this;
    }

    Window & Window::HideFromTaskbar(const bool hide)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->HideFromTaskbar(hide);
        }
        
        return *this;
    }

    Window & Window::HideWhenClosed(const bool hideWhenClosed)
    {
        return *this;
    }

    Window & Window::Close()
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->Close();
        }
        
        return *this;
    }

    unsigned int Window::Style() const
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->GetStyle();
        }

        return Styles::Default;
    }

    Window & Window::Style(const unsigned int styles)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->NewStyle(styles);
        }

        return *this;
    }

    Window & Window::Enable(const Styles::eStyle style)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->EnableStyles(static_cast<unsigned int>(style));
        }

        return *this;
    }

    Window & Window::Enable(const unsigned int styles)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->EnableStyles(styles);
        }

        return *this;
    }

    Window & Window::Disable(const Styles::eStyle style)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->DisableStyles(static_cast<unsigned int>(style));
        }

        return *this;
    }
    Window & Window::Disable(const unsigned int styles)
    {
        std::lock_guard<std::mutex> sm(m_ImplMutex);

        if (m_pImpl)
        {
            m_pImpl->DisableStyles(styles);
        }

        return *this;
    }

    Window::Window(const Vector2i & size, const std::wstring & title) :
        WindowBase(size, title)
    {
    }

    Window::Window(const std::wstring & title, const Vector2i & size) :
        Window(size, title)
    {

    }
    Window::Window(const int sizeX, const int sizeY, const std::wstring & title) :
        Window(Vector2i(sizeX, sizeY), title)
    {

    }
    Window::Window(const std::wstring & title, const int sizeX, const int sizeY) :
        Window(Vector2i(sizeX, sizeY), title)
    {

    }

    Window::~Window()
    {

    }
}