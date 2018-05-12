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

#pragma once

#include <Guier/Core/Build.hpp>

#ifdef GUIER_PLATFORM_WINDOWS

#include <Guier/Core/WindowImpl.hpp>
#include <Guier/Core/WindowBase.hpp>
#include <Windows.h>

namespace Guier
{

    class Window;

    namespace Core
    {

        class GUIER_API Win32WindowImpl : public WindowImpl
        {

        public:

            Win32WindowImpl(Window * window, const Vector2i & size, const std::wstring & title, const WindowBase::Settings & settings);

            ~Win32WindowImpl();

            virtual void Update();

            virtual const Vector2i & Size() const;

            virtual const std::wstring & Title() const;

            virtual bool IsOpen() const;

            virtual void Resize(const Vector2i & size);

            virtual void Show(const bool show);

            virtual void Minimize();

            virtual void Maximize();

            virtual void Hide(const bool hide);

            virtual void Focus();

            virtual void Open();
            virtual void Open(const Vector2i & size, const std::wstring & title, const WindowBase::Settings & settings);

            virtual void Close();


            HWND GetWindowHandle() const;
            HDC GetDeviceContextHandle() const;

        private:

            Vector2i        m_Size;     ///< Size of window.
            std::wstring    m_Title;    ///< Title of window.

            static LRESULT WindowProcStatic(HWND p_HWND, UINT p_Message,
                WPARAM p_WParam, LPARAM p_LParam);

            LRESULT WindowProc(HWND p_HWND, UINT p_Message,
                WPARAM p_WParam, LPARAM p_LParam);

            void FillWin32Background(const Vector2i & p_OldSize, const Vector2i & p_NewSize);

            Window *        m_pWindow; ///< Pointer to window.
            HWND			m_WindowHandle;
            HDC				m_DeviceContextHandle;
            //HGLRC			m_OpenGLContext;
            HBRUSH			m_BackgroundBrush;
            std::wstring	m_WindowClassName;
            bool			m_RedrawStatus;

            bool            m_Showing;

        };

    }

}

#endif