#pragma once

//VENDOR
#include "../../../VENDOR/imgui/imgui.h"

//STND
#include<string_view>
#include<limits>

//EDTR
#include "../../EditorCore.h"

namespace Editor {

	// Could do something like this, but seems a bit overkill
	/*
	struct IReferenceContainer {
		virtual ~IReferenceContainer() = default;
	};

	template<typename t>
	struct ReferenceContainer: public IReferenceContainer {
		ReferenceContainer(t* ref) : ref(ref) {};
		t* ref;
	}; */

	class BaseSlot {
	protected:
		BaseSlot(): m_Label("Label"), m_ValRef(nullptr) {};
		BaseSlot(std::string_view label, void* ref) : m_Label(label), m_ValRef(ref) {};
		~BaseSlot() {};
	
	public:
		virtual void Draw() const = 0;
		
	protected:
		std::string_view m_Label;

		//slots are internal for the editor, so this void* wont be exposed
		//each slot is self explanatory of what it expects to change, so void is relatively safe, it just beats the ref container up above imo
		void* m_ValRef;
	};
}


