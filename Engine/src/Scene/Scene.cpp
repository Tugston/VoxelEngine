#include "egpch.h"
#include "Scene.h"

//ENGINE
#include "API/GameLayers.h"
#include "Core/Logger.h"


namespace Engine::Scene
{

	Scene::Scene()
	{
		SetupScene();
	}

	Scene::Scene(const std::string_view& name) : m_Name(name)
	{
		SetupScene();
	}

	Scene::~Scene()
	{
	}

	void Scene::CollectRenderData()
	{

		for (size_t i = 0; i < LayerStack::GetLayers().size(); i++)
		{
			LayerStack::GetLayers().at(i)->GetDrawData();
		}
	}

	void Scene::AddUI() const
	{
		//check if the layer exists already, if not add it
		//4 is the game ui layer id
		if (!(LayerStack::CheckLayerExists(4)))
		{
			LayerStack::PushUILayer(new API::UILayer);
		}
	}

	void Scene::RemoveUI() const
	{
		REMOVE_UI;
	}

	void Scene::SetupScene()
	{
		Logger::LogMessage(Logger::LogType::Message, "New Scene Created!");
		
		//layer setup
		LayerStack::Clear(); //clear the layer stack to refresh for the new scene
		LayerStack::PushSpaceLayer(new API::WorldLayer);
		LayerStack::PushUILayer(new WorldLayer);
		LayerStack::PushSpaceLayer(new API::UILayer);
		LayerStack::PushUILayer(new UILayer);
	}

}
