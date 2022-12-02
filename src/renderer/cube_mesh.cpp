#include "cube_mesh.hpp"

namespace nith
{
    const f32 CubeMesh::Vertices[] = {
        +0.5f, -0.5f, +0.5f,
        +0.5f, +0.5f, +0.5f,
        -0.5f, +0.5f, +0.5f,
        -0.5f, -0.5f, +0.5f,
        +0.5f, -0.5f, -0.5f,
        +0.5f, +0.5f, -0.5f,
        -0.5f, +0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        +0.5f, -0.5f, -0.5f,
        +0.5f, +0.5f, -0.5f,
        +0.5f, +0.5f, +0.5f,
        +0.5f, -0.5f, +0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, +0.5f, -0.5f,
        -0.5f, +0.5f, +0.5f,
        -0.5f, -0.5f, +0.5f,
        +0.5f, +0.5f, -0.5f,
        +0.5f, +0.5f, +0.5f,
        -0.5f, +0.5f, +0.5f,
        -0.5f, +0.5f, -0.5f,
        +0.5f, -0.5f, +0.5f,
        +0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, +0.5f,
    };

    const u32 CubeMesh::Indices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };

    CubeMesh::CubeMesh()
    {
        m_vao.bind();

        m_vao.setBuffer(m_vbo, {
            { gl::GLDataType::Vec3 }
        });

        m_vao.setDrawCount(sizeof(Indices) / sizeof(u32));

        setVertices(Vertices, sizeof(Vertices) / sizeof(f32));
        setIndices(Indices, sizeof(Indices) / sizeof(u32));
    }
}