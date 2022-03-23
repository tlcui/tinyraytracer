#pragma once
#ifndef VECTOR3_H_
#define VECTOR3_H_


#include "vector.h"
#include "vector2.h"
#include <algorithm>
#include <tuple>
#include "utilities.h"

template <typename T>
class Vector<T, 3> final
{
public:
    static_assert(std::is_floating_point<T>::value,
        "Vector only can be instantiated with floating point types");

    //! X (or the first) component of the vector.
    T x;

    //! Y (or the second) component of the vector.
    T y;

    //! Z (or the third) component of the vector.
    T z;

    //! Constructs default vector (0, 0, 0).
    constexpr Vector() : x(0), y(0), z(0) {}

    //! Constructs vector with given parameters x_ and y_.
    constexpr Vector(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

    static constexpr Vector<T, 3> zero() { return Vector<T, 3>(); }

    //! Constructs vector with initializer list.
    template <typename U>
    Vector(const std::initializer_list<U>& lst);

    //! Copy constructor.
    constexpr Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

    //! Set both x and y components to s.
    void set(T s);

    //! Set x and y components with given parameters.
    void set(T newX, T newY, T newZ);

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
    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;

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

    //! Compute the cross product.
    Vector cross(const Vector& v) const;

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

    //! Returns true if other is similar to this vector.
    bool is_similar(const Vector& other,
        T epsilon = std::numeric_limits<T>::epsilon()) const;

    //! 镜面反射 n为单位法向量
    Vector reflect(const Vector& n);

    //! 折射 n为单位法向量
    Vector refract(const Vector& n, T eta_over_eta1);

    inline static Vector<T, 3> random() 
    {
        return Vector<T, 3>(random_generate<T>(), random_generate<T>(), random_generate<T>());
    }

    inline static Vector<T, 3> random(T min, T max) 
    {
        return Vector<T, 3>(random_generate(min, max), random_generate(min, max), random_generate(min, max));
    }
};



template <typename T>
template <typename U>
inline Vector<T, 3>::Vector(const std::initializer_list<U>& lst) {
    set(lst);
}

template <typename T>
inline void Vector<T, 3>::set(T s) {
    x = s;
    y = s;
    z = s;
}

template <typename T>
inline void Vector<T, 3>::set(T newX, T newY, T newZ) {
    x = newX;
    y = newY;
    z = newZ;
}

template <typename T>
template <typename U>
inline void Vector<T, 3>::set(const std::initializer_list<U>& lst) {
    assert(lst.size() == 3);

    auto inputElem = lst.begin();
    x = static_cast<T>(*inputElem);
    y = static_cast<T>(*(++inputElem));
    z = static_cast<T>(*(++inputElem));
}

template <typename T>
inline void Vector<T, 3>::set(const Vector& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

template <typename T>
inline void Vector<T, 3>::setZero() {
    x = 0;
    y = 0;
    z = 0;
}

template <typename T>
T& Vector<T, 3>::operator[](size_t i) {
    assert(i < 3);
    return (&x)[i];
}

template <typename T>
const T& Vector<T, 3>::operator[](size_t i) const {
    assert(i < 3);
    return (&x)[i];
}

template <typename T>
template <typename U>
inline Vector<T, 3>& Vector<T, 3>::operator=(const std::initializer_list<U>& lst) {
    set(lst);
    return (*this);
}

template <typename T>
inline Vector<T, 3>& Vector<T, 3>::operator=(const Vector& v) {
    set(v);
    return (*this);
}

template <typename T>
inline Vector<T, 3> Vector<T, 3>::operator+(const Vector& other) const
{
    return Vector<T, 3>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
inline Vector<T, 3> Vector<T, 3>::operator-(const Vector& other) const
{
    return Vector<T, 3>(x - other.x, y - other.y, z - other.z);
}

template<typename T>
inline Vector<T, 3> Vector<T, 3>::operator*(const Vector& other) const
{
    return Vector<T, 3>(x * other.x, y * other.y, z * other.z);
}

template<typename T>
inline Vector<T, 3> Vector<T, 3>::operator/(const Vector& other) const
{
    return Vector<T, 3>(x / other.x, y / other.y, z / other.z);
}

template <typename T>
inline Vector<T, 3>& Vector<T, 3>::operator+=(const Vector& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template <typename T>
inline Vector<T, 3>& Vector<T, 3>::operator-=(const Vector& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template <typename T>
inline Vector<T, 3> Vector<T, 3>:: operator+(const T& s) const
{
    return Vector<T, 3>(x + s, y + s, z + s);
}

template <typename T>
inline Vector<T, 3> Vector<T, 3>:: operator-(const T& s) const
{
    return Vector<T, 3>(x - s, y - s, z - s);
}

template <typename T>
inline Vector<T, 3> Vector<T, 3>:: operator*(const T& s) const
{
    return Vector<T, 3>(x * s, y * s, z * s);
}

template <typename T>
inline Vector<T, 3> Vector<T, 3>:: operator/(const T& s) const
{
    return Vector<T, 3>(x / s, y / s, z / s);
}

template <typename T>
inline Vector<T, 3>& Vector<T, 3>:: operator+=(const T& s)
{
    x += s;
    y += s;
    z += s;
    return *this;
}
template <typename T>
inline Vector<T, 3>& Vector<T, 3>:: operator-=(const T& s)
{
    x -= s;
    y -= s;
    z -= s;
    return *this;
}

template <typename T>
inline Vector<T, 3>& Vector<T, 3>:: operator*=(const T& s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

template <typename T>
inline Vector<T, 3>& Vector<T, 3>:: operator/=(const T& s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

template <typename T>
inline T Vector<T, 3>::dot(const Vector& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

template<typename T>
inline Vector<T,3> Vector<T, 3>::cross(const Vector& v) const
{
    return Vector(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

template<typename T>
inline bool Vector<T, 3>::operator==(const Vector& other) const
{
    return !(x != other.x || y != other.y || z != other.z);
}

template<typename T>
inline bool Vector<T, 3>::operator!=(const Vector& other) const
{
    return x != other.x || y != other.y || z != other.z;
}

template<typename T>
inline T Vector<T, 3>::norm() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template<typename T>
inline T Vector<T, 3>::norm_squared() const
{
    return x * x + y * y + z * z;
}

template<typename T>
inline void Vector<T, 3>::normalize()
{
    T _norm = norm();
    x /= _norm;
    y /= _norm;
    z /= _norm;
}

template<typename T>
inline bool Vector<T, 3>::is_similar(const Vector& other, T epsilon) const
{
    return (std::fabs(x - other.x) < epsilon) &&
        (std::fabs(y - other.y) < epsilon) &&
        (std::fabs(z - other.z) < epsilon);
}

template<typename T>
inline Vector<T, 3> Vector<T, 3>::reflect(const Vector& n)
{
    return (*this - 2*dot(n)*n);
}

template<typename T>
inline Vector<T, 3> Vector<T, 3>::refract(const Vector<T, 3>& n, T eta_over_eta1)
{
    // 将折射方向分解为垂直和水平分量，分别计算，最后求和
    auto cos_theta = fmin(dot(-n), 1.0);
    Vector<T, 3> r_out_perp = eta_over_eta1 * (*this + cos_theta * n);
    Vector<T, 3> r_out_parallel = -std::sqrt(fabs(1.0 - r_out_perp.norm_squared())) * n;
    return r_out_perp + r_out_parallel;
}

template<typename T>
inline Vector<T, 3> Vector<T, 3>::normalized() const
{
    T _norm = norm();
    return Vector<T, 3>(x / _norm, y / _norm, z / _norm);
}


template<typename T>
inline Vector<T, 3> random_in_unit_sphere()
{
    while (true)
    {
        auto p = Vector<T, 3>::random(-1, 1);
        if (p.norm_squared() >= 1) continue;
        return p;
    }
}

template<typename T>
inline Vector<T, 3> random_unit_vector()
{
    return random_in_unit_sphere<T>().normalized();
}

template<typename T>
inline Vector<T, 3> random_in_hemisphere(const Vector<T,3>& normal)
{
    Vector<T,3> in_unit_sphere (random_in_unit_sphere<T>());
    if (in_unit_sphere.dot(normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

template<typename T>
inline Vector<T, 3> random_in_unit_disk()
{
    while (true)
    {
        auto p = Vector<T, 3>(random_generate<T>(-1, 1), random_generate<T>(-1, 1), 0);
        if (p.norm_squared() >= 1) continue;
        return p;
    }
}


//! Type alias for two dimensional vector.
template <typename T>
using Vector3 = Vector<T, 3>;

//! Negative sign operator.
template <typename T>
inline Vector3<T> operator-(const Vector3<T>& a)
{
    return Vector3<T>(-a.x, -a.y, -a.z);
}

template <typename T>
inline Vector3<T> operator+(const T& a, const Vector3<T>& b)
{
    return Vector3<T>(a + b.x, a + b.y, a + b.z);
}

template <typename T>
inline Vector3<T> operator-(const T& a, const Vector3<T>& b)
{
    return Vector3<T>(a - b.x, a - b.y, a - b.z);
}

template <typename T>
inline Vector3<T> operator*(const T& a, const Vector3<T>& b)
{
    return Vector3<T>(a * b.x, a * b.y, a * b.z);
}

//! Float-type 3D vector.
typedef Vector3<float> Vector3F;

//! Double-type 3D vector.
typedef Vector3<double> Vector3D;

template<typename T>
using Color = Vector3<T>;

using ColorF = Color<float>;
using ColorD = Color<double>;

template<typename T>
using Point3 = Vector3<T>;

using Point3F = Point3<float>;
using Point3D = Point3<double>;


#endif

