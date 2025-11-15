#pragma once
#include "Core/Core.h"
#include "Scene/ECS/Registry.h"

//this is purely an abstraction class that allows the engine api to only use GameObjects for everything like a normal engine
//masks away the underlying ecs

namespace engine
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

	private:
		
	};
}
