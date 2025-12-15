/*
* File: Cyllinder.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-14 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Cyllinder.h"

//ENGN
#include "Renderer/Core/RenderCore.h"
#include "Core/Logger.h"
#include "Core/Maths/Math.h"

namespace Engine::Utility
{
	Mesh CreateCyllinder(UINT16 sideCount)
	{
		Mesh cyllinderMesh;

		if (sideCount < 4)
		{
			LOG_MSG("<Cyllinder.cpp> (CreateCyllinder) Cyllinder has insuficient amount of sides, increasing to 5");
			sideCount = 5;
		}

		std::vector<float> vertexData = {
			 0.f,  0.5f,  0.f, //top center
		};

		const float radius = 0.5f;

		Maths::Vector2<float> XYCoords;

		//calculate edges of a circle, since both sides are just two circles
		for (int i = 1; i <= sideCount; i++)
		{
			const float baseAngle = 2 * EG_PI_FLOAT * i / sideCount;
			XYCoords.x = radius * std::cos(baseAngle);
			XYCoords.y = radius * std::sin(baseAngle);

			//the circles are calculated on a 2d plane, so z is the y
			vertexData.push_back(XYCoords.x);
			vertexData.push_back(0.5f);
			vertexData.push_back(XYCoords.y);

			//now do bottom
			vertexData.push_back(XYCoords.x);
			vertexData.push_back(-0.5f);
			vertexData.push_back(XYCoords.y);
		}

		//add the bottom center
		vertexData.push_back(0.f);
		vertexData.push_back(-0.5f);
		vertexData.push_back(0.f);

		std::vector<unsigned int> indexes;

		//unsigned int topCurrent = 1;
		//unsigned int botCurrent = 2;
		//unsigned int topNext = 3;
		//unsigned int botNext = 4;

		for (int i = 0; i < sideCount; i++)
		{
			//there is probably a way to do this pure mathematically
			//but creating mesh is just a one off thing, so if checks dont matter too much
			const unsigned int topCurrent = 1 + i * 2;
			const unsigned int botCurrent = 2 + i * 2;
			const unsigned int topNext = (i == sideCount - 1) ? 1 : topCurrent + 2;
			const unsigned int botNext = (i == sideCount - 1) ? 2 : botCurrent + 2;
		
			//top triangle
			indexes.push_back(0);
			indexes.push_back(topCurrent);
			indexes.push_back(topNext);

			//side quad triangle 1
			indexes.push_back(topCurrent);
			indexes.push_back(botCurrent);
			indexes.push_back(botNext);

			//side quad triangle 2
			indexes.push_back(botNext);
			indexes.push_back(topNext);
			indexes.push_back(topCurrent);

			//bot triangle
			indexes.push_back(sideCount * 2 + 1); //bottom center vertex
			indexes.push_back(botNext);
			indexes.push_back(botCurrent);			
		}

		//now setup the mesh
		cyllinderMesh.Create();

		cyllinderMesh.vao.Bind();

		cyllinderMesh.vbo.Bind();
		cyllinderMesh.vbo.BufferData(vertexData, GL_STATIC_DRAW);

		cyllinderMesh.ebo.Bind();
		cyllinderMesh.ebo.BufferData(indexes, GL_STATIC_DRAW);

		Renderer::AttribData aData = { Renderer::ShaderDataType::Float3 };
		cyllinderMesh.vao.SetAttribData(0, aData, cyllinderMesh.vbo, cyllinderMesh.ebo);

		cyllinderMesh.vao.UnBind();
		cyllinderMesh.vbo.UnBind();
		cyllinderMesh.ebo.UnBind();

		//top and bottom have 3 vertices and each side is a quad 
		cyllinderMesh.indexCount = 12 * sideCount;

		return cyllinderMesh;
	}
}