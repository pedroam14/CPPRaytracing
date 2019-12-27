#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

struct Camera
{
    Camera()
    {
        lowerLeftCorner = Vector3(-2.0, -1.0, -1.0);
        horizontal = Vector3(4.0, 0.0, 0.0);
        vertical = Vector3(0.0, 2.0, 0.0);
        origin = Vector3(0.0, 0.0, 0.0);
    }
    inline Ray GetRay(float u, float v)
    {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }
    Vector3 origin;
    Vector3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;
};
#endif