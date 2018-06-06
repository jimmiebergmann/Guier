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

namespace Guier
{

    /**
    * Color, represented by RGBA.
    *
    */
    class GUIER_API Color
    {

    public:

        /**
        * Constructors.
        *
        * @param red        Red color component. 
        * @param green      Green color component.
        * @param blue       Blue color component.
        * @param alpha      Alpha component.
        * @param gray       Gray color. Setting red, green and blue components.
        *
        */
        Color(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha = 255);
        Color(const unsigned char gray, const unsigned char alpha = 255);

        unsigned char r;    ///< Red color component.
        unsigned char g;    ///< Green color component.
        unsigned char b;    ///< Blue color component.
        unsigned char a;    ///< Alpha component.

        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Cyan;
        static const Color Transparent;

    };

}