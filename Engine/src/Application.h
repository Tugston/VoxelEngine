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

	protected:
		void CalculateDeltaTime();
		inline const float GetDeltaTime() const { return m_DeltaTime; };

	private:
		void InitializeEngineRootSystems() const;
		void GeneralSetup();

	protected:
		bool gameIsRunning = true;
	private:
		float m_DeltaTime;
		uint32_t m_PreviousTime;

		std::unique_ptr<Window> m_Window;
	};

	//needs to be defined in the game
	Application* CreateApplication();
}