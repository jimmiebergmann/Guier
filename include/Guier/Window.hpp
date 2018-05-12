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

    class GUIER_API Window : public Callback::Slot, public Core::WindowBase
    {

    public:

        Window(const Vector2i & size = { 800, 600 }, const std::wstring & title = L"", const Settings & settings = {});
        Window(const Settings & settings, const Vector2i & size = { 800, 600 }, const std::wstring & title = L"");

        ~Window();

        const Vector2i & Size() const;

        const std::wstring & Title() const;

        bool IsOpen() const;

        void Resize(const Vector2i & size);

        void Show(const bool show = true);

        void Minimize();

        void Maximize();

        void Hide(const bool hide = true);

        void Focus();

        void Open();
        void Open(const Vector2i & size, const std::wstring & title, const Settings & settings);

        void Close();

        Callback::Signal<void(const Vector2i &)> Resized;

        Callback::Signal<void(bool)> Showing;

        Callback::Signal<void(bool)> Focused;

        Callback::Signal<void(bool)> Opened;

    };

}