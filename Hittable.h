#ifndef HITTABLEH
#define HITTABLEH

#include "Ray.h"

struct Material;

struct HitRecord
{
    float t;
    Vector3 p;
    Vector3 normal;
    Material *mat_ptr;
};

struct Hittable
{
    virtual bool hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const = 0;
};

#endif