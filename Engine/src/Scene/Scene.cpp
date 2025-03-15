#include "Scene.h"

#include "Core/Layers/LayerStack.h"

Engine::Scene::Scene()
{
}

Engine::Scene::~Scene()
{
}

void Engine::Scene::Render()
{
	for (size_t i = 0; i < LayerStack::GetLayers().size(); i++)
	{
		LayerStack::GetLayers().at(i)->Draw();
	}
}

void Engine::Scene::EnableFullDebugView() const
{

}
