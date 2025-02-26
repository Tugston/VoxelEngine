#pragma once

//there are only 2 types of callback events
//one for mouse moving, another for the mouse scroll,
//rest of the input is handled by the InputSystem class in input.h

//STND
#include <string>
#include <functional>

enum class EventType
{
	MouseMoved = 0,
	MouseScrolled
};

class CallBackEvent
{
protected:
	CallBackEvent() {};
public:
	virtual ~CallBackEvent() = default;
	
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;

#ifdef EG_DEBUG
	virtual std::string ToString() const { return GetName(); };
#endif


	bool handled = false;
};

class EventDispatcher
{
public:
	template<typename t>
	void DispatchEvent(CallBackEvent& event, std::function<void(t&)> dispatchFunction)
	{
		if (t* e = dynamic_cast<t*>(&event))
			dispatchFunction(*e);
	};
};
