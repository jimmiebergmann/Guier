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
#include <Guier/Core/WindowBase.hpp>
#include <Guier/Vector2.hpp>
#include <string>
#include <memory>

namespace Guier
{

    class Window;

    namespace Core
    {

        class GUIER_API WindowImpl
        {

        public:

            virtual ~WindowImpl();

            /**
            * Get or set current size of window.
            *
            */
            virtual const Vector2i & Size() const = 0;
            virtual void Size(const Vector2i & size) = 0;

            /**
            * Get or set current title of window.
            *
            */
            virtual const std::wstring & Title() const = 0;
            virtual void Title(const std::wstring & title) = 0;
            virtual void Title(const std::string & title) = 0;

            /**
            * Get or set the current position of the window.
            *
            * @brief Has no effect if the window is closed.
            *
            */
            virtual const Vector2i & Position() const = 0;
            virtual void Position(const Vector2i & position) = 0;

            virtual void Show() = 0;

            virtual void Minimize() = 0;

            virtual void Maximize() = 0;

            virtual void HideFromTaskbar(const bool hide) = 0;

            virtual void Close() = 0;

            virtual unsigned int GetStyle() const = 0;

            virtual void NewStyle(const unsigned int styles) = 0;

            virtual void EnableStyles(const unsigned int styles) = 0;

            virtual void DisableStyles(const unsigned int styles) = 0;

        };

    }

}