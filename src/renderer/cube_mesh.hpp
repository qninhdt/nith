#pragma once

#include "renderer/mesh.hpp"

namespace nith
{
    class CubeMesh : public Mesh
    {
    public:
        static const f32 Vertices[];
        static const u32 Indices[];

        CubeMesh();
    };
}