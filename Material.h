
#ifndef MATERIALH
#define MATERIALH

struct HitRecord;

#include "Ray.h"
#include "Rand.h"
#include "Hittable.h"

Vector3 RandomUnitInSphere()
{
    Vector3 p;
    do
    {
        p = 2.0 * Vector3(RandomDouble(), RandomDouble(), RandomDouble()) - Vector3(1, 1, 1);
    } while (p.SquaredLength() >= 1.0);
    return p;
}

float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool refract(const Vector3 &v, const Vector3 &n, float ni_over_nt, Vector3 &refracted)
{
    Vector3 uv = UnitVector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}

Vector3 reflect(const Vector3 &v, const Vector3 &n)
{
    return v - 2 * dot(v, n) * n;
}

struct Material
{
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vector3 &attenuation, Ray &scattered) const = 0;
};

struct Lambertian : Material
{
    Lambertian(const Vector3 &a) : albedo(a) {}
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vector3 &attenuation, Ray &scattered) const
    {
        Vector3 target = rec.p + rec.normal + RandomUnitInSphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Vector3 albedo;
};

struct Metal : Material
{
    Metal(const Vector3 &a, float f) : albedo(a)
    {
        f < 1 ? fuzz = f : fuzz = 1;
    }
    virtual bool scatter(const Ray &r_in, const HitRecord &rec,
                         Vector3 &attenuation, Ray &scattered) const
    {
        Vector3 reflected = reflect(UnitVector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * RandomUnitInSphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    Vector3 albedo;
    float fuzz;
};

struct Dielectric : Material
{
    Dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vector3 &attenuation, Ray &scattered) const
    {
        Vector3 outward_normal;
        Vector3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = Vector3(1.0, 1.0, 1.0);
        Vector3 refracted;
        float reflect_prob;
        float cosine;
        if (dot(r_in.direction(), rec.normal) > 0)
        {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            //         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().Length();
            cosine = dot(r_in.direction(), rec.normal) / r_in.direction().Length();
            cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().Length();
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
            reflect_prob = schlick(cosine, ref_idx);
        else
            reflect_prob = 1.0;
        if (drand48() < reflect_prob)
            scattered = Ray(rec.p, reflected);
        else
            scattered = Ray(rec.p, refracted);
        return true;
    }

    float ref_idx;
};

#endif