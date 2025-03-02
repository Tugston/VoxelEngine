#pragma once

//this class serves as a bridge between the engine and game objects, scenes, etc
//ideally the game would only make game objects, but I want the game to have a little more control
//may change in the future, but this just makes sense to me currently

#include<Engine.h>

namespace VoxelGame
{
	class WorldLayer : public Engine::Layer
	{
	public:
		WorldLayer();
		~WorldLayer();

		virtual void Attach();
		virtual void Detach();
		virtual void Draw();
		virtual void InputEvent();
	};


	class UILayer : public Engine::Layer
	{
	public:
		UILayer();
		~UILayer();

		virtual void Attach();
		virtual void Detach();
		virtual void Draw();
		virtual void InputEvent();
	};
}
