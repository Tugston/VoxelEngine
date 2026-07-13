/*
* File: Arrow.cpp
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
#include "Arrow.h"

//ENGN
#include "Core/Maths/Math.h"
#include "Renderer/Core/RenderCore.h"

#define BRANCH_DIVISOR 1.25
#define STEM_LENGTH 1

namespace Engine::Utility
{
    Mesh CreateArrow()
    {
        Mesh arrowMesh;
        const int sideCount = 6;

        //*****************************************
        //THIS IS PULLED STRAIGHT FROM THE CONE.CPP
        //*****************************************

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
        
        //*****************************************
        //THIS IS PULLED STRAIGHT FROM THE CONE.CPP
        //*****************************************

        //now need to add the hole and cyllinder for the actual arrow
        const float branchRadius = baseRadius / BRANCH_DIVISOR;
        LOG_MSG("Branch Radius: {}", branchRadius);

        //cyllinder only needs to care about the ring hole of base points
        const int cyllinderStart = vertexData.size() - 1;

        //skip the apex point
        const int currentSize = vertexData.size(); //loop adds to it
        for (UINT16 i = 3; i < currentSize; i += 3)
        {
            Maths::Vector3<float> currentPoint = Maths::Vector3<float>{ vertexData.at(i), vertexData.at(i + 1), vertexData.at(i + 2) };
            Maths::Vector3<float> targetDirection = currentPoint - baseCenterPosition;
            targetDirection.Normalize();

            const Maths::Vector3<float> adjustedPosition = baseCenterPosition + targetDirection * branchRadius;

            LOG_ERR("");
            LOG_MSG("-- TARGET DIRECTION --");
            LOG_MSG("X: {}", targetDirection.x);
            LOG_MSG("Y: {}", targetDirection.y);
            LOG_MSG("Z: {}", targetDirection.z);
            LOG_MSG("-- TARGET DIRECTION --");
            LOG_MSG("-- ADJUSTED POSITION --");
            LOG_MSG("X: {}", adjustedPosition.x);
            LOG_MSG("Y: {}", adjustedPosition.y);
            LOG_MSG("Z: {}", adjustedPosition.z);
            LOG_MSG("-- ADJUSTED POSITION --");
            LOG_MSG("-- SIDE VERTEX --");
            LOG_MSG("X: {}", vertexData.at(i));
            LOG_MSG("Y: {}", vertexData.at(i + 1));
            LOG_MSG("Z: {}", vertexData.at(i + 2));
            LOG_MSG("-- SIDE VERTEX --");
            LOG_MSG("-- BASE CENTER POSITION --");
            LOG_MSG("X: {}", baseCenterPosition.x);
            LOG_MSG("Y: {}", baseCenterPosition.y);
            LOG_MSG("Z: {}", baseCenterPosition.z);
            LOG_MSG("-- BASE CENTER POSITION --");
            LOG_ERR("");

            vertexData.push_back(adjustedPosition.x);
            vertexData.push_back(adjustedPosition.y);
            vertexData.push_back(adjustedPosition.z); 
        } 

        //need to add indices in third loop
        //to ensure arll the cone's points are formed
        for (UINT16 i = 1; i <= sideCount; i++)
        {
            const int outerCurrent = i;
            const int outerNext = (i % sideCount) + 1;

            const int innerCurrent = sideCount + i;
            const int innerNext = sideCount + ((i % sideCount) + 1);

            //first triangle of base section
            indexes.push_back(outerCurrent);
            indexes.push_back(outerNext);
            indexes.push_back(innerCurrent);

            //second triangle of base section
            indexes.push_back(innerCurrent);
            indexes.push_back(outerNext);
            indexes.push_back(innerNext);
        }

        arrowMesh.Create();

        arrowMesh.vao.Bind();

        arrowMesh.vbo.Bind();
        arrowMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);

        arrowMesh.ebo.Bind();
        arrowMesh.ebo.BufferData(indexes, GL_STATIC_DRAW);

        Renderer::AttribData data = { Renderer::ShaderDataType::Float3 };
        arrowMesh.vao.SetAttribData(0, data, arrowMesh.vbo, arrowMesh.ebo);

        arrowMesh.vao.UnBind();
        arrowMesh.ebo.UnBind();
        arrowMesh.vbo.UnBind();

        //3 count for the sides of the cone
        //6 count for the ring around the cyllinder at the base
        arrowMesh.indexCount = (sideCount * 3) + (sideCount * 6);

        return arrowMesh;
    }
}
