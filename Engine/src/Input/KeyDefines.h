#pragma once

#include "sdl2/SDL.h"

namespace Engine
{
	enum class EngineKeys
	{
		LeftClick	=		SDL_BUTTON_LEFT,
		RightClick  =		SDL_BUTTON_RIGHT,
		W			=		SDL_KeyCode(SDLK_w),
		A			=		SDL_KeyCode(SDLK_a),
		S			=		SDL_KeyCode(SDLK_s),
		D			=		SDL_KeyCode(SDLK_d),
		Space		=		SDL_KeyCode(SDLK_SPACE),
		Enter		=		SDL_KeyCode(SDLK_RETURN),
		BackSpace	=		SDL_KeyCode(SDLK_BACKSPACE)
	};
}