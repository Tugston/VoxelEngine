#pragma once


/* ************** NOTICE ****************************** */
/* THIS IS THE ENGINE LAYERS, DO NOT GET CONFUSED */
/* THESE ARE USED FOR DEBUGGING AND NOT RLY IN THE DIST */
/* ************** NOTICE ****************************** */

//ENGINE
#include "Core/Layers/Layer.h"

namespace Engine
{
	class EngineWorldLayer : public Layer
	{
	public:
		EngineWorldLayer();
		~EngineWorldLayer();

		virtual void Attach();
		virtual void Detach();

		virtual void GetDrawData();
		virtual void InputEvent();
	
	};

	class EngineUILayer : public Layer
	{
	public:
		EngineUILayer();
		~EngineUILayer();

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
