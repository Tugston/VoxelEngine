#pragma once

//ENGINE
#include "KeyDefines.h"

//VENDOR
#include <glm/glm.hpp>

namespace Engine
{
	struct InputEvent
	{
	protected:
		KeyState m_State;
	};

	struct MouseEvent : public InputEvent
	{
	private:
		EngineKeys m_Key;
		glm::vec2 m_MouseCoords;
		float m_ScrollAmnt;
	public:
		MouseEvent(EngineKeys key, KeyState state, const glm::vec2& coords, float scrollAmnt) :
			m_Key(key), m_MouseCoords(coords), m_ScrollAmnt(scrollAmnt)
		{
			m_State = state;
		};

		KeyState GetState() const { return m_State; };
		EngineKeys GetKey() const { return m_Key; };
		glm::vec2 GetCoords() const { return m_MouseCoords; };
	};

	struct KeyEvent : public InputEvent
	{
	private:
		EngineKeys m_Key;
	public:
		KeyEvent(EngineKeys key, KeyState state) : 
			m_Key(key)
		{ 
			m_State = state;
		};

		KeyState GetState() const { return m_State; };
		EngineKeys GetKey() const { return m_Key; };
	};
}