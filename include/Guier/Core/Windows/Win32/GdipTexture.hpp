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

#include <Guier/Core/Texture.hpp>
#include <Guier/String.hpp>

#include <Windows.h>
#include <gdiplus.h>
#include <Gdiplusheaders.h>

namespace Guier
{

    namespace Core
    {

        class GUIER_API GdipTexture : public Texture
        {

        public:

            /**
            * Constructor.
            *
            */
            GdipTexture(const String & filename);
            GdipTexture(const void * data, const Vector2i & size, const Format format);

            /**
            * Virtual destructor.
            *
            */
            ~GdipTexture();

            /**
            * Get format of texture.
            *
            */
            Format GetFormat() const;

            /**
            * Get size of texture.
            *
            */
            const Vector2i & GetSize() const;

            /**
            * Get underlying bitmap class.
            *
            */
            Gdiplus::Bitmap * GetBitmap() const;

        private:

            Gdiplus::Bitmap *   m_pBitmap;
            Vector2i            m_Size;
            Format              m_Format;

        };

    }

}