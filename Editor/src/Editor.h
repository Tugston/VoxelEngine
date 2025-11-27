#pragma once

//EDITOR
#include "Globals/Slots/FloatSlot.h"
#include "Globals/Slots/Vector2Slot.h"
#include "Globals/Slots/Vector3Slot.h"

//ENGINE
#include <Engine.h>
#include <Core/EntryPoint.h>

//VENDOR
#include "../VENDOR/imgui/imgui.h"
#include "../VENDOR/imgui/imgui_impl_opengl3.h"
#include "../VENDOR/imgui/imgui_impl_glfw.h"

class GLFWWindow;
class Camera::PerspectiveCamera;

namespace Editor
{
	class FloatSlot;

	class EditorApplication : public Application
	{
	public:
		EditorApplication();
		~EditorApplication();

		virtual void Start() override;
		virtual void Tick() override;

		void Draw();

		virtual void SwapBuffer() override;

	private:
		FloatSlot* m_TestSlot;
		Vector2FSlot* m_Vec2TestSlot;
		Vector3FSlot* m_Vec3TestSlot;

		Camera::PerspectiveCamera* m_Camera;

		float m_TestFloat = 2.f;
	};
}

Application* Engine::CreateApplication()
{
	LOG_MSG("Editor Application Created");
	return new Editor::EditorApplication;
}
