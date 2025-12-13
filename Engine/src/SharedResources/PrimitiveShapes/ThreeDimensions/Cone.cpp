/*
* File: Cone.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-12 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Cone.h"

//ENGN
#include "Renderer/Core/RenderCore.h"
#include "Core/Maths/Math.h"
#include "Core/Logger.h"

namespace Engine::Utility
{
    Mesh CreateCone(UINT16 sideCount)
    {
        Mesh coneMesh;

        if (sideCount < 3)
        {
            Logger::LogMessage(Logger::LogType::Message, "<Cone.cpp> (Create Cone), Cone has insufficient amount of sides, adjusting to 3");
            sideCount = 3;
        }

        //Calculate the sides of the cone

        //height is 1.f

        const float circumference = 2 * EG_PI_FLOAT * 0.5f;
        const float pointAngles = 2 * EG_PI_FLOAT / sideCount;

        const Maths::Vector3<float> apexPoint{ 0.f, 0.5f, 0.f };
        const Maths::Vector3<float> baseCenterPosition = apexPoint - Maths::Vector3{ 0.f, 1.f, 0.f };
        const Maths::Vector3<float> coneAxisDirection = Maths::Vector3<float>::Normalize(baseCenterPosition - apexPoint);

        //need a cross angle for the cone axis
       // Maths::Vector3<float> helpDir = coneAxisDirection.Length() < 0.99 ? Maths::Vector3<float>(0.f, 1.f, 0.f) : Maths::Vector3<float>(1.f, 0.f, 0.f);
        Maths::Vector3<float> helpDir = Maths::Vector3<float>(0.f, 1.f, 0.f);
        const Maths::Vector3<float> baseRightDir = Maths::Vector3<float>::Normalize(Maths::Vector3<float>::Cross(coneAxisDirection, helpDir.Absolute()));
        const Maths::Vector3<float> baseForwardDir = Maths::Vector3<float>::Cross(coneAxisDirection, baseRightDir);

        std::vector<float> vertexData
        {
            apexPoint.x, apexPoint.y, apexPoint.z
        };

        std::vector<unsigned int> indexes;

        for (UINT16 i = 0; i < sideCount; i++)
        {
            const float currentAngle = i * pointAngles;

            const float cosAngle = cos(currentAngle);
            const Maths::Vector3<float> halfCosRightDir{ 0.5f * baseRightDir.x * cosAngle, 0.5f * baseRightDir.y * cosAngle, 0.5f * baseRightDir.z * cosAngle };

            const float sinAngle = sin(currentAngle);
            const Maths::Vector3<float> halfSinBaseDir{ 0.5f * sinAngle * baseForwardDir.x, 0.5f * sinAngle * baseForwardDir.y, 0.5f * sinAngle * baseForwardDir.z };

            const Maths::Vector3<float> position = baseCenterPosition + halfCosRightDir + halfSinBaseDir;

            vertexData.push_back(position.x);
            vertexData.push_back(position.y);
            vertexData.push_back(position.z);

            if (i % 2 == 0 && i != 0)
            {
                indexes.push_back(0);
                indexes.push_back(i);
                indexes.push_back(i - 1);
            }
        }

        //now the mesh can finally be setup

        coneMesh.Create();

        coneMesh.vao.Bind();

        coneMesh.vbo.Bind();
        coneMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);

        coneMesh.ebo.Bind();
        coneMesh.ebo.BufferData(indexes, GL_STATIC_DRAW);
        
        Renderer::AttribData attribData = { Renderer::ShaderDataType::Float3 };
        coneMesh.vao.SetAttribData(0, attribData, coneMesh.vbo, coneMesh.ebo);

        coneMesh.vao.UnBind();
        coneMesh.vbo.UnBind();
        coneMesh.ebo.UnBind();

        return coneMesh;
    }
}
