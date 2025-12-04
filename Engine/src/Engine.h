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


//components
#include	"Scene/ECS/Components/Positionals/Transform.h"
#include	"Scene/ECS/Components/Renders/Sprite.h"
#include	"Scene/ECS/Components/Renders/Mesh.h"
#include	"Scene/ECS/Components/Renders/InstancedMesh.h"

//Base Meshes
#include	"SharedResources/PrimitiveShapes/TwoDimensions/Triangle.h"
#include	"SharedResources/PrimitiveShapes/TwoDimensions/Quad.h"

//testing
#include	"SharedResources/GenericResources/Shader.h"
#include	"Core/Cameras/PerspectiveCamera.h"


//VENDOR
#include	"glm/glm.hpp"
#include	"glm/gtx/string_cast.hpp"

//may update these in the future, since types could have conflations with games
//or it may be better to have the game be in a game namespace actually, idk. Still deciding.
using namespace Engine;
using namespace Engine::Utility;
using namespace Engine::Scene::ECS;
using namespace Engine::Scene::ECS::Components;
using namespace Engine::Camera;



