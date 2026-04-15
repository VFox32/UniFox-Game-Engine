#pragma once

#include "UniFox/Core/Core.h"

#include "glm/glm.hpp"

namespace UniFox {
    class Camera {
    public:
        virtual ~Camera() {};

        virtual glm::vec3 GetPosition() const = 0;
        virtual void SetPosition(const glm::vec3& position) = 0;

        virtual const glm::mat4& GetProjectionMatrix() const = 0;
        virtual const glm::mat4& GetViewMatrix() const = 0;
        virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
    };
    
    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float left, float right, float top, float bottom);
        void SetProjection(float left, float right, float top, float bottom);

        virtual glm::vec3 GetPosition() const override {return m_Position;}
        virtual void SetPosition(const glm::vec3& position) override {m_Position = position; RecalculateViewMatrix();}

        float GetRotation() const {return m_Rotation;}
        void SetRotation(const float& rotation) {m_Rotation = rotation; RecalculateViewMatrix();}

        virtual const glm::mat4& GetProjectionMatrix() const override {return m_ProjectionMatrix;}
        virtual const glm::mat4& GetViewMatrix() const override {return m_ViewMatrix;}
        virtual const glm::mat4& GetViewProjectionMatrix() const override {return m_ViewProjectionMatrix;}
    private:
        void RecalculateViewMatrix();

        glm::vec3 m_Position = glm::vec3(0.0f);
        float m_Rotation = 0.0f;

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
    
    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(float fov, float aspect);
        void SetProjection(float fov, float aspect);

        virtual glm::vec3 GetPosition() const override {return m_Position;}
        virtual void SetPosition(const glm::vec3& position) override {m_Position = position; RecalculateViewMatrix();}

        glm::vec3 GetRotation() const {return m_Rotation;}
        void SetRotation(const glm::vec3& rotation) {m_Rotation = rotation; RecalculateViewMatrix();}

        virtual const glm::mat4& GetProjectionMatrix() const override {return m_ProjectionMatrix;}
        virtual const glm::mat4& GetViewMatrix() const override {return m_ViewMatrix;}
        virtual const glm::mat4& GetViewProjectionMatrix() const override {return m_ViewProjectionMatrix;}
    private:
        void RecalculateViewMatrix();

        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Rotation = glm::vec3(0.0f);

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}