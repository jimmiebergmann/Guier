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

    template <typename T>
    class Vector2
    {

    public:

        Vector2();

        Vector2(T x, T y);

        template <typename U>
        Vector2(U x, U y);


        template <typename U>
        Vector2(const Vector2<U> & vector);

        template <typename U>
        Vector2<T> & operator = (const Vector2<U> & vector);

        bool operator == (const Vector2<T> & vector) const;

        bool operator != (const Vector2<T> & vector) const;

        Vector2<T> & operator += (const Vector2<T> & vector);

        Vector2<T> & operator -= (const Vector2<T> & vector);

        Vector2<T> & operator *= (const Vector2<T> & vector);

        Vector2<T> & operator /= (const Vector2<T> & vector);

        Vector2<T> operator + (const Vector2<T> & vector) const;

        Vector2<T> operator - () const;

        Vector2 <T > operator - (const Vector2<T> & vector) const;

        Vector2<T> operator * (const Vector2<T> & vector) const;

        template <typename U>
        Vector2<T> operator * (const U & value) const;

        Vector2<T> operator / (const Vector2<T> & vector) const;

        template <typename U> Vector2<T> operator / (const U & value) const;

        Vector2<T> Absolute() const;

        T x; ///< x-component of vector.
        T y; ///< y-component of vector.

    };

    // Include inline implementations.
    #include <Guier/Core/Vector2.inl>

    ///< Typedefs of common vector types.
    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2ui;

}