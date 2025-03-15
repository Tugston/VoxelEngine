#pragma once

#include "Renderer/Core/Renderer.h"

namespace Engine::Renderer
{
	class ENGINE_API Renderer2D : public Renderer
	{
	public:
		Renderer2D();
		~Renderer2D();

		virtual void Render();
	};
}
