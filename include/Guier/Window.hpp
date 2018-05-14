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
#include <Guier/Callback.hpp>

namespace Guier
{

    /**
    * Drawable window. Currently appearing as a platform independent window.
    *
    */
    class GUIER_API Window : public Callback::Slot, public Core::WindowBase
    {

    public:

        // Forward declarations
        friend class Core::ContextBase;

        /**
        * Get or set current size of window.
        *
        * @param size   New size of window.
        *
        */
        const Vector2i & Size() const;
        Window & Size(const Vector2i & size);

        /**
        * Get or set current title of window.
        *
        * @param title   New title of window.
        *
        */
        const std::wstring & Title() const;
        Window & Title(const std::wstring & title);
        Window & Title(const std::string & title);

        /**
        * Get or set the current position of the window.
        *
        * @brief Has no effect if the window is closed.
        *
        * @param position   New position of window.
        *
        */
        const Vector2i & Position() const;
        Window & Position(const Vector2i & position);

        /**
        * Show closed or minimized window.
        *
        * @brief    Window is created if called for the first time.
        *           
        *           Focus and put window to foreground of screen.
        *           Window is restored and shown if minimized.
        *
        */
        Window & Show();

        /**
        * Minimize window.
        *
        * @brief    Window is created if called for the first time.
        *
        *           Window is found in task bar if HideFromTaskbar is set to false.
        *
        */
        Window & Minimize();

        /**
        * Maximize window.
        *
        * @brief    Window is created if called for the first time.
        *
        */
        Window & Maximize();

        /**
        * Hide window from task bar.
        *
        */
        Window & HideFromTaskbar(const bool hide = true);

        /**
        * Hide window from task bar and from the user when the window is closed.
        *
        * @brief The window is not internally unallocated and cleared when the window is closed, if this setting is set to true.
        *
        */
        Window & HideWhenClosed(const bool hideWhenClosed = true);

        /**
        * Close the window.
        *
        * @brief Internally calling the Closed signal.
        *        Use the setting HideWhenClosed to connect hide and minimize logics to signal.
        *
        */
        Window & Close();

        /**
        * Get or set new window style.
        *
        * @brief    It's internally faster to apply mutiple styles via Style(...) method,
        *           than calling Enable for every single style.
        *
        * @param styles     bitfield of styles, defined in Styles::eStyle.
        *
        */
        unsigned int Style() const;
        Window & Style(const unsigned int styles);

        /**
        * Enable single or bitfield of window styles.
        *
        * @param style      Single style to enable.
        * @param styles     bitfield of styles, defined in Styles::eStyle.
        *
        */
        Window & Enable(const Styles::eStyle style);
        Window & Enable(const unsigned int styles);

        /**
        * Disable single or bitfield of window styles.
        *
        * @param style      Single style to disable.
        * @param styles     bitfield of mutiple styles to disable, defined in Styles::eStyle.
        *
        */
        Window & Disable(const Styles::eStyle style);
        Window & Disable(const unsigned int styles);

        /**
        * Signal called when the window is resized.
        *
        * @param Vector2i   New size of window.
        *
        */
        Callback::Signal<void(const Vector2i &)> Resized;

        /**
        * Signal called when the window is moved.
        *
        * @param Vector2i   New position of window.
        *
        */
        Callback::Signal<void(const Vector2i &)> Moved;

        /**
        * Signal called when the window is showing.
        *
        */
        Callback::Signal<void()> Showing;

        /**
        * Signal called when the window is minimized.
        *
        */
        Callback::Signal<void()> Minimized;

        /**
        * Signal called when the window is focused, or lost focus.
        *
        * @param bool   Whether or not the window gained focus. 
        *
        */
        Callback::Signal<void(bool)> Focused;

        /**
        * Signal called when the window is opened.
        *
        */
        Callback::Signal<void()> Opened;

        /**
        * Signal called when the window is closed via X button or code.
        *
        * @brief A default function is attached when creating the window, calling the Remove method of Context.
        *        Disconnect all connection of this signal to override behaivour.
        *
        */
        Callback::Signal<void()> Closed;

        /**
        * Signal called when the window is removed from context.
        *
        * @brief Any stored shared pointer of window should be restored, to make sure the pointer is unallocated.
        *
        */
        Callback::Signal<void()> Removed;

    private:

        /**
        * Private constructor, called via Context::Add(...).
        *
        * @param size[X][Y]     Initial size of window.
        * @param title          Title of window, shown in title bar and task bar.
        *
        */
        Window(const Vector2i & size = { 800, 600 }, const std::wstring & title = L"");
        Window(const std::wstring & title, const Vector2i & size = { 800, 600 });
        Window(const int sizeX, const int sizeY, const std::wstring & title = L"");
        Window(const std::wstring & title, const int sizeX, const int sizeY);

        /**
        * Private destructor.
        *
        */
        ~Window();

    };

}