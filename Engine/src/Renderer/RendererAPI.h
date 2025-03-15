#pragma once

//ENGINE
#include "Core/Core.h"
#include "Renderer/Core/RenderCore.h"
#include "Renderer/Core/2DRenderer.h"
#include "Renderer/Core/3DRenderer.h"

//helper class that will sort where everything needs to be rendererd

namespace Engine::Renderer
{
	class ENGINE_API RenderAPI
	{
	public:
		RenderAPI();
		~RenderAPI();

		//test code, entt does not exist yet
		void Render() { m_WorldRenderer.Render(); };



	private:
		Renderer2D m_UIRenderer;
		Renderer3D m_WorldRenderer;
	};
}
