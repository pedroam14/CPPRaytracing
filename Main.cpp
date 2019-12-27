#include "float.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Rand.h"
#include "Camera.h"
#include <iostream>

Vector3 RandomUnitInSphere()
{
    Vector3 p;
    do
    {
        p = 2.0 * Vector3(RandomDouble(), RandomDouble(), RandomDouble()) - Vector3(1, 1, 1);
    } while (p.SquaredLength() >= 1.0);
    return p;
}

Vector3 color(const Ray &r, Hittable *world)
{
    HitRecord rec;
    return (world->hit(r, 0.001, MAXFLOAT, rec)) ? 0.5 * color(Ray(rec.p, (rec.p + rec.normal + RandomUnitInSphere()) - rec.p), world) : (1.0 - (0.5 * ((UnitVector(r.direction())).y() + 1.0))) * Vector3(1.0, 1.0, 1.0) + (0.5 * ((UnitVector(r.direction())).y() + 1.0)) * Vector3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";

    Hittable *list[2];
    list[0] = new Sphere(Vector3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vector3(0, -100.5, -1), 100);
    Hittable *world = new HittableList(list, 2);
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
                col += color(r, world);
            }
            col /= float(ns);

            //gamma correction
            col = Vector3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}