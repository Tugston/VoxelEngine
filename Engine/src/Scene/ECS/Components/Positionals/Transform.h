#pragma once
#include "./Core/Maths/Math.h"

//not using glm, because I want my engine's api to be seperated from the library
//everything will be converted internally
//plus it gives me more control, when I want to add some bounds restrictions later (ie: Rotation can only go from 0 - 360)

//temporarily setting rotation to a Vector2, but want to switch to quaternions once I get it all setup and working

namespace Engine::Scene::ECS::Components
{
	struct TransformComponent2D
	{
		Maths::Vector2<float> location;
		//Maths::Rotator2<float> rotation;
		Maths::Vector2<float> rotation;
		Maths::Vector2<float> scale;
	};

	struct TransformComponent3D
	{
		Maths::Vector3<float> location;
		//Maths::Rotator3<float> rotation;
		Maths::Vector3<float> rotation;
		Maths::Vector3<float> scale;
	};
}
