#pragma once

#include "UniFox.h"

struct Particle {
    glm::vec4 position;
    glm::vec4 velocity;
    glm::vec4 color;
    glm::vec4 other; // x = lifetime, y = size, z = textureID
};

class Emitter {
public:
    Emitter(UniFox::Ref<UniFox::VertexArray> vao, glm::vec3 position, glm::vec3 positionVariance, glm::vec3 velocity, glm::vec3 velocityVariance, glm::vec4 startColor, glm::vec4 endColor, float size, float sizeVariance, float lifetime, float lifetimeVariance, float fadeOut, float spawnRate) 
        : m_VAO(vao), m_Position(position), m_PositionVariance(positionVariance), m_Velocity(velocity), m_VelocityVariance(velocityVariance), m_StartColor(startColor), m_EndColor(endColor), m_Size(size), m_SizeVariance(sizeVariance), m_Lifetime(lifetime), m_LifetimeVariance(lifetimeVariance), m_FadeOut(fadeOut), m_SpawnRate(spawnRate) {

        m_MaxParticles = static_cast<uint32_t>((lifetime + lifetimeVariance) * spawnRate);

        static float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
            -0.5f,  0.5f,
             0.5f,  0.5f
        };
        static uint32_t indices[] = {
            0, 1, 2,
            2, 1, 3
        };

        m_VAO->GetVertexBuffers()[0]->SetData(vertices, sizeof(vertices) * sizeof(float));
        m_VAO->GetIndexBuffer()->SetData(indices, sizeof(indices) / sizeof(uint32_t));
    }

    ~Emitter() {
    }

    void OnUpdate(UniFox::Duration dt, UniFox::PerspectiveCamera camera) {
        float s = dt.Seconds();
    }
private:
    UniFox::Ref<UniFox::VertexArray> m_VAO;

    uint32_t m_MaxParticles;

    float m_SpawnRate;
    float m_Lifetime;
    float m_LifetimeVariance;
    glm::vec3 m_Position;
    glm::vec3 m_PositionVariance;
    glm::vec3 m_Velocity;
    glm::vec3 m_VelocityVariance;
    glm::vec4 m_StartColor;
    glm::vec4 m_EndColor;
    float m_Size;
    float m_SizeVariance;
    float m_FadeOut;
};