#pragma once
#include "geometry.h"
#include "olcPixelGameEngine.h"
#include <Windows.h>

olc::Pixel LightingToPixel(float& l);

void CalculateShade(triangle&, const vec3d&);
void CalculateDepth(triangle&);

triangle CalculateCamera(triangle&, const mat4x4&);
triangle CalculateTranslation(const triangle&, const mat4x4&, const int32_t&);

void CalculateYawPitch(float&, float&);
