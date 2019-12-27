#ifndef SPHEREH
#define SPHEREH

#include "Hittable.h"

struct Sphere : Hittable
{

    Sphere() {}
    Sphere(Vector3 cen, float r) : center(cen), radius(r){};
    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
    Vector3 center;
    float radius;
};

bool Sphere::hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const
{
    Vector3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif