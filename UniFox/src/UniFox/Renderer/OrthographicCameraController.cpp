#include "ufpch.h"
#include "UniFox/Renderer/OrthographicCameraController.h"

#include "UniFox/Core/Input.h"
#include "UniFox/Core/KeyCodes.h"

namespace UniFox {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
        : m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio*m_ZoomLevel, m_AspectRatio*m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {

    }

    void OrthographicCameraController::OnUpdate(Duration dt) {
        UF_PROFILE_FUNCTION();
        
        glm::vec3 CameraOffset = glm::vec3(0.0f);
        if(Input::IsKeyPressed(UF_KEY_W)) CameraOffset.y += m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_S)) CameraOffset.y -= m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_A)) CameraOffset.x -= m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_D)) CameraOffset.x += m_CameraTranslationSpeed * dt;

        if(m_Rotation) {
            if(Input::IsKeyPressed(UF_KEY_Q)) m_CameraRotation += m_CameraRottationSpeed * dt;
            if(Input::IsKeyPressed(UF_KEY_E)) m_CameraRotation -= m_CameraRottationSpeed * dt;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_CameraPosition += CameraOffset * m_ZoomLevel;
        m_Camera.SetPosition(m_CameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& e) {
        UF_PROFILE_FUNCTION();
        
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseScrolledEvent>(UF_BIND_EVENT_FN(OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(UF_BIND_EVENT_FN(OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
        UF_PROFILE_FUNCTION();
        
        m_ZoomLevel -= e.GetYOffset() * 0.25;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio*m_ZoomLevel, m_AspectRatio*m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
        UF_PROFILE_FUNCTION();
        
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio*m_ZoomLevel, m_AspectRatio*m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}