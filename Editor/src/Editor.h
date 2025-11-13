#pragma once
#include <Engine.h>
#include <Core/EntryPoint.h>

class GLFWWindow;

namespace Editor
{
	class EditorApplication : public Engine::Application
	{
	public:
		EditorApplication();
		~EditorApplication();

		virtual void Start() override;
		virtual void Tick() override;

		void Draw();

	private:

	};
}
