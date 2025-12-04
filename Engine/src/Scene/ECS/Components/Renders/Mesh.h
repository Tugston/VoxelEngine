#pragma once

//ENGN
#include "SharedResources/GenericResources/Mesh.h"
#include "SharedResources/GenericResources/Material.h"

namespace Engine::Scene::ECS::Components
{
	struct MeshComponent
	{
		std::shared_ptr<Utility::Mesh> mesh;
		Utility::Material material;
	};
}
