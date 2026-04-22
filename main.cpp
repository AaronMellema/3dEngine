#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "renderer.h"
#include "geometry.h"
#include "math.h"
#include <algorithm>

class Engine3D : public olc::PixelGameEngine
{
public:
    mesh cube;
    mat4x4 matProj, matRotX, matRotZ;

    vec3d lightDir = { 0.0f, 0.0f, -1.0f };

    bool OnUserCreate() override
    {
        

        cube.tris = {

            // SOUTH
                { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
                { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },
                  
                // EAST
                { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
                { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

                // NORTH
                { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
                { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

                // WEST
                { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
                { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

                // TOP
                { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
                { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

                // BOTTOM
                { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
                { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f }
        };


        // Projection Matrix
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14195);

        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;


        // Rotation Matrix
        float speed = 0.0001;

        // Rotation Z
        matRotZ.m[0][0] = cosf(speed);
        matRotZ.m[0][1] = sinf(speed);
        matRotZ.m[1][0] = -sinf(speed);
        matRotZ.m[1][1] = cosf(speed);
        matRotZ.m[2][2] = 1;
        matRotZ.m[3][3] = 1;

        // Rotation x
        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(speed * 0.5f);
        matRotX.m[1][2] = sinf(speed * 0.5f);
        matRotX.m[2][1] = -sinf(speed * 0.5f);
        matRotX.m[2][2] = cosf(speed * 0.5f);
        matRotX.m[3][3] = 1;

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        Render(cube);

        return true;
    }

    void Render(mesh& mesh)
    {
        for (auto& tri : mesh.tris)
        {   
            triangle temp = CalculateCamera(tri, matRotX);

            CalculateShade(tri, lightDir);
        
            temp = CalculateTranslation(tri, matProj, ScreenWidth());
            
            FillTriangle(temp.p[0].x, temp.p[0].y,
                temp.p[1].x, temp.p[1].y,
                temp.p[2].x, temp.p[2].y,
                LightingToPixel(temp.shade));

        }
    }
};

int main()
{
    Engine3D render;
    if (render.Construct(256, 240, 4, 4))
        render.Start();

    return 0;
}
