#include "egpch.h"
#include "Triangle.h"

#include "Renderer/Core/RenderCore.h"

namespace Engine::Utility
{
    Mesh CreateTriangle()
    {

        Mesh triangleMesh;

        std::vector<float> vertexData = {
            0.5f, 0.f, 0.f,
            -0.5f, 0.f, 0.f,
            0.f, 0.5f, 0.f
        };

        std::vector<unsigned int> indexData = {
            0, 1, 3
        };

        triangleMesh.vao.Bind();
        triangleMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);
        triangleMesh.ebo.BufferData(indexData, GL_STATIC_DRAW);

        Renderer::AttribData atributeData = { Renderer::ShaderDataType::Float3 }; //just use defaults
        triangleMesh.vao.SetAttribData(0, atributeData, triangleMesh.vbo, triangleMesh.ebo);

        return triangleMesh;
    }
}
