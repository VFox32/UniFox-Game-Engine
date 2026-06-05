#include "ufpch.h"
#include "UniFox/Platform/Linux/LinuxInput.h"

#include "UniFox/Core/Application.h"

#include "GLFW/glfw3.h"

namespace UniFox {

    Ref<Input> Input::s_Instance = MakeRef<WindowsInput>();

    bool LinuxInput::IsKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return {(float)xPos, (float)yPos};
    }

    float LinuxInput::GetMouseXImpl() {
        auto[x, y] = GetMousePosition();
        return x;
    }

    float LinuxInput::GetMouseYImpl() {
        auto[x, y] = GetMousePosition();
        return y;
    }
}