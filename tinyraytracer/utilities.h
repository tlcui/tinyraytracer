// this file includes some constants and utility functions

#pragma once
#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cmath>
#include <limits>
#include <random>
#include <cstdlib>

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

//! Max size_t.
constexpr size_t MAX_SIZE = std::numeric_limits<size_t>::max();

//! Max ssize_t.
constexpr ssize_t MAX_SSIZE = std::numeric_limits<ssize_t>::max();

//! Max float.
constexpr float MAX_FLOAT = std::numeric_limits<float>::max();

//! Max double.
constexpr double MAX_DOUBLE = std::numeric_limits<double>::max();
constexpr double INF_DOUBLE = MAX_DOUBLE;

//! Float-type pi.
constexpr float PI_F = 3.14159265358979323846264338327950288f;

//! Double-type pi.
constexpr double PI_D = 3.14159265358979323846264338327950288;

//! Pi for type T.
template <typename T>
constexpr T pi() 
{
    return static_cast<T>(PI_D);
}

//! Pi for float.
template <>
constexpr float pi<float>() 
{
    return PI_F;
}

//! Pi for double.
template <>
constexpr double pi<double>() 
{
    return PI_D;
}

template<typename T>
inline T degrees_to_radians(T degrees) 
{
    return degrees * pi<T>() / 180.0;
}

template<typename T>
inline T random_generate()
{
    std::uniform_real_distribution<T> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

template<typename T>
inline T random_generate(T xmin, T xmax)
{
    std::uniform_real_distribution<T> distribution(xmin, xmax);
    static std::mt19937 generator;
    return distribution(generator);
}

template<typename T>
inline T clamp(T x, T xmin, T xmax)
{
    if (x < xmin) return xmin;
    if (x > xmax) return xmax;
    return x;
}

#endif