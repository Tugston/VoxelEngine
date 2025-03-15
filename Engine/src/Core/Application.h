#pragma once

//ENGINE
#include "Core/Core.h"
#include "Window.h"
#include "Debug/DebugUI.h"
#include "Renderer/RendererAPI.h"
#include "Scene/Scene.h"

//STND
#include <cstdint>
#include <functional>

//engine application class meant to be inheritted by the game
//this class handles all the backend engine tasks such as rendering, etc
//IT IS A SINGLETON, BE SURE TO DEFINE CREATEAPPLICATION() IN GAME AS WELL!
namespace Engine
{
	class Layer;

	class ENGINE_API Application
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

		//game run control
		bool gameIsRunning = true;

		//Adds a layer for inputs, drawing, etc to be handled in specific order
		//isUI: simple flag for positioning ui layers in the back, because they need to go first for events
		void AddLayer(Layer* newLayer, bool isUI);


	public:
		//simply quits the game
		//sets the game loop boolean value to false
		static inline void QuitGame() { s_Instance->gameIsRunning = false; };
		
		//Returns the frame rate
		static const inline unsigned int GetFrameRate() { return s_Instance->m_FrameRate; };

		//TEMPORARY


		//*************//
		//*ENGINE API*//
		//************//

	
	private:
		void Draw(float deltaTime);
	
		//setup input, and future root systems
		void InitializeEngineRootSystems() const;
		void ProcessInput() const;

	protected:
		
	private:
		float m_DeltaTime = 0;
		float m_PreviousTime = 0;
		unsigned int m_FrameRate = 0;

		Window m_Window;
		Renderer::RenderAPI m_Renderer;
		Scene m_CurrentScene;
		
		bool m_Running = true;


	//class instance just hidden away down here
	public:
		static Application* s_Instance;

		//Returns the window
		inline const static Window* GetWindow() { return &s_Instance->m_Window; };
	};

	//needs to be defined in the game
	Application* CreateApplication();
}