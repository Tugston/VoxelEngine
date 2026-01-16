/*
* File: Engine.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-17 (yyyy/mm/dd)
*
* Description: Full api of the engine for ease of accessibility
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//STND
#include	<numbers>

//ENGINE
#include	"Core/Application.h"	//Required Application Class
#include	"Core/Logger.h"			//Logging System
#include	"Core/ScriptModule.h"	//Scripting System
#include	"Core/RandNumGen.h"		//Random Number Generator
#include	"Input/Input.h"			//Input System
#include	"Scene/Scene.h"			//Level / Scene (scene includes ecs registry which includes all components)

//add all the default game objects
#include	"Scene/ECS/GameObjects/GameObject.h"		//Base Game Objects for 2D and 3D
#include	"Scene/ECS/GameObjects/SpriteObject.h"		//Game Objects with Sprites already setup
#include	"Scene/ECS/GameObjects/MeshObject.h"		//Game Object that has Meshes already setup
#include	"Scene/ECS/GameObjects/ScriptableObject.h"	//Game Objects that pretty much just add a script to all other object types

//Components
#include	"Scene/ECS/Components/Data/TransformComponent.h"
#include	"Scene/ECS/Components/Data/ScriptComponent.h"
#include	"Scene/ECS/Components/Renders/SpriteComponent.h"
#include	"Scene/ECS/Components/Renders/MeshComponent.h"
#include	"Scene/ECS/Components/Renders/InstancedMeshComponent.h"

//Base Meshes
#include	"SharedResources/PrimitiveShapes/ThreeDimensions/Cone.h"
#include	"SharedResources/PrimitiveShapes/ThreeDimensions/Cyllinder.h"

#include	"SharedResources/PrimitiveShapes/TwoDimensions/Triangle.h"
#include	"SharedResources/PrimitiveShapes/TwoDimensions/Quad.h"

//TESTING
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



