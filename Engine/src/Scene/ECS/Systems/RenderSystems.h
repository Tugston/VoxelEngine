#pragma once

namespace Engine::Renderer
{
	class Renderer;
}

namespace Engine::Scene
{
	class Scene;
}

namespace Engine::Scene::ECS::Systems
{
	void SysRenderOpaqueMesh(std::shared_ptr<Scene> scene, Renderer::Renderer* renderer);
}

