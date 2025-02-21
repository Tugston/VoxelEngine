#include "Input.h"

//ENGINE
#include "InputManager.h"

namespace Engine
{
    std::unique_ptr<InputManager> InputSystem::s_InputManager = nullptr;

    bool InputSystem::Init()
    {
        s_InputManager = std::make_unique<InputManager>();
        return s_InputManager.get();
    }

    bool InputSystem::IsKeyPressed(EngineKeys key)
    {
        return false;
    }

    bool InputSystem::IsKeyReleased(EngineKeys key)
    {
        return false;
    }

    bool InputSystem::IsKeyHeld(EngineKeys key)
    {
        return false;
    }

    void InputSystem::ProcessEvents()
    {
    }
}
