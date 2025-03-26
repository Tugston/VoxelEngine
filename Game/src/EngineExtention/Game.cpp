
//this class serves as a bridge between the engine and game objects, scenes, etc
//ideally the game would only make game objects, but I want the game to have a little more control
//may change in the future, but this just makes sense to me currently

//ENGINE
#include<Engine.h>
#include<Core/EntryPoint.h> //entry point

namespace VoxelGame
{
	class Game : public Application
	{
	public:
		Game() : Application()
		{
			m_Shader = new Renderer::Shader("TestShader");
		}

		~Game() override
		{

		}

		virtual void Start() override
		{
			Application::Start();

			m_Shader->Create();
			Tick();
		}

		virtual void Tick() override
		{
			while (m_Running)
			{
				//ALL TEST STUFF
				Debug::UI::Refresh();
				Debug::UI::BeginUI("Engine Menu");
				Debug::UI::AddElement<std::string, glm::vec3>(Debug::ElementType::ColorEdit3, "Color", &m_Color);
				Debug::UI::EndUI();


				m_Shader->Use();

				m_Shader->SetUniformVec3("uColor", m_Color);
				//***
				Application::Tick();
			}
		}

	private:
		glm::vec3 m_Color = glm::vec3(0);
		Renderer::Shader* m_Shader;
	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


