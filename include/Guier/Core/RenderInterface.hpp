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
#include <Guier/Core/RenderArea.hpp>
#include <Guier/Core/Texture.hpp>
#include <Guier/Font.hpp>

namespace Guier
{

    class Control;

    namespace Core
    {

        class GUIER_API RenderInterface
        {

        public:

            /**
            * Virtual destructor.
            *
            */
            virtual ~RenderInterface();

            /**
            * Render Controller.
            *
            */
            virtual void RenderControl(Control * control, const RenderArea & renderArea);

            /**
            * Render Rectangle.
            *
            */
            virtual void RenderRectangle(const Vector2i & position, const Vector2i & size, Texture * texture) = 0;
            virtual void RenderRectangle(const Vector2i & position, const Vector2i & size, Texture * texture, const Vector2i & portionPosition, const Vector2i & portionSize) = 0;
            virtual void RenderRectangle(const Vector2i & position, const Vector2i & size, const Color & color) = 0;

            /**
            * Render font.
            *
            */
            virtual void RenderFont(Font * font, const String & string, const unsigned int size, const Vector2i & position, const Color & color = Color::Black);

        };

    }

}