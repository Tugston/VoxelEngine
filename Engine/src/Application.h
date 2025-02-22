#pragma once

//ENGINE
#include "Core/Core.h"
#include "Renderer/Window.h"

//STND
#include <cstdint>

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


		inline static Window* GetWindow() { return s_Instance->m_Window.get(); };

	protected:
		void CalculateDeltaTime();
		inline const float GetDeltaTime() const { return m_DeltaTime; };

		bool gameIsRunning = true;

	private:
		void InitializeEngineRootSystems() const;
		void GeneralSetup();

	private:
		float m_DeltaTime;
		uint32_t m_PreviousTime;

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;


	//class instance just hidden away
	public:
		static Application* s_Instance;
	};

	//needs to be defined in the game
	Application* CreateApplication();
}