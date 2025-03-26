#pragma once

//STND
#include <utility>
#include <functional>

//ENGINE
#include "Core/Core.h"
#include "Renderer/Core/UIRenderer.h"
#include "Renderer/Core/SceneRenderer.h"
#include "Renderer/Core/DebugRenderer.h"
#include "Renderer/Core/RenderData.h"

//helper class that will sort where everything needs to be rendererd

namespace Engine::Renderer
{
	class RenderAPI
	{
	public:
		RenderAPI(std::pair<unsigned int, unsigned int> viewportSize);
		~RenderAPI();

		//test code, entt does not exist yet
		void Render();
		void Setup(); //temporary function for setting stuff up

		void Clear();
		
		//opengl resize event for the window
		std::function<void(int, int)> Resize();
	private:
		UIRenderer m_UIRenderer;
		SceneRenderer m_WorldRenderer;
		DebugRenderer m_DebugRenderer;
	};
}
