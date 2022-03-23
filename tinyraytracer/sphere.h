#pragma once
#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"
#include "vector3.h"
#include <cmath>
#include "material.h"

template<typename T>
class Sphere : public Hittable<T>
{
public:
    Sphere() {}
    Sphere(const Point3<T>& cen, T r, shared_ptr<Material<T>> m) : center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(
        const Ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const override;

public:
    Point3<T> center;
    T radius;

    //��Sphere�Ĳ���
    shared_ptr<Material<T>> mat_ptr; //Ϊ�˲�����̬��������ʵ�ʹ���һ��Sphereʱ����Ӧ��ָ��ĳ��Material�����������Metal<T>�����
};

template<typename T>
bool Sphere<T>::hit(const Ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const 
{
    Vector3<T> oc = r.origin() - center;
    auto a = r.direction().norm_squared();
    auto half_b =oc.dot(r.direction());
    auto c = oc.norm_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    Vector3<T> outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;


    return true;
}

#endif