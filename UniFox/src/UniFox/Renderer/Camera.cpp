#include "ufpch.h"
#include "UniFox/Renderer/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace UniFox {
    /////////////////////////////
    //// Orthographic Camera ////
    /////////////////////////////
    OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom) 
        : m_ProjectionMatrix(glm::ortho(left, right, top, bottom, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
        UF_PROFILE_FUNCTION();
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float top, float bottom) {
        UF_PROFILE_FUNCTION();
        
        m_ProjectionMatrix = glm::ortho(left, right, top, bottom, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix() {
        UF_PROFILE_FUNCTION();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
    
    ////////////////////////////
    //// Perspective Camera ////
    ////////////////////////////
    PerspectiveCamera::PerspectiveCamera(float fov, float aspect)
        : m_ProjectionMatrix(glm::perspective(fov, aspect, 0.1f, 1000.0f)), m_ViewMatrix(1.0f) {
        UF_PROFILE_FUNCTION();
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::SetProjection(float fov, float aspect) {
        UF_PROFILE_FUNCTION();
        
        m_ProjectionMatrix = glm::perspective(fov, aspect, 0.1f, 1000.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::RecalculateViewMatrix() {
        UF_PROFILE_FUNCTION();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}