#pragma once

//this class serves as a bridge between the engine and game for the layers
//the game should only have to deal with the game objects and the game class
//however I am seperating this from the engine layers just to add some potential flexibility
#include "Core/Layers/LayerStack.h"

namespace Engine::API
{
	class WorldLayer : public Engine::Layer
	{
	public:
		WorldLayer();
		~WorldLayer();

		virtual void Attach();
		virtual void Detach();
		virtual void GetDrawData();
		virtual void InputEvent();
	};


	class UILayer : public Engine::Layer
	{
	public:
		UILayer();
		~UILayer();

		virtual void Attach();
		virtual void Detach();
		virtual void GetDrawData();
		virtual void InputEvent();
	};
}
