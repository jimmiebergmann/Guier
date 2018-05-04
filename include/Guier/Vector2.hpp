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

    ///< Include the inline file.
    #include <Guier/Core/Vector2.inl>

    ///< Helper typedefs
    typedef Vector2<int> Vector2i;

}