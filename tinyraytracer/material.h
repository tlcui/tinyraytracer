#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "utilities.h"
#include "ray.h"
//#include "hittable_list.h"

template<typename T>
struct hit_record;

template<typename T>
class Material {
public:
    virtual bool scatter(
        const Ray<T>& r_in, const hit_record<T>& rec, Color<T>& attenuation, Ray<T>& scattered
    ) const = 0;
};

template<typename T>
class Lambertian : public Material<T> 
{
public:
    Lambertian(const Color<T>& a) : albedo(a) {}

    virtual bool scatter(
        const Ray<T>& r_in, const hit_record<T>& rec, Color<T>& attenuation, Ray<T>& scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector<T>();
        
        //防止反射方向为零向量
        if (scatter_direction.is_similar(Vector3<T>::zero()))
        {
            scatter_direction = rec.normal;
        }

        scattered = Ray<T>(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    Color<T> albedo;
};


template<typename T>
class Metal : public Material<T> 
{
public:
    Metal(const Color<T>& a, T f) : albedo(a), fuzz(f<1 ? f : 1) {}

    virtual bool scatter(
        const Ray<T>& r_in, const hit_record<T>& rec, Color<T>& attenuation, Ray<T>& scattered) const override 
    {
        Vector3<T> reflected = r_in.direction().normalized().reflect(rec.normal);
        scattered = Ray<T>(rec.p, reflected + fuzz * random_in_unit_sphere<T>());
        attenuation = albedo;
        return (scattered.direction().dot(rec.normal) > 0);
    }

public:
    Color<T> albedo;
    T fuzz; //模糊反射系数
};

template<typename T>
class Dielectric : public Material<T> 
{
public:
    Dielectric(T index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(
        const Ray<T>& r_in, const hit_record<T>& rec, Color<T>& attenuation, Ray<T>& scattered
    ) const override {
        attenuation = Color<T>(1.0, 1.0, 1.0);
        T refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        Vector3<T> unit_direction = r_in.direction().normalized();
        
        //接下来需要判断是全反射还是既有反射又有折射，分别讨论
        T cos_theta = fmin(unit_direction.dot(-rec.normal), 1);
        T sin_theta = std::sqrt(1 - cos_theta * cos_theta);
        bool cannot_refract = sin_theta * refraction_ratio > 1;
        Vector3<T> direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_generate<T>())
        {
            direction = unit_direction.reflect(rec.normal);
        }
        else
        {
            direction = unit_direction.refract(rec.normal, refraction_ratio);
        }

        scattered = Ray<T>(rec.p, direction);
        return true;
    }

public:
    T ir; // Index of Refraction

private:
    static T reflectance(T cosine, T ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};
#endif