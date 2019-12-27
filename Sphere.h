#ifndef SPHEREH
#define SPHEREH

#include "Hittable.h"

struct Sphere : Hittable
{
    Sphere() {}
    Sphere(Vector3 cen, float r, Material *m)
        : center(cen), radius(r), mat_ptr(m){};
    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
    Vector3 center;
    float radius;
    Material *mat_ptr; /* NEW */
};

bool Sphere::hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
    Vector3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr; /* NEW */
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr; /* NEW */
            return true;
        }
    }
    return false;
}

#endif