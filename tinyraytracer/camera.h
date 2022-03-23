#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "utilities.h"
#include "vector3.h"
#include "hittable_list.h"
#include "ray.h"

template<typename T>
class Camera {
public:
    Camera(Point3<T> look_from, Point3<T> look_at, Vector3<T> v_up, T vfov, T aspect_ratio, T aperture, T focus_dist) 
        // vfov is the vertical field-of-view in degrees.
    {
        auto theta = degrees_to_radians<T>(vfov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = (look_from - look_at).normalized();
        u = v_up.cross(w).normalized();
        v = w.cross(u);

        origin = look_from;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }

    Ray<T> get_ray(T s, T t) const 
    {
        Vector3<T> rd(lens_radius * random_in_unit_disk<T>());
        Vector3<T> offset(u * rd.x + v * rd.y);
        return Ray<T>(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

private:
    Point3<T> origin;
    Point3<T> lower_left_corner;
    Vector3<T> horizontal;
    Vector3<T> vertical;
    Vector3<T> u, v, w;
    T lens_radius;
};
#endif