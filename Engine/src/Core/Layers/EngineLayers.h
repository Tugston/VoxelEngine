#pragma once

//ENGINE
#include "Core/Layers/Layer.h"

namespace Engine
{
	class ENGINE_API WorldLayer : public Layer
	{
	public:
		WorldLayer();
		~WorldLayer();

		virtual void Attach();
		virtual void Detach();

		virtual void Draw();
		virtual void InputEvent();
	
	};

	class ENGINE_API UILayer : public Layer
	{
	public:
		UILayer();
		~UILayer();

		virtual void Attach();
		virtual void Detach();

		virtual void Draw();
		virtual void InputEvent();

	private:
		bool m_ShowAllData = false;
		int m_TestInt = 0;
		float m_TestFloat = 0;
	};

}
