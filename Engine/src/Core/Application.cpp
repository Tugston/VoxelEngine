#include "egpch.h"
#include "Application.h"

//ENGINE
#include "Core/Logger.h"
#include "Core/Layers/LayerStack.h"


//this cpp file is a mess, and will always be, using the find tool (ctrl-f) is advised

namespace Engine
{
	//instantiate static reference
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Window("Voxel Game"), m_CurrentScene(nullptr)
	{
		s_Instance = this;
		srand(time(NULL));
		InitializeEngineRootSystems();

		m_Camera = std::make_shared<Camera::PerspectiveCamera>(glm::vec3(0.f, 0.f, 0.f));
		m_Renderer = std::make_unique<Renderer::Renderer>(m_Window.GetBufferSize());
	}

	Application::~Application()
	{
		glfwTerminate();
		LayerStack::Destroy();
		Logger::LogMessage(Logger::LogType::Critical, "Application Stopped!");
	}

	void Application::Start()
	{
		Logger::LogMessage(Logger::LogType::Warning, "Started!");

		m_Window.SetFrameSize(m_Renderer->Resize(m_Camera.get())); //send the resize function to the window for resize callback


		//create a level for the engine to automatically use
		//can obviously be overwrote in the game app
		CreateLevel("Test Level");
	}

	void Application::Tick()
	{
		CalculateDeltaTime();
		ProcessInput();
		InputSystem::MouseIdleDetection(m_DeltaTime);

		m_Window.PollEvents();
		Draw(GetDeltaTime());
	}

	void Application::CreateLevel(std::string_view levelName)
	{
		if (m_CurrentScene)
			m_CurrentScene.reset();

		m_CurrentScene = std::make_unique<Scene::Scene>(Scene::Scene(levelName));
	}

	//need to somehow save scenes and everything else, this is on the back burner for a while
	//just want to get the level structure setup so I can contain everything
	void Application::LoadLevel(std::string_view levelName)
	{
	}

	void Application::Draw(float deltaTime)
	{
		m_Renderer->BeginRender(m_Camera.get());

		m_Renderer->EndRender();
		m_CurrentScene->CollectRenderData();
		
		SwapBuffer();
	}


	void Application::CalculateDeltaTime()
	{
		float currentTime = (float)glfwGetTime();
		m_DeltaTime = (currentTime - m_PreviousTime); //get delta time
		m_PreviousTime = currentTime;

		static unsigned int CurrentFrames = 0;
		CurrentFrames++;

		static double fpsTimer = currentTime;
		if (currentTime - fpsTimer >= 1)
		{
			m_FrameRate = CurrentFrames;
			CurrentFrames = 0;
			fpsTimer = currentTime;
		}
	}

	void Application::InitializeEngineRootSystems() const
	{
		//terminate the engine if a system failed to initialize
		auto InitializeCheck = [](bool status, std::string_view message)
		{
			if (status)
			{
				Logger::LogMessage(Logger::LogType::Message, std::string(message).append(" Initialized!"));
			}
			else
			{
				Logger::LogMessage(Logger::LogType::Critical, std::string(message).append(" Failed!"));
				EG_ASSERT(false && ": Engine Root Initialization Aborted");
			}
		};

		InitializeCheck(InputSystem::Init(), "Input System");
		InitializeCheck(LayerStack::Init(), "Layer Stack");
		//InitializeCheck(Debug::UI::Init(), "Debug UI");
	}

	void Application::ProcessInput() const
	{
		//engine layers have debug inputs, maybe the game layers need to somehow dispatch input into the layers?? idk
		//probably not though. But for sure this controls debug stuff and what not.
		for (auto layer : LayerStack::GetLayers())
			layer->InputEvent();
	}

}
