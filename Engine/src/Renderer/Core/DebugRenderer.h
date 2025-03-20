#pragma once

//ENGINE
#include "Renderer/Core/Renderer.h"


namespace Engine::Renderer
{
	class DebugRenderer : public Renderer
	{
	public:
		DebugRenderer();
		~DebugRenderer();

		virtual void Render();

	};
}
