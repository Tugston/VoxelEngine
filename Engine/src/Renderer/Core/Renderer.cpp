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
			Logger::LogMessage(Logger::LogType::Critical, "<Renderer.h> Glew Did Not Initialize");
			EG_ASSERT(false);
		}
	};
}
