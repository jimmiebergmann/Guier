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
            virtual void load() = 0;

            /**
            * Get or set current size of window.
            *
            * @param size   New size of window.
            *
            */
            virtual const Vector2i & size() const = 0;
            virtual void size(const Vector2i & size) = 0;

            /**
            * Get or set the current position of the window.
            *
            * @param position   New position of window.
            *
            */
            virtual const Vector2i & position() const = 0;
            virtual void position(const Vector2i & position) = 0;

            /**
            * Get or set current title of window.
            *
            * @param title   New title of window.
            *
            */
            virtual const String & title() const = 0;
            virtual void title(const String & title) = 0;

            /**
            * Set window style. Overridig any previously added styles.
            *
            * @param style      Style to set.
            * @param styles     Multiple styles to set.
            *
            */
            virtual void setStyle(const Window::Style style) = 0;
            virtual void setStyle(const std::initializer_list<Window::Style> & styles) = 0;


            /**
            * Add window style.
            *
            * @param style      Style to add to window.
            * @param styles     Multiple styles to add to window.
            *
            */
            virtual void addStyle(const Window::Style style) = 0;
            virtual void addStyle(const std::initializer_list<Window::Style> & styles) = 0;

            /**
            * Remove window style.
            *
            * @param style      Style to remove from window.
            * @param styles     Multiple styles to remove from window.
            *
            */
            virtual void removeStyle(const Window::Style style) = 0;
            virtual void removeStyle(const std::initializer_list<Window::Style> & styles) = 0;

            /**
            * Show minimized window.
            *
            * @brief    Window is created if called for the first time.
            *
            *           Focus and put window to foreground of screen.
            *           Window is restored and shown if minimized.
            *
            */
            virtual void show() = 0;

            /**
            * Hide window window.
            *
            * @brief The window will disappear from screen and taskbar.
            *        Restore window via Show() method.
            *
            */
            virtual void hide() = 0;

            /**
            * Minimize window.
            *
            * @brief    The window will disappear from screen and is
            *           found in task bar if HideFromTaskbar is set to false.
            *
            */
            virtual void minimize() = 0;

            /**
            * Maximize window.
            *
            * @brief    Window is created if called for the first time.
            *
            */
            virtual void maximize() = 0;

            /**
            * Close the window.
            *
            * @brief Internally calling the Closed signal.
            *        Use the setting HideWhenClosed to connect hide and minimize logics to signal.
            *
            */
            virtual void close() = 0;

            /**
            * Perform child operations, add or remove childs.
            *
            */
            virtual bool add(Control * child, const Index & index) = 0;
            virtual bool remove(Control * child) = 0;
            virtual Control * remove(const Index & index) = 0;

            /**
            * Create texture from bitmap.
            *
            */
            virtual Core::Texture * createTexture(Bitmap * bitmap) = 0;

        protected:

            static WindowManager Manager;

        };

    }

}