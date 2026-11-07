/*
* File: LayerStack.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-08 (yyyy/mm/dd)
*
* Description: Controls the layers of entities to aid the renderer and debug views and what not
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

/**
* @file LayerStack.h
* @brief Controls and groups the rendering and input order.
*
* @details The layer system is a very simple setup. Each scene consists of the same four layers in non dist builds. The dist build does not need engine features, so these are removed and only the game layers are present. The layer orders are as follows...
* 
* Viper::WorldLayer (Game World) -> Viper::EngineWorldLayer (line traces, collision boxes, etc) -> Viper::UILayer -> Viper::EngineUILayer (Engine details)
* 
* This system is primarily meant to render the Game's UI on top of the Game's scene rendering. Every scene follows this same order and process, so the LayerStack class is static.
* 
*/

//ENGINE
#include "Core/Layers/Layer.h"

//STND
#include<vector>

namespace Viper
{
	class LayerStack
	{
	public:
		static bool Init();
		static void Destroy();

		/**
		* @brief Add a Layer object to the stack of a world type.
		* @details Inserts a new Layer right before the CurrentLocation() iterator. Then the function calls the pure virtual Layer::Attach() function to setup the layer itself. If the setup is successful, incriment m_EmplaceIndex by one and log success. Otherwise, log a failure message.
		* 
		* @note These are the actual scene layers for both engine debug and game world.
		* 
		* @param[in, out] layer The specific layer type to be added, must be a type of WorldLayer or EngineWorldLayer.
		* 
		* @return True if the layer was successfully setup and added, false otherwise.
		*/
		static void PushWorldLayer(Layer* layer);

		/**
		* @brief Add a Layer object to the stack of a UI type.
		* @details Pushes back a new Layer at the very end of #m_Layers. Then the pure virtual Layer::Attach() function is called to setup the layer itself. The #m_EmplaceIndex does not require being updated because this adds layers to the very back anyways. Log a message to state if everything attached and setup properly.
		* 
		* @note These are the UI layers for both the engine debug, game, and game debug.
		* 
		* @param[in, out] layer The specific layer type to be added, must be a child of UILayer, UIDebugLayer, or EngineUILayer.
		* 
		* @return True if the layer was successfully setup and added, false otherwise.
		*/
		static void PushUILayer(Layer* layer);

		/**
		* @brief Clear all layers entirely.
		* @details Checks if #m_Layers actually has layers, if not return. If it does, loop through each layer deleting the pointer. Then finally clear the vector itself.
		* 
		* @post #m_Layers is full cleared completely.
		*/
		static void Clear();
		static void RemoveLayer(const std::vector<Layer*>::iterator& LayerPosition);


		//take advantage of the layer "stack" actually being an underlying vector
		static const bool CheckLayerExists(LayerID id);

		static std::vector<Layer*>::iterator Top();
		static std::vector<Layer*>::iterator Bottom();

		//current location stores the halfway point, ie, where Space and UI layers meet
		static std::vector<Layer*>::iterator CurrentLocation();
		static inline unsigned int CurrentLocationVal() { return m_insertIdex; };

		static const inline std::vector<Layer*> GetLayers() { return m_Layers; };
	private:
		static std::vector<Layer*> m_Layers; //Layer Stack will have full control over layers, so not worrying about smart pointers
		static unsigned int m_insertIdex;
	};



	//Setting these to macros so it avoids a series of function calls
	//basically, the engine application needs to control these, and they are used for debugging

#if defined(EG_DEBUG) || defined(APP_DEBUG)
	#ifndef REMOVE_ENGINE_UI_LAYER
	#define REMOVE_ENGINE_UI_LAYER \
		for(std::vector<Layer*>::iterator i = Viper::LayerStack::CurrentLocation(); i < Viper::LayerStack::Bottom(); i++){\
			if((*i)->GetID() == LayerID::EngineUI){\
				Viper::LayerStack::RemoveLayer(i);\
				break;\
			}\
		};
	#endif

	//remove the engine render layer from the layer stack
	#ifndef REMOVE_ENGINE_DEBUG_LAYER
	#define REMOVE_ENGINE_DEBUG_LAYER \
		for(std::vector<Layer*>::iterator i = Viper::LayerStack::Top(); i < Viper::LayerStack::CurrentLocation(); i++){\
			if((*i)->GetID() == LayerID::EngineWorld){\
				Viper::LayerStack::RemoveLayer(i);\
				break;\
			}\
		};
	#endif

	//maybe the game world layer will need to be removed to test engine debug features 
	//so adding it just in case, debug only obviously
	#ifndef REMOVE_GAME_WORLD_LAYER
	#define REMOVE_GAME_WORLD_LAYER(x)\
		for(std::vector<Layer*>::iterator i = Viper::LayerStack::Top(); i < Viper::LayerStack::CurrentLocation(); i++){\
			if((*i)->GetID() == x){\
				Viper::LayerStack::RemoveLayer(i);\
				break;\
			}\
		};
	#endif
#else
	#ifndef REMOVE_ENGINE_UI_LAYER
	#define REMOVE_ENGINE_UI_LAYER
	#endif
	#ifndef REMOVE_ENGINE_DEBGUG_LAYER
	#define REMOVE_ENGINE_DEBUG_LAYER
	#endif
	#ifndef REMOVE_GAME_WORLD_LAYER(x)
	#define REMOVE_GAME_WORLD_LAYER(x)
	#endif
#endif

//this macro is the only one available in the dist build so I am not having the world readably refer to layers
#ifndef REMOVE_UI
	//completely removes all ui from the screen
	//this includes disabling the rendering, input, and hit detection
	#define REMOVE_UI\
		for(std::vector<Layer*>::iterator i = Viper::LayerStack::CurrentLocation(); i < Viper::LayerStack::Bottom(); i++){\
			Viper::LayerStack::RemoveLayer(i);\
			break;\
		};
#endif
}
