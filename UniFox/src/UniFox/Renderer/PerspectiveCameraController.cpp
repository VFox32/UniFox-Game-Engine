#include "ufpch.h"
#include "UniFox/Renderer/PerspectiveCameraController.h"

#include "UniFox/Core/Input.h"
#include "UniFox/Core/KeyCodes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace UniFox {
    PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, bool rotation) 
        : m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(120, aspectRatio), m_FOV(fov) {
        m_PrevMouseX = Input::GetMouseX();
        m_PrevMouseY = Input::GetMouseY();
    }

    void PerspectiveCameraController::OnUpdate(Duration dt) {
        UF_PROFILE_FUNCTION();
        if(!m_Active) return;
        
        glm::vec3 CameraOffset = glm::vec3(0.0f);
        if(Input::IsKeyPressed(UF_KEY_W)) CameraOffset.z -= m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_S)) CameraOffset.z += m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_A)) CameraOffset.x -= m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_D)) CameraOffset.x += m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_SPACE)) CameraOffset.y += m_CameraTranslationSpeed * dt;
        if(Input::IsKeyPressed(UF_KEY_LEFT_SHIFT)) CameraOffset.y -= m_CameraTranslationSpeed * dt;
        
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation.y), glm::vec3(0, 1, 0))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation.x), glm::vec3(1, 0, 0))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation.z), glm::vec3(0, 0, 1));
        CameraOffset = glm::vec3(rotation * glm::vec4(CameraOffset, 1.0f));

        if(m_Rotation) {
            if(Input::IsKeyPressed(UF_KEY_Q)) m_CameraRotation.z += m_CameraRotationSpeed * dt;
            if(Input::IsKeyPressed(UF_KEY_E)) m_CameraRotation.z -= m_CameraRotationSpeed * dt;
            
            float mouseX = Input::GetMouseX();
            float mouseY = Input::GetMouseY();

            float deltaX = mouseX - m_PrevMouseX;
            float deltaY = mouseY - m_PrevMouseY;

            m_CameraRotation.x -= deltaY * dt * 20.0f;
            m_CameraRotation.x -= deltaY * dt * 20.0f;
            m_CameraRotation.y -= deltaX * dt * 20.0f;
            m_CameraRotation.y -= deltaX * dt * 20.0f;

            m_PrevMouseX = mouseX;
            m_PrevMouseY = mouseY;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_CameraPosition += CameraOffset;
        m_Camera.SetPosition(m_CameraPosition);
    }

    void PerspectiveCameraController::OnEvent(Event& e) {
        UF_PROFILE_FUNCTION();
        
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowResizeEvent>(UF_BIND_EVENT_FN(OnWindowResized));
        dispatcher.Dispatch<KeyPressedEvent>(UF_BIND_EVENT_FN(OnKeyPressed));
    }

    bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e) {
        UF_PROFILE_FUNCTION();
        
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(m_FOV, m_AspectRatio);
        return false;
    }

    bool PerspectiveCameraController::OnKeyPressed(KeyPressedEvent& e) {
        if(e.GetKeyCode() == UF_KEY_LEFT_ALT) {
            if(e.GetRepeatCount() == 0) {
                m_Active ^= 1;
                m_PrevMouseX = Input::GetMouseX();
                m_PrevMouseY = Input::GetMouseY();
            }
        }
        return true;
    }
}