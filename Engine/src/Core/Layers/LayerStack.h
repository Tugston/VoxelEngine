#pragma once

//ENGINE
#include "Core/Layers/Layer.h"

//STND
#include<vector>

//I am going for a simple setup where each scene will have the same layers
//my current idea for layers is as so
//Game -> Engine Debug Graphics -> Game UI -> Engine UI Debug
//this is really only a system for the Game's UI to be layered on top of the Game's 3d rendering
//and it will be like that in every scene, which is why I made this static

namespace Engine
{
	class LayerStack
	{
	public:
		static bool Init();
		static void Destroy();

		static void PushSpaceLayer(Layer* layer);	//actual "world" layers
		static void PushUILayer(Layer* layer);		//ui layers
		static void Clear();						//clear all layers

		static void RemoveLayer(const std::vector<Layer*>::iterator& LayerPosition);


		//take advantage of the layer "stack" actually being an underlying vector

		static const bool CheckLayerExists(unsigned char id);

		static std::vector<Layer*>::iterator Top();
		static std::vector<Layer*>::iterator Bottom();

		//current location stores the halfway point, ie, where Space and UI layers meet
		static std::vector<Layer*>::iterator CurrentLocation();
		static inline unsigned int CurrentLocationVal() { return m_emplaceIdex; };

		static const inline std::vector<Layer*> GetLayers() { return m_Layers; };
	private:
		static std::vector<Layer*> m_Layers; //Layer Stack will have full control over layers, so not worrying about smart pointers
		static unsigned int m_emplaceIdex;
	};



	//Setting these to macros so it avoids a series of function calls
	//basically, the engine application needs to control these, and they are used for debugging

#if defined(EG_DEBUG) || defined(APP_DEBUG)
	#ifndef REMOVE_ENGINE_UI_LAYER
	#define REMOVE_ENGINE_UI_LAYER \
		for(std::vector<Layer*>::iterator i = Engine::LayerStack::CurrentLocation(); i < Engine::LayerStack::Bottom(); i++){\
			if((*i)->GetID() == 2){\
				Engine::LayerStack::RemoveLayer(i);\
				break;\
			}\
		};
	#endif

	//remove the engine render layer from the layer stack
	#ifndef REMOVE_ENGINE_DEBUG_LAYER
	#define REMOVE_ENGINE_DEBUG_LAYER \
		for(std::vector<Layer*>::iterator i = Engine::LayerStack::Top(); i < Engine::LayerStack::CurrentLocation(); i++){\
			if((*i)->GetID() == 1){\
				Engine::LayerStack::RemoveLayer(i);\
				break;\
			}\
		};
	#endif

	//maybe the game world layer will need to be removed to test engine debug features 
	//so adding it just in case, debug only obviously
	#ifndef REMOVE_GAME_WORLD_LAYER
	#define REMOVE_GAME_WORLD_LAYER(x)\
		for(std::vector<Layer*>::iterator i = Engine::LayerStack::Top(); i < Engine::LayerStack::CurrentLocation(); i++){\
			if((*i)->GetID() == x){\
				Engine::LayerStack::RemoveLayer(i);\
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

//this macro is the only one available in the share build so I am not having the world readably refer to layers
#ifndef REMOVE_UI
	//completely removes all ui from the screen
	//this includes disabling the rendering, input, and hit detection
	#define REMOVE_UI\
		for(std::vector<Layer*>::iterator i = Engine::LayerStack::CurrentLocation(); i < Engine::LayerStack::Bottom(); i++){\
			Engine::LayerStack::RemoveLayer(i);\
			break;\
		};
#endif
}
