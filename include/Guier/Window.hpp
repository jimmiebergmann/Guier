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

#include <Guier/Core/WindowBase.hpp>

namespace Guier
{

    /**
    * Drawable window. Currently appearing as a platform independent window.
    *
    */
    class GUIER_API Window : public Core::WindowBase// public Core::PlatformWindow
    {

    public:

        /**
        * Constructor.
        *
        * @param size           Size of window.
        * @param title          Title of window.
        * @param styles         List of styles. Using default window style if omitted.
        *
        */
        Window(const Vector2i & size, const String & title = L"");
        Window(const Vector2i & size, const String & title, const std::initializer_list<Style> & styles);

        /**
        * Private destructor.
        *
        */
        ~Window();

        /**
        * Get or set current size of window.
        *
        * @param size   New size of window.
        *
        */
        const Vector2i & Size() const;
        Window * Size(const Vector2i & size);

        /**
        * Get or set the current position of the window.
        *
        * @param position   New position of window.
        *
        */
        const Vector2i & Position() const;
        Window * Position(const Vector2i & position);

        /**
        * Get or set current title of window.
        *
        * @param title   New title of window.
        *
        */
        const String & Title() const;
        Window * Title(const String & title);

        /**
        * Set window style. Overridig any previously added styles.
        *
        * @param style      Style to set.
        * @param styles     Multiple styles to set.
        *
        */
        Window * SetStyle(const Style style);
        Window * SetStyle(const std::initializer_list<Style> & styles);


        /**
        * Add window style.
        *
        * @param style      Style to add to window.
        * @param styles     Multiple styles to add to window.
        *
        */
        Window * AddStyle(const Style style);
        Window * AddStyle(const std::initializer_list<Style> & styles);

        /**
        * Remove window style.
        *
        * @param style      Style to remove from window.
        * @param styles     Multiple styles to remove from window.
        *
        */
        Window * RemoveStyle(const Style style);
        Window * RemoveStyle(const std::initializer_list<Style> & styles);

        /**
        * Show minimized window.
        *
        * @brief    Window is created if called for the first time.
        *           
        *           Focus and put window to foreground of screen.
        *           Window is restored and shown if minimized.
        *
        */
        Window * Show();

        /**
        * Hide window window.
        *
        * @brief The window will disappear from screen and taskbar.
        *        Restore window via Show() method.
        *
        */
        Window * Hide();

        /**
        * Minimize window.
        *
        * @brief    The window will disappear from screen and is
        *           found in task bar if HideFromTaskbar is set to false.
        *
        */
        Window * Minimize();

        /**
        * Maximize window.
        *
        * @brief    Window is created if called for the first time.
        *
        */
        Window * Maximize();

        /**
        * Close the window.
        *
        * @brief Internally calling the Closed signal.
        *        Use the setting HideWhenClosed to connect hide and minimize logics to signal.
        *
        */
        Window * Close();

        /**
        * Signal called when the window is resized.
        *
        * @param Vector2i   New size of window.
        *
        */
//      Callback::Signal<void(const Vector2i &)> Resized;

        /**
        * Signal called when the window is moved.
        *
        * @param Vector2i   New position of window.
        *
        */
//      Callback::Signal<void(const Vector2i &)> Moved;

        /**
        * Signal called when the window is showing.
        *
        */
//       Callback::Signal<void()> Showing;

        /**
        * Signal called when the window is hiding.
        *
        */
 //       Callback::Signal<void()> Hiding;

        /**
        * Signal called when the window is minimized.
        *
        */
//       Callback::Signal<void()> Minimized;

        /**
        * Signal called when the window is maximized.
        *
        */
//        Callback::Signal<void()> Maximized;

        /**
        * Signal called when the window is focused.
        *
        */
 //       Callback::Signal<void()> Focused;

        /**
        * Signal called when the window lose focus
        *
        */
 //       Callback::Signal<void()> Unfocusing;

        /**
        * Signal called when the window is closed via X button or code.
        *
        * @brief A default function is attached when creating the window, calling the Remove method of Context.
        *        Disconnect all connection of this signal to override behaivour.
        *
        */
        //        Callback::Signal<void()> Closed;

        /**
        * Signal called when the window is unallocated via delete keyword.
        * Do not use the pointer after deletion.
        *
        * @param Window Pointer of deleted window.
        *
        */
//        Callback::Signal<void(Window *)> Deleted;



    };

}