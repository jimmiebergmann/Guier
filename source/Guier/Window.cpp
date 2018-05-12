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

#if defined(GUIER_PLATFORM_WINDOWS)
#include <Guier/Core/Window/Win32WindowImpl.hpp>
#endif

namespace Guier
{

    Window::Window(const Vector2i & size, const std::wstring & title, const Settings & settings) :
        WindowBase()
    {
        #if defined(GUIER_PLATFORM_WINDOWS)
            m_pImpl = new Core::Win32WindowImpl(this, size, title, settings);
        #else
            #error Unkown platform.
        #endif
    }

    Window::Window(const Settings & settings, const Vector2i & size, const std::wstring & title) :
        Window(size, title, settings)
    {
    }

    Window::~Window()
    {
        m_Deleted = true;
        m_pContext->Remove(this);

        if (m_pImpl)
        {
            delete m_pImpl;
        }
    }

    const Vector2i & Window::Size() const
    {
        return m_pImpl->Size();
    }

    const std::wstring & Window::Title() const
    {
        return m_pImpl->Title();
    }

    bool Window::IsOpen() const
    {
        return m_pImpl->IsOpen();
    }

    void Window::Resize(const Vector2i & size)
    {
        m_pImpl->Resize(size);
    }

    void Window::Show(const bool show)
    {
        m_pImpl->Show(show);
    }

    void Window::Minimize()
    {
        m_pImpl->Minimize();
    }

    void Window::Maximize()
    {
        m_pImpl->Maximize();
    }

    void Window::Hide(const bool hide)
    {
        m_pImpl->Hide(hide);
    }

    void Window::Focus()
    {
        m_pImpl->Focus();
    }

    void Window::Open()
    {
        m_pImpl->Open();
    }

    void Window::Open(const Vector2i & size, const std::wstring & title, const Settings & settings)
    {
        m_pImpl->Open(size, title, settings);
    }

    void Window::Close()
    {
        m_pImpl->Close();
    }
}