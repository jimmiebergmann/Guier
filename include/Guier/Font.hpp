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

#include <Guier/String.hpp>
#include <Guier/Vector2.hpp>
#include <Guier/Color.hpp>

namespace Guier
{

    class Context;
    namespace Core { class RenderInterface; }


    class GUIER_API Font
    {

    public:

        /**
        * Constructors.
        *
        * @breif The system will initially check if the font is installed.
        *        If it's not installed, handle the name as a local path.
        *
        * @param context    Pointer to context.
        * @param name       Name or path of font.
        * @param data       Load front from memory. Pointer to data.
        * @param dataSize   Size of data.
        *
        * @throw std::runtime_error If the font is not found.
        *
        */
        Font(Context * context, const String & name);
        Font(Context * context, const unsigned char * data, const size_t dataSize);

        /**
        * Constructors.
        *
        */
        virtual ~Font();

    private:


        Context * m_pContext; ///< Pointer to 

        /**
        * Render font.
        *
        */
        virtual void Render(const String & string, const unsigned int size, const Vector2i & position, const Color & color = Color::Black) = 0;

        friend class Text;                  ///< Friend class of text.
        friend class Core::RenderInterface;

    };

}