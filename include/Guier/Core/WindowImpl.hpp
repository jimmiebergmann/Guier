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

namespace Guier
{

    namespace Core
    {

        class GUIER_API WindowImpl
        {

        public:

            virtual ~WindowImpl();

            virtual void Update() = 0;

            virtual const Vector2i & Size() const = 0;

            virtual const std::wstring & Title() const = 0;

            virtual bool IsOpen() const = 0;

            virtual void Resize(const Vector2i & size) = 0;

            virtual void Show(const bool show) = 0;

            virtual void Minimize() = 0;

            virtual void Maximize() = 0;

            virtual void Hide(const bool hide) = 0;

            virtual void Focus() = 0;

            virtual void Open() = 0;
            virtual void Open(const Vector2i & size, const std::wstring & title, const WindowBase::Settings & settings) = 0;

            virtual void Close() = 0;

        };

    }

}