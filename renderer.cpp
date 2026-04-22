#include "renderer.h"

olc::Pixel LightingToPixel(float& l)
{

    uint8_t intensity = (uint8_t)(l * 255.0f);

    return olc::Pixel(intensity, intensity, intensity);
}

void CalculateShade(triangle& tri, const vec3d& lightDir)
{
    vec3d edge1, edge2, crossProduct, normalizedCrossProduct;
     
    SubtractVec3d(tri.p[1], tri.p[0], edge1);
    SubtractVec3d(tri.p[2], tri.p[0], edge2);

    CrossProductVec3d(edge1, edge2, crossProduct);
    NormalizeVec3d(crossProduct, normalizedCrossProduct);

    tri.shade = DotProductVec3d(normalizedCrossProduct, lightDir);
}

triangle CalculateCamera(triangle& tri, const mat4x4& world)
{   
    triangle out;

    out.p[0] = MulitplyMatrixVec3d(tri.p[0], world);
    out.p[1] = MulitplyMatrixVec3d(tri.p[1], world);
    out.p[2] = MulitplyMatrixVec3d(tri.p[2], world);

    return out;
}

triangle CalculateTranslation(const triangle& tri, const mat4x4& matProj, const int32_t& width)
{
    triangle triTranslated = tri;
    triTranslated.p[0].z = tri.p[0].z + 3.0f;
    triTranslated.p[1].z = tri.p[1].z + 3.0f;
    triTranslated.p[2].z = tri.p[2].z + 3.0f;

    triTranslated.p[0] = MulitplyMatrixVec3d(triTranslated.p[0], matProj);
    triTranslated.p[1] = MulitplyMatrixVec3d(triTranslated.p[1], matProj);
    triTranslated.p[2] = MulitplyMatrixVec3d(triTranslated.p[2], matProj);

    // Scale into view
    triTranslated.p[0].x += 1.0f; triTranslated.p[0].y += 1.0f;
    triTranslated.p[1].x += 1.0f; triTranslated.p[1].y += 1.0f;
    triTranslated.p[2].x += 1.0f; triTranslated.p[2].y += 1.0f;

    triTranslated.p[0].x *= 0.5f * (float)width;
    triTranslated.p[0].y *= 0.5f * (float)width;
    triTranslated.p[1].x *= 0.5f * (float)width;
    triTranslated.p[1].y *= 0.5f * (float)width;
    triTranslated.p[2].x *= 0.5f * (float)width;
    triTranslated.p[2].y *= 0.5f * (float)width;

    return triTranslated;
}

void CalculateYawPitch(float& yaw, float& pitch)
{
    SetMousePos()
}

