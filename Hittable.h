#ifndef HITTABLEH
#define HITTABLEH

#include "Ray.h"

struct HitRecord
{
    float t;
    Vector3 p;
    Vector3 normal;
};

struct Hittable
{
    virtual bool hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const = 0;
};

#endif