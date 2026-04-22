#pragma once
#include <cmath>

struct vec3d
{
    float x, y, z;
};

struct mat4x4
{
    float m[4][4] = { 0 };
};

// Vector Ops
void NormalizeVec3d(const vec3d&, vec3d&);
void SubtractVec3d(const vec3d&, const vec3d&, vec3d&);
void CrossProductVec3d(const vec3d&, const vec3d&, vec3d&);
float DotProductVec3d(const vec3d&, const vec3d&);

// Matrix Ops
void MulitplyMatrixVec3d(const vec3d&, vec3d&, const mat4x4&);
vec3d MulitplyMatrixVec3d(const vec3d&, const mat4x4&);