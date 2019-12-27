#define RAYH
#include <iostream>
#include "Ray.h"

float HitSphere(const Vector3 &center, float radius, const Ray &r)
{
    Vector3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant < 0) ? -1.0 : (-b - sqrt(discriminant)) / (2.0 * a);
}

Vector3 color(const Ray &r)
{
    float t = HitSphere(Vector3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        Vector3 N = unit_vector(r.point_at_parameter(t) - Vector3(0, 0, -1));
        return 0.5 * Vector3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    Vector3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";
    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0.0);
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vector3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}