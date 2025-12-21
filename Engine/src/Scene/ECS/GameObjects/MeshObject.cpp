/*
* File: MeshObject.cpp
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
#include "MeshObject.h"

//ENGN
#include "SharedResources/GenericResources/Material.h"
#include "SharedResources/PrimitiveShapes/ThreeDimensions/Cone.h"
#include "SharedResources/PrimitiveShapes/ThreeDimensions/Cyllinder.h"

#define SETUP_MATERIAL()\
meshComp->material.shader = new Utility::Shader("TestShader");\
if(Utility::Shader* matShader = meshComp->material.shader)\
{\
	matShader->Create();\
	matShader->SetUniformVec3("uColor", DEFAULT_COLOR);\
} else {\
	LOG_WARN("<MeshObject.cpp> Material Setup Failed on Object!");\
}\

namespace Engine::Scene::ECS
{
	static Utility::Mesh GetMeshType(MeshType type, std::optional<UINT16> sideCount)
	{
		switch (type)
		{
		case Engine::Scene::ECS::MeshType::CUBE_MESH:

		case Engine::Scene::ECS::MeshType::CONE_MESH:

			if (sideCount.has_value())
				return Utility::CreateCone(sideCount.value());
			else
				return Utility::CreateCone();

		case Engine::Scene::ECS::MeshType::CYLINDER_MESH:

			if (sideCount.has_value())
				return Utility::CreateCyllinder(sideCount.value());
			else
				return Utility::CreateCyllinder();
		
		case Engine::Scene::ECS::MeshType::SPHERE_MESH:
			break;
		default:
			break;
		}
	}

	MeshObject::MeshObject(std::shared_ptr<Scene> scene, MeshType type, std::optional<UINT16> sideCount):
		GameObject3D(scene)
	{
		AddComponent<Components::MeshComponent>();
		Components::MeshComponent* meshComp = GetComponent<Components::MeshComponent>();

		if (!meshComp)
		{
			LOG_WARN("<MeshObject.cpp> (MeshObject) Mesh Component Invalid for Unknown Reason!");
			return;
		}

		meshComp->mesh = std::make_shared<Utility::Mesh>(GetMeshType(type, sideCount));
	
		SETUP_MATERIAL();
	}

	MeshObject::MeshObject(std::shared_ptr<Scene> scene, std::string_view fileName):
		GameObject3D(scene)
	{
		//wip, need to actually make the mesh imported and everything first, which will come later
	}

	MeshObject::MeshObject(std::shared_ptr<Scene> scene, Components::TransformComponent3D transform, MeshType type, std::optional<UINT16> sideCount):
		GameObject3D(scene, transform)
	{
		AddComponent<Components::MeshComponent>();
		Components::MeshComponent* meshComp = GetComponent<Components::MeshComponent>();

		if (!meshComp)
		{
			LOG_WARN("<MeshObject.cpp> (MeshObject) Mesh Component Invalid for Unknown Reason!");
			return;
		}

		meshComp->mesh = std::make_shared<Utility::Mesh>(GetMeshType(type, sideCount));

		SETUP_MATERIAL();
	}

	MeshObject::MeshObject(std::shared_ptr<Scene> scene, Components::TransformComponent3D transform, std::string_view fileName):
		GameObject3D(scene, transform)
	{
		//wip, need to actually make the mesh imported and everything first, which will come later
	}
}

