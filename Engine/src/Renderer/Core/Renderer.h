/*
* File: Renderer.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-14-03 (yyyy/mm/dd)
*
* Description: Pipline that handles every single vertex, render pass, lighting calculation, or whatever required to draw the scene
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include <queue>
#include <functional>
#include <variant>

//ENGINE
#include "Core/Core.h"
#include "RenderObjects.h"

namespace Engine::Camera
{
	class EditorCamera;
}

namespace Engine::Utility
{
	class Texture2D;
}

namespace Engine::Renderer
{
	class FrameBuffer;
	using ViewSize = std::pair<unsigned int, unsigned int>;

	//fill packets with all possible types that can be in each category of queues
	using OpaquePackets = std::variant<MeshObject, InstanceMeshObject>;

	class Renderer
	{
	public:
		enum class RenderTarget: UINT8
		{
			Window,
			FrameBufferTexture
		};

		Renderer(ViewSize viewportSize);
		Renderer(ViewSize viewportSize, RenderTarget target);
		~Renderer();
		
		void BeginRender(Engine::Camera::EditorCamera* camera);
		void EndRender();
	
		//this works with the RenderObject function so any renderObject can be passed as the api
		void SubmitObject(RenderObject& renderObject);

		std::function<void(int, int)> Resize(Camera::EditorCamera* camera = nullptr); //utilized for application window resizing callback

		//EDITOR SPECIFICS
		unsigned int GetRenderTexture() { return m_TextureColorBuffer->GetID(); }

	private:
		void SetupRenderTexture();

		void ClearScreen();
		void ClearQueues(); //there shouldnt be any data left over from previous frame, but just in case

		//Object Registering
		void RegisterOpaqueObject(OpaquePackets mesh);

	private:
		RenderTarget m_RenderTarget;	

		//render queues
		std::queue<OpaquePackets> m_OpaqueSceneObjects;

		friend struct MeshObject;
		friend struct InstanceMeshObject;

		//EXTRA DATA THAT SHOULD NOT BE IN THE GAME BUT RENDERER NEEDS IT
		FrameBuffer* m_FrameBuffer;
		Utility::Texture2D* m_TextureColorBuffer;
	};
}
