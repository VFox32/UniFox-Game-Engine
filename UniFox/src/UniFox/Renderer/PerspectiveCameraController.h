#pragma once

#include "UniFox/Renderer/PerspectiveCamera.h"
#include "UniFox/Core/Time.h"

#include "UniFox/Events/Event.h"
#include "UniFox/Events/MouseEvent.h"
#include "UniFox/Events/WindowEvent.h"
#include "UniFox/Events/KeyEvent.h"
#include "UniFox/Core/KeyCodes.h"

namespace UniFox {
    class PerspectiveCameraController {
    public:
        PerspectiveCameraController(float fov, float aspectRatio, bool rotation = false);

        void OnUpdate(Duration dt);
        void OnEvent(Event& e);

        PerspectiveCamera& GetCamera() {return m_Camera;}
        const PerspectiveCamera& GetCamera() const {return m_Camera;}
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);
    private:
        float m_AspectRatio;
        float m_FOV = 90.0f;
        PerspectiveCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraRotation = glm::vec3(0.0f);
        glm::vec3 m_CameraPosition = glm::vec3(0.0f);
        float m_CameraTranslationSpeed = 5.0f;
        float m_CameraRotationSpeed = 180.0f;
        float m_PrevMouseX = 0.0f;
        float m_PrevMouseY = 0.0f;

        bool m_Active = 1;
    };
}