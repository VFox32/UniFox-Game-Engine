#pragma once

#include "UniFox/Renderer/Camera.h"

#include "UniFox/Core/Time.h"
#include "UniFox/Events/Event.h"
#include "UniFox/Events/KeyEvent.h"
#include "UniFox/Events/MouseEvent.h"
#include "UniFox/Events/WindowEvent.h"

namespace UniFox {
    class CameraController {
    public:
        virtual ~CameraController() {}

        virtual void OnUpdate(Duration dt) = 0;
        virtual void OnEvent(Event& e) = 0;

        virtual Camera& GetCamera() = 0;
        virtual const Camera& GetCamera() const = 0;
    };

    class OrthographicCameraController : public CameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        virtual void OnUpdate(Duration dt) override;
        virtual void OnEvent(Event& e) override;

        virtual OrthographicCamera& GetCamera() override {return m_Camera;}
        virtual const OrthographicCamera& GetCamera() const override {return m_Camera;}
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
    
    class PerspectiveCameraController : public CameraController {
    public:
        PerspectiveCameraController(float fov, float aspectRatio, bool rotation = false);

        virtual void OnUpdate(Duration dt) override;
        virtual void OnEvent(Event& e) override;

        virtual PerspectiveCamera& GetCamera() override {return m_Camera;}
        virtual const PerspectiveCamera& GetCamera() const override {return m_Camera;}
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