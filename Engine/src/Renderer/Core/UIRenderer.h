#pragma once

#include "Renderer/Core/Renderer.h"

namespace Engine::Renderer
{
	class UIRenderer : public Renderer
	{
	public:
		UIRenderer();
		~UIRenderer();

		void Setup();
		virtual void Render(RenderTarget target) override;
		
	};
}
