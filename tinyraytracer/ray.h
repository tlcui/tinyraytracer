#pragma once
#ifndef RAY_H_
#define RAY_H_

#include "vector3.h"

template<typename T>
class Ray
{
public:
    Ray() {}
    Ray(const Point3<T>& origin, const Vector3<T>& direction)
        : orig(origin), dir(direction)
    {}

    Point3<T> origin() const { return orig; }
    Vector3<T> direction() const { return dir; }

    Point3<T> at(T t) const 
    {
        return orig + t * dir;
    }

public:
    Point3<T> orig;
    Vector3<T> dir;
};
#endif