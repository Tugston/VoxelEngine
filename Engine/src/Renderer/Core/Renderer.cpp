/*
* File: Renderer.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-14-03 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Renderer.h"

//ENGINE
#include "Renderer/Core/RenderCore.h"
#include "Core/Cameras/PerspectiveCamera.h"
#include "Core/Cameras/OrthographicCamera.h"

namespace Engine::Renderer
{
	Renderer::Renderer(ViewSize viewportSize):
		m_RenderTarget(RenderTarget::Window)
	{
		glViewport(0, 0, viewportSize.first, viewportSize.second);

		if (glewInit() != GLEW_OK)
		{
			LOG_CRIT("<Renderer.cpp> Glew Not Initialized");
			EG_ASSERT(false);
		}
	};

	Renderer::Renderer(ViewSize viewportSize, RenderTarget target):
		m_RenderTarget(target)
	{
		glViewport(0, 0, viewportSize.first, viewportSize.second);

		if (glewInit() != GLEW_OK)
		{
			LOG_CRIT("<Renderer.cpp> Glew Not Initialized!");
			EG_ASSERT(false);
		}
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::BeginRender(Camera::EditorCamera* camera)
	{
		ClearScreen();
		ClearQueues();
	}

	void Renderer::EndRender()
	{
		while (!m_OpaqueSceneObjects.empty())
		{
			OpaquePackets* packet = &m_OpaqueSceneObjects.front();
			//m_OpaqueSceneObjects.pop();

			if (packet == nullptr)
			{
				m_OpaqueSceneObjects.pop();
				continue;
			}

			std::visit(
				[](const auto arg)
				{
					using t = std::decay_t<decltype(arg)>;

					if constexpr (std::is_same_v<t, MeshObject>)
					{
						arg.Render();
					}

				}
			, *packet);

			m_OpaqueSceneObjects.pop();
		}
	}

	void Renderer::ClearScreen()
	{
		glClearColor(.5f, .9f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ClearQueues()
	{
		auto clear = [this](auto queueToClear)
			{
				while (!queueToClear.empty())
					queueToClear.pop();
			};

		clear(m_OpaqueSceneObjects);
	}

	void Renderer::SubmitObject(RenderObject& renderObject)
	{
		renderObject.SubmitToRender(this);
	}

	std::function<void(int, int)> Renderer::Resize(Camera::EditorCamera* camera)
	{
		return [=](int width, int height)
			{
				glViewport(0, 0, width, height);

				if (camera)
					camera->UpdateProjection(width, height);
			};
	}

	//*************
	//REGISTER DUMP
	//*************

	void Renderer::RegisterOpaqueObject(OpaquePackets mesh)
	{
		m_OpaqueSceneObjects.push(mesh);
	}

	//*************
	//REGISTER DUMP
	//*************
}
