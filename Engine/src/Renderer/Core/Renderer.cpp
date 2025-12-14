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
#include "Renderer/Architecture/Buffer.h"
#include "Core/Cameras/PerspectiveCamera.h"
#include "Core/Cameras/OrthographicCamera.h"
#include "SharedResources/GenericResources/Texture.h"

namespace Engine::Renderer
{
	//defaults to window, so no need to setup anything
	Renderer::Renderer(ViewSize viewportSize):
		m_RenderTarget(RenderTarget::Window), m_FrameBuffer(nullptr), m_TextureColorBuffer(nullptr)
	{
		glViewport(0, 0, viewportSize.first, viewportSize.second);
		glEnable(GL_DEPTH_TEST);

		if (glewInit() != GLEW_OK)
		{
			LOG_CRIT("<Renderer.cpp> Glew Not Initialized");
			EG_ASSERT(false);
		}
	};

	Renderer::Renderer(ViewSize viewportSize, RenderTarget target):
		m_RenderTarget(target), m_FrameBuffer(nullptr), m_TextureColorBuffer(nullptr)
	{
		glViewport(0, 0, viewportSize.first, viewportSize.second);
		glEnable(GL_DEPTH_TEST);

		if (glewInit() != GLEW_OK)
		{
			LOG_CRIT("<Renderer.cpp> Glew Not Initialized!");
			EG_ASSERT(false);
		}

		if (target == RenderTarget::FrameBufferTexture)
			SetupRenderTexture();

	}

	Renderer::~Renderer()
	{
		delete m_FrameBuffer;
		delete m_TextureColorBuffer;
	}

	void Renderer::BeginRender(Camera::EditorCamera* camera)
	{
		if (m_RenderTarget == RenderTarget::FrameBufferTexture && m_FrameBuffer)
			m_FrameBuffer->Bind();

		ClearScreen();
		ClearQueues();

		if (m_RenderTarget == RenderTarget::FrameBufferTexture && m_FrameBuffer)
			m_FrameBuffer->UnBind();
	}

	void Renderer::EndRender()
	{
		//prepare the texture for opengl to render to
		if (m_RenderTarget == RenderTarget::FrameBufferTexture && m_FrameBuffer)
			m_FrameBuffer->Bind();

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

		if (m_RenderTarget == RenderTarget::FrameBufferTexture && m_FrameBuffer)
			m_FrameBuffer->UnBind();
	}

	void Renderer::SetupRenderTexture()
	{
		m_FrameBuffer = new FrameBuffer;
		m_FrameBuffer->Create();

		m_TextureColorBuffer = new Utility::Texture2D;
		m_TextureColorBuffer->CreateEmpty(Utility::TextureDefaultParams{ "",1280, 720 });
		m_TextureColorBuffer->SetFilter(GL_LINEAR, GL_LINEAR);

		m_FrameBuffer->Bind();
		m_TextureColorBuffer->Bind();

		m_FrameBuffer->BufferTexture2D(GL_COLOR_ATTACHMENT0, m_TextureColorBuffer->GetID(), 0);

		//depth buffer setup is connected through gpu
		RenderBuffer* depthBuffer = new RenderBuffer;
		depthBuffer->Create();
		depthBuffer->Bind();
		depthBuffer->RenderBufferStorage(GL_DEPTH24_STENCIL8, 1280, 720);

		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer->GetID()));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERR("<Renderer.cpp> (Construct) Render Buffer Not Setup!");
		}
	}

	void Renderer::ClearScreen()
	{
		glClearColor(.5f, .9f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
