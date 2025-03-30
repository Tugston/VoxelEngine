#pragma once

//STND
#include	<numbers>

//ENGINE
#include	"Core/Application.h"	//Required Application Class
#include	"Core/Logger.h"			//Logging System
#include	"Input/Input.h"			//Input System
#include	"Scene/Scene.h"			//Level / Scene

//test
#include	"Renderer/Architecture/Shader.h"
#include	"Renderer/Architecture/Camera/PerspectiveCamera.h"


#include	"../VENDOR/imgui/imconfig.h"
#include	"../VENDOR/imgui/imgui_internal.h"
#include	"../VENDOR/imgui/imgui.h"
#include	"../VENDOR/imgui/imgui_impl_glfw.h"
#include	"../VENDOR/imgui/imgui_impl_opengl3.h"
#include	"../VENDOR/imgui/imgui_impl_opengl3_loader.h"

//VENDOR
#include	"glm/glm.hpp"
#include	"glm/gtx/string_cast.hpp"

using namespace Engine;


//API MACROS
#define EG_PI			std::numbers::pi
#define EG_PI_FLOAT		(float)std::numbers::pi
