#pragma once
#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include "hittable.h"

#include <memory>
#include <vector>

template<typename T>
class Hittable_list : public Hittable<T> 
{
public:
    Hittable_list() {}
    Hittable_list(shared_ptr<Hittable<T>> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable<T>> object) { objects.push_back(object); }

    virtual bool hit(
        const Ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const override
    {
        hit_record<T> temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object : objects) {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

public:
    std::vector<shared_ptr<Hittable<T>>> objects;
};

/*template<typename T>
bool Hittable_list<T>::hit(const Ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const 
{
    hit_record<T> temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) 
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
*/
#endif