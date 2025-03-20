#include "egpch.h"
#include "Scene.h"

//ENGINE
#include "API/GameLayers.h"
#include "Core/Logger.h"


namespace Engine::Scene
{

	Scene::Scene()
	{

		Logger::LogMessage(Logger::LogType::Message, "New Scene Created!");
		
		//layer setup
		LayerStack::Clear(); //clear the layer stack to refresh for the new scene
		LayerStack::PushSpaceLayer(new API::WorldLayer);
		LayerStack::PushUILayer(new WorldLayer);
		LayerStack::PushSpaceLayer(new API::UILayer);
		LayerStack::PushUILayer(new UILayer);
	}

	Scene::Scene(const std::string_view& name) : m_Name(name)
	{
		Scene();
	}

	Scene::~Scene()
	{
	}

	Renderer::RenderData Scene::CollectRenderData()
	{
		Renderer::RenderData test;

		for (size_t i = 0; i < LayerStack::GetLayers().size(); i++)
		{
			LayerStack::GetLayers().at(i)->GetDrawData();
		}

		return test;
	}

	void Scene::AddUI() const
	{
		//check if the layer exists already, if not add it
		if (!(LayerStack::CheckLayerExists(4)))
		{
			LayerStack::PushUILayer(new API::UILayer);
		}
	}

	void Scene::RemoveUI() const
	{
		REMOVE_UI;
	}

}
