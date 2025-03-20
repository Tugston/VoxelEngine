#pragma once

//STND
#include <vector>

namespace Engine::Renderer
{
	struct RenderData
	{
	public:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
	};

}
