#pragma once
#include "math.h"
#include <vector>

struct triangle
{
    vec3d p[3];
    float shade;
};

struct mesh
{
    std::vector<triangle> tris;
};