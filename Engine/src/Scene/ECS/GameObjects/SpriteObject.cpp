/*
* File: SpriteObject.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-20 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "SpriteObject.h"

//ENGN
#include "Renderer/Core/RenderCore.h"
#include "SharedResources/GenericResources/Material.h"
#include "SharedResources/PrimitiveShapes/TwoDimensions/Quad.h"
#include "SharedResources/PrimitiveShapes/TwoDimensions/Triangle.h"

//all of the constructors do this exact same stuff.
//was debating setting up a macro for adding the sprite component as well
#define SETUP_MATERIAL()\
spriteComp->material.shader = new Utility::Shader("TestShader");\
if(Utility::Shader* spriteShader = spriteComp->material.shader)\
{\
	spriteShader->Create();\
	spriteShader->SetUniformVec3("uColor", DEFAULT_COLOR);\
} else {\
	LOG_WARN("<SpriteObject.cpp> Material Setup Failed on Object!");\
}

namespace Engine::Scene::ECS
{
	static Utility::Mesh GetMeshType(SpriteType type)
	{
		switch (type)
		{
		case SpriteType::QUAD_MESH:
			return Utility::CreateQuad();
		case SpriteType::TRIANGLE_MESH:
			return Utility::CreateTriangle();
		default:
			return Utility::CreateQuad(); //quads are probably safer in case of fail
		}
	}

	//****************
	//Sprite Object 2D
	//****************

	SpriteObject2D::SpriteObject2D(std::shared_ptr<Scene> scene, SpriteType type): GameObject2D(scene)
	{
		AddComponent<Components::SpriteComponent>();
		Components::SpriteComponent* spriteComp = GetComponent<Components::SpriteComponent>();

		if (!spriteComp)
		{
			LOG_WARN("<SpriteObject.cpp> (SpriteObject2D) Sprite Component Invalid for Unknown Reason!");
			return;
		}

		spriteComp->planeMesh = std::make_shared<Utility::Mesh>(GetMeshType(type));

		SETUP_MATERIAL();
	}


	SpriteObject2D::SpriteObject2D(std::shared_ptr<Scene> scene, Components::TransformComponent2D transform, SpriteType type):
		GameObject2D(scene, transform)
	{
		AddComponent<Components::SpriteComponent>();
		Components::SpriteComponent* spriteComp = GetComponent<Components::SpriteComponent>();

		if (!spriteComp)
		{
			LOG_WARN("<SpriteObject.cpp> (SpriteObject2D) Sprite Component Invalid for Unknown Reason!");
			return;
		}

		spriteComp->planeMesh = std::make_shared<Utility::Mesh>(GetMeshType(type));

		SETUP_MATERIAL();
	}

	//****************
	//Sprite Object 2D
	//****************

	//****************
	//Sprite Object 3D
	//****************

	SpriteObject3D::SpriteObject3D(std::shared_ptr<Scene> scene, SpriteType type): GameObject3D(scene)
	{
		AddComponent<Components::SpriteComponent>();
		Components::SpriteComponent* spriteComp = GetComponent<Components::SpriteComponent>();

		if (!spriteComp)
		{
			LOG_WARN("<SpriteObject.cpp> (SpriteObject3D) Sprite Component Invalid for Unknown Reason!");
			return;
		}

		spriteComp->planeMesh = std::make_shared<Utility::Mesh>(GetMeshType(type));

		SETUP_MATERIAL();
	}

	SpriteObject3D::SpriteObject3D(std::shared_ptr<Scene> scene, Components::TransformComponent3D transform, SpriteType type):
		GameObject3D(scene, transform)
	{
		AddComponent<Components::SpriteComponent>();
		Components::SpriteComponent* spriteComp = GetComponent<Components::SpriteComponent>();
		
		if (!spriteComp)
		{
			LOG_WARN("<SpriteObject.cpp> (SpriteObject3D) Sprite Component Invalid for Unknow Reason!");
			return;
		}
		
		spriteComp->planeMesh = std::make_shared<Utility::Mesh>(GetMeshType(type));

		SETUP_MATERIAL();
	}

	//****************
	//Sprite Object 3D
	//****************
}