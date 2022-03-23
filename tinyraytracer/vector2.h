#pragma once
#ifndef VECTOR2_H_
#define VECTOR2_H_

#include"vector.h"
#include<algorithm>
#include<limits>

template <typename T>
class Vector<T, 2> final 
{
public:
    static_assert(std::is_floating_point<T>::value,
        "Vector only can be instantiated with floating point types");

    //! X (or the first) component of the vector.
    T x;

    //! Y (or the second) component of the vector.
    T y;

    //! Constructs default vector (0, 0).
    constexpr Vector() : x(0), y(0) {}

    //! Constructs vector with given parameters \p x_ and \p y_.
    constexpr Vector(T x_, T y_) : x(x_), y(y_) {}

    static constexpr Vector<T,2> zero() { return Vector<T,2>(); }

    //! Constructs vector with initializer list.
    template <typename U>
    Vector(const std::initializer_list<U>& lst);

    //! Copy constructor.
    constexpr Vector(const Vector& v) : x(v.x), y(v.y) {}

    //! Set both x and y components to s.
    void set(T s);

    //! Set x and y components with given parameters.
    void set(T newX, T newY);

    //! Set x and y components with given initializer list.
    template <typename U>
    void set(const std::initializer_list<U>& lst);

    //! Set x and y with other vector pt.
    void set(const Vector& pt);

    //! Set both x and y to zero.
    void setZero();

    //! Returns reference to the \p i -th element of the vector.
    T& operator[](size_t i);

    //! Returns const reference to the \p i -th element of the vector.
    const T& operator[](size_t i) const;

    //! Set x and y components with given initializer list.
    template <typename U>
    Vector& operator=(const std::initializer_list<U>& lst);

    //! Set x and y with other vector pt.
    Vector& operator=(const Vector& v);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);

    Vector operator+(const T& s) const;
    Vector operator-(const T& s) const;
    Vector operator*(const T& s) const;
    Vector operator/(const T& s) const;

    Vector& operator+=(const T& s);
    Vector& operator-=(const T& s);
    Vector& operator*=(const T& s);
    Vector& operator/=(const T& s);

    //! Compute dot product.
    T dot(const Vector& v) const;

    //! Returns true if other is the same as this vector.
    bool operator==(const Vector& other) const;

    //! Returns true if other is not the same as this vector.
    bool operator!=(const Vector& other) const;

    //! Compute norm and square of norm.
    T norm() const;
    T norm_squared() const;

    //! Normalizes this vector.
    void normalize();

    //! Return normalized vector.
    Vector normalized() const;
};



template <typename T>
template <typename U>
inline Vector<T, 2>::Vector(const std::initializer_list<U>& lst) {
    set(lst);
}

template <typename T>
inline void Vector<T, 2>::set(T s) {
    x = s;
    y = s;
}

template <typename T>
inline void Vector<T, 2>::set(T newX, T newY) {
    x = newX;
    y = newY;
}

template <typename T>
template <typename U>
inline void Vector<T, 2>::set(const std::initializer_list<U>& lst) {
    assert(lst.size() == 2);

    auto inputElem = lst.begin();
    x = static_cast<T>(*inputElem);
    y = static_cast<T>(*(++inputElem));
}

template <typename T>
inline void Vector<T, 2>::set(const Vector& v) {
    x = v.x;
    y = v.y;
}

template <typename T>
inline void Vector<T, 2>::setZero() {
    x = 0;
    y = 0;
}

template <typename T>
T& Vector<T, 2>::operator[](size_t i) {
    assert(i < 2);
    return (&x)[i];
}

template <typename T>
const T& Vector<T, 2>::operator[](size_t i) const {
    assert(i < 2);
    return (&x)[i];
}

template <typename T>
template <typename U>
inline Vector<T, 2>& Vector<T, 2>::operator=(const std::initializer_list<U>& lst) {
    set(lst);
    return (*this);
}

template <typename T>
inline Vector<T, 2>& Vector<T, 2>::operator=(const Vector& v) {
    set(v);
    return (*this);
}

template <typename T>
inline Vector<T, 2> Vector<T, 2>::operator+(const Vector& other) const
{
    return Vector<T, 2>(x + other.x, y + other.y);
}

template <typename T>
inline Vector<T, 2> Vector<T, 2>::operator-(const Vector& other) const
{
    return Vector<T, 2>(x - other.x, y - other.y);
}

template <typename T>
inline Vector<T, 2>& Vector<T, 2>::operator+=(const Vector& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
inline Vector<T, 2>& Vector<T, 2>::operator-=(const Vector& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
inline Vector<T, 2> Vector<T,2>:: operator+(const T& s) const
{
    return Vector<T, 2>(x + s, y + s);
}

template <typename T>
inline Vector<T, 2> Vector<T, 2>:: operator-(const T& s) const
{
    return Vector<T, 2>(x - s, y - s);
}

template <typename T>
inline Vector<T, 2> Vector<T, 2>:: operator*(const T& s) const
{
    return Vector<T, 2>(x * s, y * s);
}

template <typename T>
inline Vector<T, 2> Vector<T, 2>:: operator/(const T& s) const
{
    return Vector<T, 2>(x / s, y / s);
}

template <typename T>
inline Vector<T, 2>& Vector<T, 2>:: operator+=(const T& s)
{
    x += s;
    y += s;
    return *this;
}
template <typename T>
inline Vector<T, 2>& Vector<T, 2>:: operator-=(const T& s)
{
    x -= s;
    y -= s;
    return *this;
}

template <typename T>
inline Vector<T, 2>& Vector<T, 2>:: operator*=(const T& s)
{
    x *= s;
    y *= s;
    return *this;
}

template <typename T>
inline Vector<T, 2>& Vector<T, 2>:: operator/=(const T& s)
{
    x /= s;
    y /= s;
    return *this;
}

template <typename T>
inline T Vector<T, 2>::dot(const Vector& v) const
{
    return x * v.x + y * v.y;
}

template<typename T>
inline bool Vector<T, 2>::operator==(const Vector& other) const
{
    return x == other.x && y == other.y;
}

template<typename T>
inline bool Vector<T, 2>::operator!=(const Vector& other) const
{
    return x != other.x || y != other.y;
}

template<typename T>
inline T Vector<T, 2>::norm() const
{
    return std::sqrt(x * x + y * y);
}

template<typename T>
inline T Vector<T, 2>::norm_squared() const
{
    return x * x + y * y;
}

template<typename T>
inline void Vector<T, 2>::normalize()
{
    T _norm = norm();
    x /= _norm;
    y /= _norm;
}

template<typename T>
inline Vector<T, 2> Vector<T, 2>::normalized() const
{
    T _norm = norm();
    return Vector<T, 2>(x / _norm, y / _norm);
}



//! Type alias for two dimensional vector.
template <typename T>
using Vector2 = Vector<T, 2>;

//! Negative sign operator.
template <typename T>
inline Vector2<T> operator-(const Vector2<T>& a)
{
    return Vector2<T>(-a.x, -a.y);
}

template <typename T>
inline Vector2<T> operator+(const T& a, const Vector2<T>& b)
{
    return Vector2<T>(a + b.x, a + b.y);
}

template <typename T>
inline Vector2<T> operator-(const T& a, const Vector2<T>& b)
{
    return Vector2<T>(a - b.x, a - b.y);
}

template <typename T>
inline Vector2<T> operator*(const T& a, const Vector2<T>& b)
{
    return Vector2<T>(a * b.x, a * b.y);
}

//! Float-type 2D vector.
typedef Vector2<float> Vector2F;

//! Double-type 2D vector.
typedef Vector2<double> Vector2D;


#endif