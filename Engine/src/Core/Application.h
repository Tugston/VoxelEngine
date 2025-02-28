#pragma once

//ENGINE
#include "Core/Core.h"
#include "Window.h"

//STND
#include <cstdint>
#include <functional>

//engine application class meant to be inheritted by the game
//this class handles all the backend engine tasks such as rendering, etc
namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
	
	public:
		virtual void Start();
		virtual void Tick();
		void Draw(float deltaTime);

	protected:
		void CalculateDeltaTime();
		inline const float GetDeltaTime() const { return m_DeltaTime; };

		bool gameIsRunning = true;

	private:
		
		//setup input, and future root systems
		void InitializeEngineRootSystems() const;

	private:
		float m_DeltaTime;
		float m_PreviousTime;

		Window m_Window;
		bool m_Running = true;


	//class instance just hidden away down here
	public:
		static Application* s_Instance;
		inline const static Window* GetWindow() { return &s_Instance->m_Window; };
	};

	//needs to be defined in the game
	Application* CreateApplication();
}