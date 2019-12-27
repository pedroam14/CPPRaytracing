#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "Hittable.h"

struct HittableList : Hittable
{
    HittableList() {}
    HittableList(Hittable **l, int n)
    {
        list = l;
        listSize = n;
    }
    virtual bool hit(
        const Ray &r, float tmin, float tmax, HitRecord &rec) const;
    Hittable **list;
    int listSize;
};

bool HittableList::hit(const Ray &r, float tMin, float tMax,
                       HitRecord &rec) const
{

    HitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tMax;
    for (int i = 0; i < listSize; i++)
    {
        if (list[i]->hit(r, tMin, closestSoFar, tempRec))
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}

#endif