#include "egpch.h"
#include "Renderer.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"

namespace Engine::Renderer
{
	Renderer::Renderer()
	{
		if (glewInit() != GLEW_OK)
		{
			LOG_CRIT("<Renderer.cpp> Glew Did Not Initialize");
			EG_ASSERT(false);
		}
	};
}
