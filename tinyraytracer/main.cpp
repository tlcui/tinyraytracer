#include <array>
#include <iostream>
#include "vector.h"
#include "vector3.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "utilities.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include <ctime>
#include <tbb/parallel_for.h>


template<typename T>
Color<T> ray_color(const Ray<T>& r, const Hittable<T>& world, int depth) 
{
    if (depth <= 0) return Color<T>::zero();

    hit_record<T> rec;
    if (world.hit(r, 0.0001, MAX_DOUBLE, rec)) {
        Ray<T> scattered;
        Color<T> attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return Color<T>(0, 0, 0);
    }
    Vector3<T> unit_direction = r.direction().normalized();
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Color<T>(1.0, 1.0, 1.0) + t * Color<T>(0.5, 0.7, 1.0);
}


Hittable_list<double> random_scene() 
{
    Hittable_list<double> world;

    auto ground_material = make_shared<Lambertian<double>>(ColorD(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere<double>>(Point3D(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_generate<double>();
            Point3D center(a + 0.9 * random_generate<double>(), 0.2, b + 0.9 * random_generate<double>());

            if ((center - Point3D(4, 0.2, 0)).norm() > 0.9) {
                shared_ptr<Material<double>> sphere_material;

                if (choose_mat < 0.7) {
                    // diffuse
                    auto albedo = ColorD::random() * ColorD::random();
                    sphere_material = make_shared<Lambertian<double>>(albedo);
                    world.add(make_shared<Sphere<double>>(center, random_generate(0.15 , 0.25), sphere_material));
                }
                else if (choose_mat < 0.9) {
                    // metal
                    auto albedo = ColorD::random(0.5, 1);
                    auto fuzz = random_generate<double>(0, 0.5);
                    sphere_material = make_shared<Metal<double>>(albedo, fuzz);
                    world.add(make_shared<Sphere<double>>(center, random_generate(0.15, 0.25), sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric<double>>(1.5);
                    world.add(make_shared<Sphere<double>>(center, random_generate(0.15, 0.25), sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric<double>>(1.5);
    world.add(make_shared<Sphere<double>>(Point3D(0, 1, 0), random_generate(0.9, 1.1), material1));

    auto material2 = make_shared<Lambertian<double>>(ColorD(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere<double>>(Point3D(-4, 1, 0), random_generate(0.9, 1.1), material2));

    auto material3 = make_shared<Metal<double>>(ColorD(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere<double>>(Point3D(4, 1, 0), random_generate(0.9, 1.1), material3));

    return world;
}

int main() 
{
    auto start = clock();


    // Image

    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // World
    auto world = random_scene();

    // Camera

    Point3D lookfrom(13, 2, 3);
    Point3D lookat(0, 0, 0);
    Vector3D v_up(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera<double> cam(lookfrom, lookat, v_up, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        tbb::parallel_for(tbb::blocked_range<size_t>(0, image_width), [&](const tbb::blocked_range<size_t>& r) 
            {
            for (int i = r.begin(); i != r.end(); ++i) 
            {
                Color<double> pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random_generate<double>()) / (image_width - 1);
                    auto v = (j + random_generate<double>()) / (image_height - 1);
                    Ray<double> r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, world, max_depth);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
            });
    }

    auto end = clock();
    std::cerr << "\nDone.\n";
    std::cerr << "time consumption: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "s\n";
    
    //single-thread 2983.71s
    //multi-thread 430.159s
}