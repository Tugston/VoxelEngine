#pragma once

//ENGN
#include "SharedResources/GenericResources/Mesh.h"
#include "SharedResources/GenericResources/Material.h"


namespace Engine::Scene::ECS::Components
{
	struct Sprite
	{
		Utility::Mesh planeMesh;
		Utility::Material material;
	};
}
