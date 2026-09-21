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
    Mesh CreateArrow(ArrowConstruct construct)
    {
        Mesh arrowMesh;

        //*****************************************
        //THIS IS PULLED STRAIGHT FROM THE CONE.CPP (kinda)
        //*****************************************

        const float pointAngles = 2 * EG_PI_FLOAT / construct.sideCount;

        const Maths::Vector3<float> apexPoint{ 0.f, 0.5, 0.f };
        const Maths::Vector3<float> baseCenterPosition{ 0.f, apexPoint.y - construct.coneHeight, 0.f };

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

        //++i on side count in order to skip first
        for (UINT16 i = 1; i <= construct.sideCount; i++)
        {
            const float currentAngle = i * pointAngles;

            //base radius is 0.5f
            //calc the object's position on a circle around the base's center
            const Maths::Vector3<float> position = baseCenterPosition + baseRightDir * construct.baseRadius * std::cos(currentAngle) + baseForwardDir * construct.baseRadius * std::sin(currentAngle);

            vertexData.push_back(position.x);
            vertexData.push_back(position.y);
            vertexData.push_back(position.z);

            indexes.push_back(0);
            indexes.push_back(i);
            indexes.push_back((i % construct.sideCount) + 1); //loop around when at sideCount
        }
        
        //*****************************************
        //THIS IS PULLED STRAIGHT FROM THE CONE.CPP
        //*****************************************

        //now need to add the hole and cyllinder for the actual arrow
        const float branchRadius = construct.baseRadius / BRANCH_DIVISOR;
        LOG_MSG("Branch Radius: {}", branchRadius); 
       
        const int cyllinderStart = construct.sideCount + 1;

        //skip the apex point
        const int currentSize = vertexData.size(); //loop adds to it
        for (UINT16 i = 3; i < currentSize; i += 3)
        {
            Maths::Vector3<float> currentPoint = Maths::Vector3<float>{ vertexData.at(i), vertexData.at(i + 1), vertexData.at(i + 2) };
            Maths::Vector3<float> targetDirection = currentPoint - baseCenterPosition;
            targetDirection.Normalize();

            const Maths::Vector3<float> adjustedPosition = baseCenterPosition + targetDirection * branchRadius;

            vertexData.push_back(adjustedPosition.x);
            vertexData.push_back(adjustedPosition.y);
            vertexData.push_back(adjustedPosition.z); 
        }

        //need to add indices in third loop
        //to ensure arll the cone's points are formed
        for (UINT16 i = 1; i <= construct.sideCount; i++)
        {
            const int outerCurrent = i;
            const int outerNext = (i % construct.sideCount) + 1;

            const int innerCurrent = construct.sideCount + i;
            const int innerNext = construct.sideCount + ((i % construct.sideCount) + 1);

            //first triangle of base section
            indexes.push_back(outerCurrent);
            indexes.push_back(outerNext);
            indexes.push_back(innerCurrent);

            //second triangle of base section
            indexes.push_back(innerCurrent);
            indexes.push_back(outerNext);
            indexes.push_back(innerNext);
        }

        //***********
        //BOTTOM STEM
        //*********** 

        for (UINT16 i = 0; i < construct.sideCount; i++)
        {
            const int vertexIndex = cyllinderStart + i;
            const int floatIndex = vertexIndex * 3;

            vertexData.push_back(vertexData.at(floatIndex)); //copy x from top of ring
            vertexData.push_back(vertexData.at(floatIndex + 1) - construct.stemHeight); //move the y down
            vertexData.push_back(vertexData.at(floatIndex + 2)); //copy z as well
        }

        //now just connect the top to the bottom
        for (UINT16 i = 0; i < construct.sideCount; i++)
        {
            const unsigned int topCurrent = cyllinderStart + i;
            const unsigned int botCurrent = cyllinderStart + construct.sideCount + i;
            const unsigned int topNext = (i == construct.sideCount - 1) ? cyllinderStart : topCurrent + 1;
            const unsigned int botNext = (i == construct.sideCount - 1) ? cyllinderStart + construct.sideCount : botCurrent + 1;
            
            //side quad triangle 1
            indexes.push_back(topCurrent);
            indexes.push_back(botCurrent);
            indexes.push_back(botNext);

            //side quad triangle 2
            indexes.push_back(botNext);
            indexes.push_back(topNext);
            indexes.push_back(topCurrent);
        }

        //***********
        //BOTTOM STEM
        //***********

        //**********
        //BOTTOM CAP
        //**********
        
        //add the bottom apex point
        vertexData.push_back(0.f);
        vertexData.push_back(apexPoint.y - construct.stemHeight);
        vertexData.push_back(0.f);

        const unsigned int bottomApex = cyllinderStart + construct.sideCount * 2;

        for (UINT16 i = 0; i < construct.sideCount; i++)
        {
            const unsigned int botCurrent = cyllinderStart + construct.sideCount + i;
            const unsigned int botNext = (i == construct.sideCount - 1) ? cyllinderStart + construct.sideCount : botCurrent + 1;

            indexes.push_back(botCurrent);
            indexes.push_back(botNext);
            indexes.push_back(bottomApex);
        }

        
        //**********
        //BOTTOM CAP
        //**********

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
        //12 count for the stem at bottom
        arrowMesh.indexCount = indexes.size();

        return arrowMesh;
    }
}
