#pragma once

//ENGINE
#include "Core/Core.h"

//STND
#include <cstdint>

//engine application class meant to be inheritted by the game
//this applicatition just handles delta time as of now
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
		const float GetDeltaTime() const;

	protected:
		bool gameIsRunning = true;
	private:
		float m_DeltaTime;
		uint32_t m_PreviousTime;
	};

	//needs to be defined in the game
	Application* CreateApplication();
}