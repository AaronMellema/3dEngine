#include "math.h"

/*
    Vector Operations
 */
void NormalizeVec3d(const vec3d& i, vec3d& o)
{
    float l = sqrt(i.x * i.x + i.y * i.y + i.z * i.z);

    if (abs(l) < 0.000001f)
    {
        o.x = 0;
        o.y = 0;
        o.z = 0;
        return;
    }

    o.x = i.x / l;
    o.y = i.y / l;
    o.z = i.z / l;
}

void SubtractVec3d(const vec3d& i, const vec3d& j, vec3d& o)
{
    o.x = i.x - j.x;
    o.y = i.y - j.y;
    o.z = i.z - j.z;
}

void CrossProductVec3d(const vec3d& i, const vec3d& j, vec3d& o)
{
    o.x = i.y * j.z - i.z * j.y;
    o.y = i.z * j.x - i.x * j.z;
    o.z = i.x * j.y - i.y * j.x;
}

float DotProductVec3d(const vec3d& i, const vec3d& j)
{
    return i.x * j.x + i.y * j.y + i.z * j.z;
}

/*
    Matrix Operations
 */
void MulitplyMatrixVec3d(const vec3d& i, vec3d& o, const mat4x4& m)
{
    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f)
    {
        o.x /= w; o.y /= w; o.z /= w;
    }
}

vec3d MulitplyMatrixVec3d(const vec3d& i, const mat4x4& m)
{   
    vec3d out;
    out.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
    out.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
    out.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
    float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

    if (w != 0.0f)
    {
        out.x /= w; out.y /= w; out.z /= w;
    }

    return out;
}