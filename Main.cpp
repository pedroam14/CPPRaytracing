#include "float.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include <iostream>


Vector3 color(const Ray &r, Hittable *world, int depth)
{
    HitRecord rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        Ray scattered;
        Vector3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return Vector3(0, 0, 0);
        }
    }
    else
    {
        Vector3 unit_direction = UnitVector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";

    Hittable *list[4];
    list[0] = new Sphere(Vector3(0, 0, -1), 0.5, new Lambertian(Vector3(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vector3(0, -100.5, -1), 100, new Lambertian(Vector3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2)));
    list[3] = new Sphere(Vector3(-1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.8, 0.8)));
    Hittable *world = new HittableList(list, 4);

    Camera cam;
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vector3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + RandomDouble()) / float(nx);
                float v = float(j + RandomDouble()) / float(ny);
                Ray r = cam.GetRay(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}