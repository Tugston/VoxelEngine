#pragma once

//STND
#include <utility>
#include <functional>

//ENGINE
#include "Core/Core.h"
#include "Renderer/Core/2DRenderer.h"
#include "Renderer/Core/3DRenderer.h"

//helper class that will sort where everything needs to be rendererd

namespace Engine::Renderer
{
	class ENGINE_API RenderAPI
	{
	public:
		RenderAPI(std::pair<unsigned int, unsigned int> viewportSize);
		~RenderAPI();

		//test code, entt does not exist yet
		void Render() { m_WorldRenderer.Render(); };
		void Setup() { m_WorldRenderer.Setup(); };

		void Clear();
		
		//opengl resize event for the window
		std::function<void(int, int)> Resize();
	private:
		Renderer2D m_UIRenderer;
		Renderer3D m_WorldRenderer;
	};
}
