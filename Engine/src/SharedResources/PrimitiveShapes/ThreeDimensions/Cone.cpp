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

        const float baseRadius = 0.5f;
        const float pointAngles = 2 * EG_PI_FLOAT / sideCount;


        const Maths::Vector3<float> apexPoint{ 0.f, 0.5f, 0.f };
        const Maths::Vector3<float> baseCenterPosition{ 0.f, -0.5f, 0.f }; //apex point - height

        const Maths::Vector3<float> coneAxisDirection = Maths::Vector3<float>::Normalize(baseCenterPosition - apexPoint);

        //need a cross angle for the cone axis
        //this cannot be parrallel
        Maths::Vector3<float> helpDir = Maths::Vector3<float>(1.f, 0.f, 0.f);

        Maths::Vector3<float> baseRightDir = Maths::Vector3<float>::Normalize(Maths::Vector3<float>::Cross(coneAxisDirection, helpDir));
        Maths::Vector3<float> baseForwardDir = Maths::Vector3<float>::Cross(coneAxisDirection, baseRightDir);

        std::vector<float> vertexData
        {
            apexPoint.x, apexPoint.y, apexPoint.z
        };

        std::vector<unsigned int> indexes;

        for (UINT16 i = 1; i <= sideCount; i++)
        {
            const float currentAngle = i * pointAngles;

            //base radius is 0.5f
            const Maths::Vector3<float> position = baseCenterPosition + baseRightDir * baseRadius * std::cos(currentAngle) + baseForwardDir * baseRadius * std::sin(currentAngle);

            vertexData.push_back(position.x);
            vertexData.push_back(position.y);
            vertexData.push_back(position.z);

            indexes.push_back(0);
            indexes.push_back(i);
            indexes.push_back((i % sideCount) + 1); //loop around when at sideCount
        }

        //add the bottom triangles
        vertexData.push_back(baseCenterPosition.x);
        vertexData.push_back(baseCenterPosition.y);
        vertexData.push_back(baseCenterPosition.z);

        for (UINT16 i = 1; i <= sideCount; i++)
        {
            indexes.push_back(sideCount + 1); //base center position
            indexes.push_back(i);
            indexes.push_back((i % sideCount) + 1);
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

        //each side has three vertexes
        //the bottom has side count indexes as well so double it
        coneMesh.indexCount = sideCount * 6;

        return coneMesh;
    }
}
