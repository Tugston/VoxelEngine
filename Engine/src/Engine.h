#pragma once

//STND
#include	<numbers>

//ENGINE
#include	"Core/Application.h"	//Required Application Class
#include	"Core/Logger.h"			//Logging System
#include	"Input/Input.h"			//Input System
#include	"Scene/Scene.h"			//Level / Scene (scene includes ecs registry which includes all components)

//add all the default game objects
#include	"Scene/ECS/GameObjects/GameObject.h"	//Base Game Objects for 2D and 3D


//testing
#include	"Renderer/Architecture/Shader.h"
#include	"Core/Cameras/PerspectiveCamera.h"


//VENDOR
#include	"glm/glm.hpp"
#include	"glm/gtx/string_cast.hpp"

using namespace Engine;
using namespace Engine::Scene::ECS;
using namespace Engine::Scene::ECS::Components;


//API MACROS
#define EG_PI			std::numbers::pi
#define EG_PI_FLOAT		(float)std::numbers::pi
