#pragma once

#include "gl/vertex_array.hpp"

namespace nith
{
    class Mesh
    {
    public:
        
        Mesh():
            m_ibo(gl::GLDataType::Uint) 
        {
            m_vao.bind();
            m_vbo.bind();
            m_vao.setIndex(m_ibo);
        }

        template<typename T>
        void setVertices(const std::vector<T>& vertices)
        {
            m_vbo.bind();
            m_vbo.setData(vertices);
        }

        template<typename T>
        void setVertices(T* vertices, const u32& size)
        {
            m_vbo.bind();
            m_vbo.setData((void*) vertices, size * sizeof(T));
        }

        template<typename T>
        void setIndices(const std::vector<T>& indices)
        {
            m_ibo.bind();
            m_ibo.setData(indices);
        }

        template<typename T>
        void setIndices(T* indices, const u32& size)
        {
            m_ibo.bind();
            m_ibo.setData((void*) indices, size * sizeof(T));
        }

        void render()
        {
            m_vao.bind();
            m_vao.draw();
        }

        gl::VertexArray& getVertexArray() { return m_vao; }
        gl::VertexBuffer& getVertexBuffer() { return m_vbo; }
        gl::IndexBuffer& getIndexBuffer() { return m_ibo; }

    protected:
        gl::VertexArray m_vao;
        gl::VertexBuffer m_vbo;
        gl::IndexBuffer m_ibo;
    };
}
