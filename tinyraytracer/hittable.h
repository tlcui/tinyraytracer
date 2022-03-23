#pragma once
#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "ray.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

template<typename T>
class Material;

// �����ߺ������ཻ�����������µĽṹ������¼�ཻ����Ϣ
template<typename T>
struct hit_record 
{
    Point3<T> p;
    Vector3<T> normal;
    shared_ptr<Material<T>> mat_ptr;
    T t;
    bool front_face;

    inline void set_face_normal(const Ray<T>& r, const Vector3<T>& outward_normal) 
    {
        front_face = outward_normal.dot(r.direction()) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

template<typename T>
class Hittable 
{
public:
    virtual bool hit(const Ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const = 0;
};

#endif