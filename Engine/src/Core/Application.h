#pragma once

//ENGINE
#include "Core/Core.h"
#include "Renderer/RendererAPI.h"
#include "Input/Input.h"
#include "Core/Window.h"
#include "Core/Debug/DebugUI.h"
#include "Scene/Scene.h"
#include "Renderer/Architecture/Camera/PerspectiveCamera.h"

//STND
#include <cstdint>
#include <functional>

//engine application class meant to be inheritted by the game
//this class handles all the backend engine tasks such as rendering, etc
//IT IS A SINGLETON, BE SURE TO DEFINE CREATEAPPLICATION() IN GAME AS WELL!
namespace Engine
{
	class Layer;

	class Application
	{
	public:
		Application();
		virtual ~Application();
	
		//*************//
		//*ENGINE API*//
		//************//
	public:
		//Call parents AFTER the game's functions
		//Delta time is exposed separetly ie... GetDeltaTime();
		virtual void Start();
		virtual void Tick();

	protected:
		//Calculates the delta time between each frame
		//WARNING: The application class handles this in the game tick
		//however, its exposed for whatever reason it may need to be calculated in the game as well
		void CalculateDeltaTime();

		//returns the time between the last and current frame
		inline const float GetDeltaTime() const { return m_DeltaTime; };

		//run control
		bool m_Running = true;
		
		//create a completely new level
		void CreateLevel(const std::string_view& levelName);

		//open an existing level 
		void LoadLevel(const std::string_view& levelName); 


	public:
		//simply quits the game
		//sets the game loop boolean value to false
		static inline void QuitGame() { s_Instance->m_Running = false; };
		
		//Returns the frame rate
		static const inline unsigned int GetFrameRate() { return s_Instance->m_FrameRate; };

		static inline Renderer::PerspectiveCamera* GetCamera() { return s_Instance->m_Camera; };

		//*************//
		//*ENGINE API*//
		//************//

	
	private:
		void Draw(float deltaTime);
	
		//setup input, and future root systems
		void InitializeEngineRootSystems() const;
		void ProcessInput() const;

	private:
	
	protected:
		std::unique_ptr<Scene::Scene> m_CurrentScene; //heap allocate, because the scene will contain a lot of stuff
		
		Renderer::PerspectiveCamera* m_Camera;
		
	private:
		float m_DeltaTime = 0;
		float m_PreviousTime = 0;
		unsigned int m_FrameRate = 0;

		Window m_Window;
		Renderer::RenderAPI* m_Renderer;



	//class instance just hidden away down here
	public:
		static Application* s_Instance;

		//Returns the window or crashes
		inline const static Window* GetWindow() { if (&s_Instance->m_Window) return &s_Instance->m_Window;
		else { Logger::LogMessage(Logger::LogType::Critical, "Window Invalid!"); EG_ASSERT(false); }
		};
	};

	//needs to be defined in the game
	Application* CreateApplication();
}

//glm experimental features
#define GLM_ENABLE_EXPERIMENTAL