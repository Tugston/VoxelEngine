#pragma once

//ENGINE
#include "Core/Core.h"
#include "Core/Layers/LayerStack.h"
#include "Core/Layers/EngineLayers.h"
#include "./ECS/Registry.h"

//STND
#include <string>
#include <string_view>

namespace Engine::Scene
{
	class Scene
	{
	public:
		Scene();
		Scene(std::string_view name);
		~Scene();

		
		ECS::EntityID RegisterObject();

		template<typename t, typename... Args>
		t* RegisterComponent(ECS::EntityID id, Args&&... args)
		{
			return m_Registry->AddComponent<t>(id, std::forward<Args>(args)...);
		}

		template<typename t>
		void DestroyComponent(ECS::EntityID id)
		{
			m_Registry->RemoveComponent<t>(id);
		}

		template<typename t>
		t* GetObjectComponent(ECS::EntityID id)
		{
			return m_Registry->GetComponent<t>(id);
		}

		//collects all objects with renderable ecs components
		void CollectRenderData(); 

		void AddUI() const;
		void RemoveUI() const;

		//DEBUG ONLY
		//may as well make them header only as well
	#if defined(EG_DEBUG) || (APP_DEBUG)
		inline void EnableFullDebugView() const { LayerStack::PushWorldLayer(new EngineWorldLayer); LayerStack::PushUILayer(new EngineUILayer); };
		inline void EnableDebugUI() const { LayerStack::PushUILayer(new EngineUILayer); };
		inline void EnableDebugGeometry() const { LayerStack::PushWorldLayer(new EngineWorldLayer); };
		inline void DisableFullDebugView() const { REMOVE_ENGINE_UI_LAYER; REMOVE_ENGINE_DEBUG_LAYER; };
		inline void DisableDebugUI() const { REMOVE_ENGINE_UI_LAYER; };
		inline void DisableDebugGeometry() const { REMOVE_ENGINE_DEBUG_LAYER; };
	#endif

	private:
		void SetupScene();

	private:
		std::string m_Name = "Example Scene";
		std::shared_ptr<ECS::Registry> m_Registry;
	};

}
