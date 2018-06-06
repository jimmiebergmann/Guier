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

template <typename T>
inline Vector2<T>::Vector2() :
    x(static_cast<T>(0)),
    y(static_cast<T>(0))
{
}

template <typename T>
inline Vector2<T>::Vector2(T p_X, T p_Y) :
    x(p_X),
    y(p_Y)
{
}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(U p_X, U p_Y) :
    x(static_cast<T>(p_X)),
    y(static_cast<T>(p_Y))
{
}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U> & p_Vector) :
    x(static_cast< T >(p_Vector.x)),
    y(static_cast< T >(p_Vector.y))
{
}

template <typename T>
template <typename U>
inline Vector2<T> & Vector2<T>::operator = (const Vector2<U> & p_Vector)
{
    x = static_cast< T >(p_Vector.x);
    y = static_cast< T >(p_Vector.y);
    return *this;
}

template <typename T>
inline bool Vector2<T>::operator == (const Vector2<T> & p_Vector) const
{
    return (x == p_Vector.x) && (y == p_Vector.y);
}

template <typename T>
inline bool Vector2<T>::operator != (const Vector2<T> & p_Vector) const
{
    return (x != p_Vector.x) || (y != p_Vector.y);
}

template <typename T>
inline Vector2<T> & Vector2<T>::operator += (const Vector2<T> & p_Vector)
{
    x += p_Vector.x;
    y += p_Vector.y;
    return *this;
}

template <typename T>
inline Vector2<T> & Vector2<T>::operator -= (const Vector2<T> & p_Vector)
{
    x -= p_Vector.x;
    y -= p_Vector.y;
    return *this;
}

template <typename T>
inline Vector2<T> & Vector2<T>::operator *= (const Vector2<T> & p_Vector)
{
    x *= p_Vector.x;
    y *= p_Vector.y;
    return *this;
}

template <typename T>
inline Vector2<T> & Vector2<T>::operator /= (const Vector2<T> & p_Vector)
{
    x /= p_Vector.x;
    y /= p_Vector.y;
    return *this;
}

template <typename T>
inline Vector2<T> Vector2<T>::operator + (const Vector2<T> & p_Vector) const
{
    return Vector2<T>(x + p_Vector.x, y + p_Vector.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator - () const
{
    return Vector2<T>(-x, -y);
}

template <typename T>
inline Vector2 <T > Vector2<T>::operator - (const Vector2<T> & p_Vector) const
{
    return Vector2<T>(x - p_Vector.x, y - p_Vector.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator * (const Vector2<T> & p_Vector) const
{
    return Vector2<T>(x * p_Vector.x, y * p_Vector.y);
}

template <typename T>
template <typename U>
inline Vector2<T> Vector2<T>::operator * (const U & p_Value) const
{
    return Vector2<T>(x * static_cast<T>(p_Value),
        y * static_cast<T>(p_Value));
}

template <typename T>
inline Vector2<T> Vector2<T>::operator / (const Vector2<T> & p_Vector) const
{
    return Vector2<T>(x / p_Vector.x, y / p_Vector.y);
}

template <typename T>
template <typename U>
inline Vector2< T > Vector2< T >::operator / (const U & p_Value) const
{
    return Vector2<T>(x / static_cast<T>(p_Value),
        y / static_cast<T>(p_Value));
}

template <typename T>
inline Vector2<T> Vector2<T>::absolute() const
{
    return Vector2<T>((T)std::abs((T)x),
        (T)std::abs((T)y));
}

