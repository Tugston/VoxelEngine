#include "Application.h"

//VENDOR
#include <sdl2/SDL.h>
#include <sdl2/SDL_timer.h>

//ENGINE
#include "Core/Logger.h"

Engine::Application::Application() : m_DeltaTime(0.f), m_PreviousTime(SDL_GetTicks())
{
	Logger::Init();
}

Engine::Application::~Application()
{
}

void Engine::Application::Start()
{
}

void Engine::Application::Tick()
{
	CalculateDeltaTime();
}

void Engine::Application::Draw(float deltaTime)
{
	
}

void Engine::Application::CalculateDeltaTime()
{
	uint32_t currentTime = SDL_GetTicks();
	m_DeltaTime = (currentTime - m_PreviousTime) / 1000.f;
	m_PreviousTime = currentTime;
}

const float Engine::Application::GetDeltaTime() const
{
	return m_DeltaTime;
}
