#pragma once

//---------------------------------------------------------------------
// ENTRY POINT
// FILE CAN ONLY BE INCLUDED ONCE
// NEEDS TO BE INCLUDED AT THE START OF THE GAME'S APPLICATION CPP FILE
// ENTRY POINT
//---------------------------------------------------------------------

//ENGINE
#include "Application.h"
#include "Logger.h"

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int arc, char** argv)
{
	Engine::Logger::Init();
	auto* game = Engine::CreateApplication();
	game->Start();
	delete game;
}

#endif
