#pragma once

#include "CallBackEvent.h"

class MouseMoveEvent : public CallBackEvent
{
public:
	MouseMoveEvent(const float& x, const float& y) :
		m_MouseX(x), m_MouseY(y) {}
	
	inline float GetX() const { return m_MouseX; };
	inline float GetY() const { return m_MouseY; };
	inline EventType GetEventType() const override { return EventType::MouseMoved; };
	inline const char* GetName() const override { return "MouseMovedEvent"; };

private:
	float m_MouseX;
	float m_MouseY;
};

class MouseScrollEvent : public CallBackEvent
{
public:
	MouseScrollEvent(const float& scrollAmnt) :
		m_ScrollAmnt(scrollAmnt){};

	inline float GetScrollAmount() const { return m_ScrollAmnt; };
	inline EventType GetEventType() const override { return EventType::MouseScrolled; };
	inline const char* GetName() const override { return "MouseScrollEvent"; };
private:
	float m_ScrollAmnt;
};
