#include "egpch.h"
#include "RendererAPI.h"

//ENGINE
#include "Core/Logger.h"
#include "Core/Application.h"

//VENDOR
#include "GL/GL.h"

namespace Engine::Renderer
{
	RenderAPI::RenderAPI(std::pair<unsigned int, unsigned int> viewportSize)
	{
		glViewport(0, 0, viewportSize.first, viewportSize.second);
		m_CurrentActiveCamera = Application::GetCamera();
	}

	RenderAPI::~RenderAPI()
	{
	}

	void RenderAPI::Render()
	{
		m_WorldRenderer.Render();
		m_DebugRenderer.Render();
		m_UIRenderer.Render();
	}

	void RenderAPI::Setup()
	{
		m_WorldRenderer.Setup();
		m_UIRenderer.Setup();
		m_DebugRenderer.Setup();
	}

	void RenderAPI::Clear()
	{
		//clear the my gl renderers
		glClearColor(.5f, .9f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//clear the debug renderer with imgui
	//	m_DebugRenderer.Clear();
	}

	std::function<void(int, int)> RenderAPI::Resize()
	{
		return [this](int width, int height)
			{
				//update the viewport
				glViewport(0, 0, width, height);

				//use the updated viewport to update the camera's projection
				m_CurrentActiveCamera->UpdateProjection(width, height);
			};
	}
}
