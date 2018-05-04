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
inline Vector2<T> Vector2<T>::Absolute() const
{
    return Vector2<T>((T)std::abs((T)x),
        (T)std::abs((T)y));
}

