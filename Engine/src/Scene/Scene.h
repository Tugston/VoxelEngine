#pragma once

//VENDOR
#include "entt/entt.hpp"

//ENGINE
#include "Core/Core.h"
#include "Renderer/Core/RenderData.h"
#include "Core/Layers/LayerStack.h"
#include "Core/Layers/EngineLayers.h"

//STND
#include <string>
#include <string_view>

namespace Engine::Scene
{
	class Scene
	{
	public:
		Scene();
		Scene(const std::string_view& name);
		~Scene();

		void CollectRenderData(); //collects all the rendering components data

		void AddUI() const;
		void RemoveUI() const;

		//DEBUG ONLY
		//may as well make them header only as well
	#if defined(EG_DEBUG) || (APP_DEBUG)
		inline void EnableFullDebugView() const { LayerStack::PushSpaceLayer(new WorldLayer); LayerStack::PushUILayer(new UILayer); };
		inline void EnableDebugUI() const { LayerStack::PushUILayer(new UILayer); };
		inline void EnableDebugGeometry() const { LayerStack::PushSpaceLayer(new WorldLayer); };
		inline void DisableFullDebugView() const { REMOVE_ENGINE_UI_LAYER; REMOVE_ENGINE_DEBUG_LAYER; };
		inline void DisableDebugUI() const { REMOVE_ENGINE_UI_LAYER; };
		inline void DisableDebugGeometry() const { REMOVE_ENGINE_DEBUG_LAYER; };
	#endif

	private:
		void SetupScene();

	private:
		std::string m_Name = "Example Scene";
	//	entt::registry m_Registry;
	};

}
