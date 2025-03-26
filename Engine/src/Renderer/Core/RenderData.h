#pragma once

//STND
#include <vector>

namespace Engine::Renderer
{
	struct SceneRenderData
	{
	public:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
	};

	struct UIRenderData
	{

	};
}
