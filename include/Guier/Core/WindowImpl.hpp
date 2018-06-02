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
#include <Guier/Core/WindowManager.hpp>
#include <Guier/Window.hpp>
#include <Guier/Vector2.hpp>
#include <Guier/String.hpp>

namespace Guier
{

    namespace Core
    {

        class GUIER_API WindowImpl
        {

        public:

            /**
            * Destructor.
            *
            */
            virtual ~WindowImpl();

            /**
            * Load native window.
            *
            */
            virtual void Load() = 0;

            /**
            * Get or set current size of window.
            *
            * @param size   New size of window.
            *
            */
            virtual const Vector2i & Size() const = 0;
            virtual void Size(const Vector2i & size) = 0;

            /**
            * Get or set the current position of the window.
            *
            * @param position   New position of window.
            *
            */
            virtual const Vector2i & Position() const = 0;
            virtual void Position(const Vector2i & position) = 0;

            /**
            * Get or set current title of window.
            *
            * @param title   New title of window.
            *
            */
            virtual const String & Title() const = 0;
            virtual void Title(const String & title) = 0;

            /**
            * Set window style. Overridig any previously added styles.
            *
            * @param style      Style to set.
            * @param styles     Multiple styles to set.
            *
            */
            virtual void SetStyle(const Window::Style style) = 0;
            virtual void SetStyle(const std::initializer_list<Window::Style> & styles) = 0;


            /**
            * Add window style.
            *
            * @param style      Style to add to window.
            * @param styles     Multiple styles to add to window.
            *
            */
            virtual void AddStyle(const Window::Style style) = 0;
            virtual void AddStyle(const std::initializer_list<Window::Style> & styles) = 0;

            /**
            * Remove window style.
            *
            * @param style      Style to remove from window.
            * @param styles     Multiple styles to remove from window.
            *
            */
            virtual void RemoveStyle(const Window::Style style) = 0;
            virtual void RemoveStyle(const std::initializer_list<Window::Style> & styles) = 0;

            /**
            * Show minimized window.
            *
            * @brief    Window is created if called for the first time.
            *
            *           Focus and put window to foreground of screen.
            *           Window is restored and shown if minimized.
            *
            */
            virtual void Show() = 0;

            /**
            * Hide window window.
            *
            * @brief The window will disappear from screen and taskbar.
            *        Restore window via Show() method.
            *
            */
            virtual void Hide() = 0;

            /**
            * Minimize window.
            *
            * @brief    The window will disappear from screen and is
            *           found in task bar if HideFromTaskbar is set to false.
            *
            */
            virtual void Minimize() = 0;

            /**
            * Maximize window.
            *
            * @brief    Window is created if called for the first time.
            *
            */
            virtual void Maximize() = 0;

            /**
            * Close the window.
            *
            * @brief Internally calling the Closed signal.
            *        Use the setting HideWhenClosed to connect hide and minimize logics to signal.
            *
            */
            virtual void Close() = 0;

            /**
            * Perform child operations, add or remove childs.
            *
            */
            virtual bool Add(Control * child, const Index & index) = 0;
            virtual bool Remove(Control * child) = 0;
            virtual Control * Remove(const Index & index) = 0;

        protected:

            static WindowManager Manager;

        };

    }

}