/*
* File: KeyDefines.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-17 (yyyy/mm/dd)
*
* Description: Coorelate supported keys to glfw's system
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGINE
#include "Core/Core.h"

//VENDOR
#include <glfw/glfw3.h>

namespace Engine
{
	enum class EngineKeys
	{

		//MOUSE
		LeftClick	=		GLFW_MOUSE_BUTTON_1,
		RightClick  =		GLFW_MOUSE_BUTTON_2,

		//ALPHABET KEYS
		Q			=		GLFW_KEY_Q,
		W			=		GLFW_KEY_W,
		E			=		GLFW_KEY_E,
		R			=		GLFW_KEY_R,
		T			=		GLFW_KEY_T,
		Y			=		GLFW_KEY_Y,
		U			=		GLFW_KEY_U,
		I			=		GLFW_KEY_I,
		O			=		GLFW_KEY_O,
		P			=		GLFW_KEY_P,
		A			=		GLFW_KEY_A,
		S			=		GLFW_KEY_S,
		D			=		GLFW_KEY_D,
		F			=		GLFW_KEY_F,
		G			=		GLFW_KEY_G,
		H			=		GLFW_KEY_H,
		J			=		GLFW_KEY_J,
		K			=		GLFW_KEY_K,
		L			=		GLFW_KEY_L,
		Z			=		GLFW_KEY_Z,
		X			=		GLFW_KEY_X,
		C			=		GLFW_KEY_C,
		V			=		GLFW_KEY_V,
		B			=		GLFW_KEY_B,
		N			=		GLFW_KEY_N,
		M			=		GLFW_KEY_M,

		//NUMBER KEYS
		ONE			=		GLFW_KEY_1,
		TWO			=		GLFW_KEY_2,
		THREE		=		GLFW_KEY_3,
		FOUR		=		GLFW_KEY_4,
		FIVE		=		GLFW_KEY_5,
		SIX			=		GLFW_KEY_6,
		SEVEN		=		GLFW_KEY_7,
		EIGHT		=		GLFW_KEY_8,
		NINE		=		GLFW_KEY_9,
		ZERO		=		GLFW_KEY_0,

		//MODIFICATION KEYS
		Space		=		GLFW_KEY_SPACE,
		Enter		=		GLFW_KEY_ENTER,
		BackSpace	=		GLFW_KEY_BACKSPACE,
		TAB			=		GLFW_KEY_TAB,
		ESC			=		GLFW_KEY_ESCAPE,
		CAPS		=		GLFW_KEY_CAPS_LOCK,
		LSHIFT		=		GLFW_KEY_LEFT_SHIFT,
		RSHIFT		=		GLFW_KEY_RIGHT_SHIFT,
		LCTRL		=		GLFW_KEY_LEFT_CONTROL,
		RCTRL		=		GLFW_KEY_RIGHT_CONTROL,
		LALT		=		GLFW_KEY_LEFT_ALT,
		RALT		=		GLFW_KEY_RIGHT_ALT,
		LARROW		=		GLFW_KEY_LEFT,
		RARROW		=		GLFW_KEY_RIGHT,
		DARROW		=		GLFW_KEY_DOWN,
		UARROW		=		GLFW_KEY_UP,

		//SPECIAL KEYS
		MINUS		=		GLFW_KEY_MINUS,
		EQUAL		=		GLFW_KEY_EQUAL,
		F1			=		GLFW_KEY_F1,
		F2			=		GLFW_KEY_F2,
		F3			=		GLFW_KEY_F3,
		F4			=		GLFW_KEY_F4,
		F5			=		GLFW_KEY_F5,
		F6			=		GLFW_KEY_F6,
		F7			=		GLFW_KEY_F7,
		F8			=		GLFW_KEY_F8,
		F9			=		GLFW_KEY_F9,
		F10			=		GLFW_KEY_F10,
		F11			=		GLFW_KEY_F11,
		F12			=		GLFW_KEY_F12
	};
}