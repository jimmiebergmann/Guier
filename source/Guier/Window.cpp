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

    Window::Window(Context * context, const Vector2i & size, const std::wstring & title) :
        WindowBase(context, size, title)
    {
    }

    Window::Window(Context * context, const std::wstring & title, const Vector2i & size) :
        Window(context, size, title)
    {

    }
    Window::Window(Context * context, const int sizeX, const int sizeY, const std::wstring & title) :
        Window(context, Vector2i(sizeX, sizeY), title)
    {

    }
    Window::Window(Context * context, const std::wstring & title, const int sizeX, const int sizeY) :
        Window(context, Vector2i(sizeX, sizeY), title)
    {

    }

    Window::~Window()
    {
        //m_Deleted = true;
        //m_pContext->Remove(this);
    }

    const Vector2i & Window::Size() const
    {
        return m_pImpl->Size();
    }

    std::shared_ptr<Window> Window::Size(const Vector2i & size)
    {
        m_pImpl->Size(size);
        return m_SharedPtrWindow;
    }

    const std::wstring & Window::Title() const
    {
       return m_pImpl->Title();
    }

    std::shared_ptr<Window> Window::Title(const std::wstring & title)
    {
        m_pImpl->Title(title);
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::Title(const std::string & title)
    {
        m_pImpl->Title(title);
        return m_SharedPtrWindow;
    }

    const Vector2i & Window::Position() const
    {
        return m_pImpl->Position();
    }

    std::shared_ptr<Window> Window::Position(const Vector2i & position)
    {
        m_pImpl->Position(position);
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::Show()
    {
        m_pImpl->Show();
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::Minimize()
    {
        m_pImpl->Minimize();
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::Maximize()
    {
        m_pImpl->Maximize();
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::HideFromTaskbar(const bool hide)
    {
        m_pImpl->HideFromTaskbar(hide);
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::HideWhenClosed(const bool hideWhenClosed)
    {
        return m_SharedPtrWindow;
    }

    std::shared_ptr<Window> Window::Close()
    {
        m_pImpl->Close();
        return m_SharedPtrWindow;
    }
}