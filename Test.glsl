/**
 * b1_ch10.glsl
 * Ray Tracing in One Weekend
 * Chapter 10 - Dialectrics
 */

 #include "./common.glsl"

 #iChannel0 "self"

bool hit_world(Ray r, float tmin, float tmax, out HitRecord rec)
{
    bool hit = false;
    rec.t = tmax;

    if(hit_sphere(
        createSphere(vec3(0.0, 0.0, -1.0), 0.5),
        r,
        tmin,
        rec.t,
        rec))
    {
        hit = true;
        rec.material = createDiffuseMaterial(vec3(0.1, 0.2, 0.5));
    }

    if(hit_sphere(
        createSphere(vec3(1.0, 0.0, -1.0), 0.5),
        r,
        tmin,
        rec.t,
        rec))
    {
        hit = true;
        rec.material = createMetalMaterial(vec3(0.8, 0.6, 0.2), 0.3);
    }

    if(hit_sphere(
        createSphere(vec3(-1.0, 0.0, -1.0), 0.5),
        r,
        tmin,
        rec.t,
        rec))
    {
        hit = true;
        rec.material = createDialectricMaterial(vec3(0.8), 1.5);
    }

    if(hit_sphere(
        createSphere(vec3(-1.0, 0.0, -1.0), -0.45),
        r,
        tmin,
        rec.t,
        rec))
    {
        hit = true;
        rec.material = createDialectricMaterial(vec3(0.8), 1.5);
    }

    if(hit_sphere(
        createSphere(vec3(0.0, -100.5, -1.0), 100.0),
        r,
        tmin,
        rec.t,
        rec))
    {
        hit = true;
        rec.material = createDiffuseMaterial(vec3(0.8, 0.8, 0.0));
    }

    return hit;
}

vec3 color(Ray r)
{
    HitRecord rec;
    vec3 col = vec3(1.0);
    for(int i = 0; i < 20; ++i)
    {
        if(hit_world(r, 0.001, 10000.0, rec))
        {
            Ray scatterRay;
            vec3 atten;
            if(scatter(r, rec, atten, scatterRay))
            {
                col *= atten;
                r = scatterRay;

            }
            else
            {
                return vec3(0.0);
            }
        }
        else
        {
            float t = 0.5 * (r.d.y + 1.0);
            col *= mix(vec3(1.0), vec3(0.5, 0.7, 1.0), t);
            return col;
        }
    }
    return col;
}

void main()
{
    gSeed = float(baseHash(floatBitsToUint(gl_FragCoord.xy))) / float(0xffffffffU) + iTime;

    vec2 mouse = iMouse.xy / iResolution.xy;
    mouse.x = mouse.x * 2.0 - 1.0;

    Camera cam = createCamera(
        vec3(mouse.x * 5.0, mouse.y * 5.0, 1.0),    // camera position
        vec3(0.0, 0.0, -1.0),   // look at
        vec3(0.0, 1.0, 0.0),    // world up vector
        90.0,
        iResolution.x / iResolution.y);

    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec4 prev = texture(iChannel0, uv);
    vec3 prevLinear = toLinear(prev.xyz);
    prevLinear *= prev.w;

    uv = (gl_FragCoord.xy + hash2(gSeed)) / iResolution.xy;
    vec3 col = color(getRay(cam, uv));

    if(iMouseButton.x != 0.0 || iMouseButton.y != 0.0)
    {
        col = toGamma(col);
        gl_FragColor = vec4(col, 1.0);
        return;
    }
    if(prev.w > 5000.0)
    {
        gl_FragColor = prev;
        return;
    }

    col = (col + prevLinear);
    float w = prev.w + 1.0;
    col /= w;
    col = toGamma(col);
    gl_FragColor = vec4(col, w);
}
