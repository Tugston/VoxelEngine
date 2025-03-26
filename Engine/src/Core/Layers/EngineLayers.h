#pragma once

//ENGINE
#include "Core/Layers/Layer.h"

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

	private:
		bool m_ShowAllData = false;
		int m_TestInt = 0;
		float m_TestFloat = 0;
	};

}
