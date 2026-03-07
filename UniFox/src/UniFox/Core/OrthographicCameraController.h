#pragma once

#include "UniFox/Renderer/OrthographicCamera.h"
#include "UniFox/Core/Time.h"

#include "UniFox/Events/Event.h"
#include "UniFox/Events/MouseEvent.h"
#include "UniFox/Events/WindowEvent.h"

namespace UniFox {
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Duration dt);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() {return m_Camera;}
        const OrthographicCamera& GetCamera() const {return m_Camera;}
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        float m_CameraRotation = 0.0f;
        glm::vec3 m_CameraPosition = glm::vec3(0.0f);
        float m_CameraTranslationSpeed = 5.0f;
        float m_CameraRottationSpeed = 180.0f;
    };
}