#ifdef RAYH
#define RAYH
#include "Vector.h"

struct Ray
{
    Vector3 A, B;
    Ray() {}
    Ray(const Vector3 &a, const Vector3 &b)
    {
        A = a;
        B = b;
    }
    inline Vector3 origin() const { return A; }
    inline Vector3 direction() const { return B; }
    inline Vector3 pointing_at(float t) const { return A + t * B; }
};
#endif