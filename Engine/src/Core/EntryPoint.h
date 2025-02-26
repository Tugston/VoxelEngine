#pragma once

//FILE CANNOT BE INCLUDED ANYWHERE

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
