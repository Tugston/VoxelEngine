/*
* File: Triangle.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-26 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Triangle.h"

#include "Renderer/Core/RenderCore.h"

namespace Engine::Utility
{
    Mesh CreateTriangle()
    {

        Mesh triangleMesh;

        std::vector<float> vertexData = {
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        std::vector<unsigned int> indexData = {
            0, 1, 2
        };

        triangleMesh.Create();

        triangleMesh.vbo.Bind();
        triangleMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);

        triangleMesh.ebo.Bind();
        triangleMesh.ebo.BufferData(indexData, GL_STATIC_DRAW);

        triangleMesh.vao.Bind();

        Renderer::AttribData atributeData = { Renderer::ShaderDataType::Float3 }; //just use defaults
        triangleMesh.vao.SetAttribData(0, atributeData, triangleMesh.vbo, triangleMesh.ebo);

        triangleMesh.vao.UnBind();
        triangleMesh.ebo.UnBind();
        triangleMesh.vbo.UnBind();

        triangleMesh.indexCount = 3;

        return triangleMesh;
    }
}
