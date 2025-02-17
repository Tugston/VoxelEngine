#pragma once

//FILE CANNOT BE INCLUDED ANYWHERE

//ENGINE
#include "Application.h"

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int arc, char** argv)
{
	auto* game = Engine::CreateApplication();
	game->Start();
	delete game;
	return 0;
}

#endif
