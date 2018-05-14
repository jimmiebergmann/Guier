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
#include <Guier/Callback.hpp>
#include <Windows.h>

namespace Guier
{

    class Window;
    class Context;

    namespace Core
    {

        class GUIER_API Win32WindowImpl : public WindowImpl
        {

        public:

            Win32WindowImpl(Context * context, std::shared_ptr<Window> window, const Vector2i & size, const std::wstring & title);

            ~Win32WindowImpl();

            static void HandleEvents();


            virtual const Vector2i & Size() const;
            virtual void Size(const Vector2i & size);

            /**
            * Get or set current title of window.
            *
            */
            virtual const std::wstring & Title() const;
            virtual void Title(const std::wstring & title);
            virtual void Title(const std::string & title);

            /**
            * Get or set the current position of the window.
            *
            * @param position   New position of window.
            *                   x or y value less than = system default position.
            *
            */
            virtual const Vector2i & Position() const;
            virtual void Position(const Vector2i & position);

            virtual void Show();

            virtual void Minimize();

            virtual void Maximize();

            virtual void HideFromTaskbar(const bool hide);

            virtual void Close();

            virtual unsigned int GetStyle() const;

            virtual void NewStyle(const unsigned int styles);

            virtual void EnableStyles(const unsigned int styles);

            virtual void DisableStyles(const unsigned int styles);


            HWND GetWindowHandle() const;
            HDC GetDeviceContextHandle() const;

        private:

            /**
            * Internally set Win32 window position and size.
            *
            */
            void UpdatePositionSize();

            void NewStyleInternal(const unsigned int styles);

            static LRESULT WindowProcStatic(HWND p_HWND, UINT p_Message, WPARAM p_WParam, LPARAM p_LParam);
            LRESULT WindowProc(HWND p_HWND, UINT p_Message, WPARAM p_WParam, LPARAM p_LParam);
            void FillWin32Background(const Vector2i & p_OldSize, const Vector2i & p_NewSize);

            bool                                         m_Showing;             ///< Window is currently showing.
            bool                                         m_HideWhenClosed;      ///< Hide window when closing.
            bool                                         m_HideFromTaskbar;     ///< Hide window from tastbar.
            Vector2i                                     m_Position;            ///< Position of window.
            Vector2i                                     m_Size;                ///< Size of window.
            std::wstring                                 m_Title;               ///< Title of window.
            std::shared_ptr<Guier::Callback::Connection> m_CloseConnection;     ///< Connection of defailt close signal.
            
            unsigned int                                 m_Styles;              ///< Bitfield of styles.
            DWORD                                        m_Win32Style;          ///< Win32 style of window.
            DWORD                                        m_Win32ExtendedStyle;  ///< Win32 extended style of window.
            mutable std::mutex                           m_StyleMutex;          /// Style mutex.



            Context * const         m_pContext;             ///< Pointer of context.
            std::shared_ptr<Window> m_Window;               ///< Pointer of window.
            HWND			        m_WindowHandle;
            HDC				        m_DeviceContextHandle;
            //HGLRC			        m_OpenGLContext;
            HBRUSH			        m_BackgroundBrush;
            std::wstring	        m_WindowClassName;
            bool			        m_RedrawStatus;
         

        };

    }

}

#endif