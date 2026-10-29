/*
* File: EntryPoint.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-17 (yyyy/mm/dd)
*
* Description: Main function
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once


/**
* @mainpage Viper Engine
* 
* #Ai & Automation
* Viper Engine utilizes absolutely zero Artificial Intelligence in the creation, formation, or ideation of this project.
* Every aspect of this project and every line of code, apart from the very early beginnings, are created by me.
* This project has evovled across several refactors and reorganizations. Nothing in this project is perfect, but I understand that.
* 
* #Attributions
* This project follows the GPL-3.0 License Identifier. Please utilize and follow the licensing aggreement in the root directory.
* All licensing info is provided in every file above the header guard.
* Any comments or documentation below said guard may or may not represent correct licensing information or possess all needed information to satisfy the license.
* If there are any questions about the licensing, you may email me at VincentPierce.dev@gmail.com
*/

/**
* @file EntryPoint.h
* @brief The main function for the engine
* 
* @details This file must only be included once! It must be placed at the top of your game's application CPP file. Includes protection for Windows only.
* 
* @author Vincent Pierce
* @date February 17, 2025
*/


//ENGINE
#include "Application.h"
#include "Logger.h"

#ifdef ENGINE_PLATFORM_WINDOWS

/**
* @fn int main(int arc, char** argv)
* @brief Starting point
* 
* @post Instantiates, boots, and executes the application context, then deletes it when finished. 
* 
* @param[in] argc The argument count indicating the total parameters provided
* @param[in] argv Specific pointer array for each CLI argument
* 
* @note Command-line arguments are parsed by the platform but are currently bypassed by the engine.
*/
int main(int arc, char** argv)
{
	Engine::Logger::Init();
	auto* game = Engine::CreateApplication();
	game->Start();
	delete game;
}

#endif
