#pragma once

//ENGINE
#include "Core/Core.h"
#include "Window.h"

//STND
#include <cstdint>
#include <functional>

//engine application class meant to be inheritted by the game
//this class handles all the backend engine tasks such as rendering, etc
//IT IS A SINGLETON, BE SURE TO DEFINE CREATE APPLICATION IN GAME AS WELL!
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
		float m_DeltaTime;
		float m_PreviousTime;

		Window m_Window;
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