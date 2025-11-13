#pragma once

/* ************** NOTICE ********************* */
/* THIS IS THE GAME LAYER, DO NOT GET CONFUSED */
/* ************** NOTICE ********************* */

#include "Core/Layers/LayerStack.h"

namespace Engine
{
	class WorldLayer : public Layer
	{
	public:
		WorldLayer();
		~WorldLayer();

		virtual void Attach();
		virtual void Detach();
		virtual void GetDrawData();
		virtual void InputEvent();
	};


	class UILayer : public Layer
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
