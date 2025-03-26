#include "egpch.h"
#include "DebugRenderer.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"
#include "Core/Debug/DebugUI.h"

namespace Engine::Renderer
{
	DebugRenderer::DebugRenderer()
	{

	}

	DebugRenderer::~DebugRenderer()
	{

	}

	void DebugRenderer::Setup()
	{

	}

	void DebugRenderer::Render()
	{
		Debug::UI::Render();
	}

	void DebugRenderer::Clear()
	{
		Debug::UI::Refresh();
	}
}
