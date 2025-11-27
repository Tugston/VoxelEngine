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

namespace Engine::Renderer
{	
	using ViewSize = std::pair<unsigned int, unsigned int>;

	//fill packets with all possible types that can be in each category of queues
	using OpaquePackets = std::variant<const MeshObject*, const InstanceMeshObject*>;

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
		void SubmitObject(std::shared_ptr<RenderObject> renderObject);

		std::function<void(int, int)> Resize(Camera::EditorCamera* camera = nullptr); //utilized for application window resizing callback

	private:
		void ClearScreen();
		void ClearQueues(); //there shouldnt be any data left over from previous frame, but just in case

		//Object Registering
		void RegisterOpaqueObject(std::shared_ptr<OpaquePackets> mesh);

	private:
		RenderTarget m_RenderTarget;	

		//render queues
		std::queue<std::weak_ptr<OpaquePackets>> m_OpaqueSceneObjects;

		friend struct MeshObject;
		friend struct InstanceMeshObject;
	};
}
