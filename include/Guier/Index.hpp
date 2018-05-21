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

#include <Guier/Vector2.hpp>

namespace Guier
{

    class GUIER_API Index
    {

    public:

        /**
        * Enumerator of different index types, depending on what constructor is being used.
        *
        */
        enum eType
        {
            SingleInteger,
            DoubleInteger
        };

        /**
        * Constructors.
        *
        */
        Index(const int index);
        Index(const int x, const int y);
        Index(const Vector2i & index);
        Index(const Index & index);

        /**
        * Destructor.
        *
        */
        ~Index();

        /**
        * Get type of index.
        *
        */
        eType Type() const;

        /**
        * Get single integer index.
        *
        */
        int GetSingleInteger() const;

        /**
        * Get double integer index.
        *
        */
        Vector2i GetDoubleInteger() const;

        /**
        * Check if index is the first.
        *
        */
        bool IsFirst() const;

        /**
        * Check if index is the last.
        *
        */
        bool IsLast() const;

        /**
        * First index.
        *
        */
        static const Index First;

        /**
        * Last index.
        *
        */
        static const Index Last;

        /**
        * Compare operators
        *
        */
        bool operator == (const Index & index) const;
        bool operator != (const Index & index) const;

    private:

        const eType m_Type; ///< Type of index.
        int         m_X;
        int         m_Y;

    };

}