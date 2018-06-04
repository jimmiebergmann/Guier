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

#include <Guier/Core/Win32/WindowsHeaders.hpp>
#include <Guier/Core/WindowImpl.hpp>
#include <Guier/Core/Windows/Win32/GdipRenderer.hpp>
#include <Guier/Window.hpp>

namespace Guier
{

    class Plane;
    class Skin;

    namespace Core
    {

        class WindowBase;

        class GUIER_API Win32WindowImpl : public WindowImpl
        {

        public:

            /**
            * Constructor.
            *
            */
            Win32WindowImpl(WindowBase * window, Skin * skin, const Vector2i & size, const String & title, const std::initializer_list<Window::Style> & styles);

            /**
            * Destructor.
            *
            */
            virtual ~Win32WindowImpl();

            /**
            * Load the implementation.
            *
            * @brief    Internally triggers the window manager loading mechanism.
            *           Function wont return until window manager is done loading the window.
            *
            */
            void LoadImplementation();

            /**
            * Get or set current size of window.
            *
            * @param size   New size of window.
            *
            */
            const Vector2i & Size() const;
            void Size(const Vector2i & size);

            /**
            * Get or set the current position of the window.
            *
            * @param position   New position of window.
            *
            */
            const Vector2i & Position() const;
            void Position(const Vector2i & position);

            /**
            * Get or set current title of window.
            *
            * @param title   New title of window.
            *
            */
            const String & Title() const;
            void Title(const String & title);

            /**
            * Set window style. Overridig any previously added styles.
            *
            * @param style      Style to set.
            * @param styles     Multiple styles to set.
            *
            */
            void SetStyle(const Window::Style style);
            void SetStyle(const std::initializer_list<Window::Style> & styles);


            /**
            * Add window style.
            *
            * @param style      Style to add to window.
            * @param styles     Multiple styles to add to window.
            *
            */
            void AddStyle(const Window::Style style);
            void AddStyle(const std::initializer_list<Window::Style> & styles);

            /**
            * Remove window style.
            *
            * @param style      Style to remove from window.
            * @param styles     Multiple styles to remove from window.
            *
            */
            void RemoveStyle(const Window::Style style);
            void RemoveStyle(const std::initializer_list<Window::Style> & styles);

            /**
            * Show minimized window.
            *
            * @brief    Window is created if called for the first time.
            *
            *           Focus and put window to foreground of screen.
            *           Window is restored and shown if minimized.
            *
            */
            void Show();

            /**
            * Hide window window.
            *
            * @brief The window will disappear from screen and taskbar.
            *        Restore window via Show() method.
            *
            */
            void Hide();

            /**
            * Minimize window.
            *
            * @brief    The window will disappear from screen and is
            *           found in task bar if HideFromTaskbar is set to false.
            *
            */
            void Minimize();

            /**
            * Maximize window.
            *
            * @brief    Window is created if called for the first time.
            *
            */
            void Maximize();

            /**
            * Close the window.
            *
            * @brief Internally calling the Closed signal.
            *        Use the setting HideWhenClosed to connect hide and minimize logics to signal.
            *
            */
            void Close();

            /**
            * Perform child operations, add or remove childs.
            *
            */
            bool Add(Control * child, const Index & index);
            bool Remove(Control * child);
            Control * Remove(const Index & index);

        private:

            /**
            * Load native window.
            *
            */
            void Load();
            
            /**
            * Internal function used for setting style of window.
            *
            */
            void SetStyleInternal(const unsigned int styles);

            /**
            * Window event functions.
            *
            */
            static LRESULT WindowProcStatic(HWND p_HWND, UINT p_Message, WPARAM p_WParam, LPARAM p_LParam);
            LRESULT WindowProc(HWND p_HWND, UINT p_Message, WPARAM p_WParam, LPARAM p_LParam);
            
            GdipRenderer *      m_pRenderer;            ///< Pointer to renderer;
            Vector2i        m_Size;                 ///< Current size of window.
            Vector2i        m_Position;             ///< Position of window.
            String          m_Title;                ///< Title of window.
            unsigned int    m_Styles;               ///< Bitfield of styles.
            int             m_DPI;                  ///< Current window dpi.
            HWND		    m_WindowHandle;
            HDC			    m_DeviceContextHandle;
            DWORD           m_Win32Style;           ///< Win32 style of window.
            DWORD           m_Win32ExtendedStyle;   ///< Win32 extended style of window.
            std::wstring	m_WindowClassName;   

            WindowBase *    m_pWindow;
            Skin *          m_pSkin;                ///< Pointer to skin.
            Plane *         m_pPlane;               ///< Plane containing all childs.

        };

    }

}

#endif