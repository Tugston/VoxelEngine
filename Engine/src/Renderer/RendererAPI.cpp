#include "egpch.h"
#include "RendererAPI.h"

#include "Core/Logger.h"

//VENDOR
#include "GL/GL.h"

Engine::Renderer::RenderAPI::RenderAPI(std::pair<unsigned int, unsigned int> viewportSize)
{
	glViewport(0, 0, viewportSize.first, viewportSize.second);
}

Engine::Renderer::RenderAPI::~RenderAPI()
{
}

void Engine::Renderer::RenderAPI::Clear()
{
	glClearColor(.5f, .9f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

std::function<void(int, int)> Engine::Renderer::RenderAPI::Resize()
{
	return [](int width, int height)
		{
			//test logging
			//Logger::LogMessage(Logger::LogType::Message, "(Window Resize Event) X: {}, Y: {}", width, height);
			glViewport(0, 0, width, height);
		};
}
