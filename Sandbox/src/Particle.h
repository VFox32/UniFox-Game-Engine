#pragma once

#include "UniFox.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//// TODO ////
// - Fix spawn rate
// - update properties at runtime

class Emitter {
private:
    struct Particle {
        glm::vec4 position;
        glm::vec4 velocity;
        glm::vec4 color;
        glm::vec4 other; // x = lifetime, y = size, z = textureID
    };
public:
    Emitter(
        glm::vec3 position, int positionShape, glm::vec3 positionDirection, float positionSize1, float positionSize2,
        glm::vec3 velocityDirection, int velocityShape, glm::vec3 velocityMagnitude, float velocitySize1, float velocitySize2,
        glm::vec4 startColor, glm::vec4 endColor,
        float size, float sizeVariance,
        float lifetime, float lifetimeVariance,
        float fadeOut, float spawnRate) 
        : m_Position(position), m_PositionShape(positionShape), m_PositionDirection(positionDirection), m_PositionSize1(positionSize1), m_PositionSize2(positionSize2),
        m_VelocityDirection(velocityDirection), m_VelocityShape(velocityShape), m_VelocityMagnitude(velocityMagnitude), m_VelocitySize1(velocitySize1), m_VelocitySize2(velocitySize2),
        m_StartColor(startColor), m_EndColor(endColor), m_Size(size), m_SizeVariance(sizeVariance), m_Lifetime(lifetime), m_LifetimeVariance(lifetimeVariance), m_FadeOut(fadeOut), m_SpawnRate(spawnRate) {

        m_MaxParticles = static_cast<uint32_t>((lifetime + lifetimeVariance) * spawnRate);

        m_VAO = UniFox::VertexArray::Create();
        m_ParticleShader = UniFox::Shader::Create("assets/shaders/shader.glsl");
        
        m_StorageBuffer = UniFox::StorageBuffer::Create(nullptr, m_MaxParticles * sizeof(Particle));
        m_ComputeShader = UniFox::Shader::Create("assets/shaders/particle.glsl");
        m_ComputeShader->Bind();
        m_ComputeShader->SetFloat("u_Lifetime", m_Lifetime);
        m_ComputeShader->SetFloat("u_LifetimeVariance", m_LifetimeVariance);

        m_ComputeShader->SetFloat3("u_Position", m_Position);
        m_ComputeShader->SetInt("u_PositionShape", m_PositionShape);
        m_ComputeShader->SetFloat3("u_PositionShapeDirection", m_PositionDirection);
        m_ComputeShader->SetFloat("u_PositionSize1", m_PositionSize1);
        m_ComputeShader->SetFloat("u_PositionSize2", m_PositionSize2);

        m_ComputeShader->SetFloat3("u_VelocityDirection", m_VelocityDirection);
        m_ComputeShader->SetInt("u_VelocityShape", m_VelocityShape);
        m_ComputeShader->SetFloat3("u_VelocityMagnitude", m_VelocityMagnitude);
        m_ComputeShader->SetFloat("u_VelocitySize1", m_VelocitySize1);
        m_ComputeShader->SetFloat("u_VelocitySize2", m_VelocitySize2);

        m_ComputeShader->SetFloat4("u_StartColor", m_StartColor);
        m_ComputeShader->SetFloat4("u_EndColor", m_EndColor);
        m_ComputeShader->SetFloat("u_Size", m_Size);
        m_ComputeShader->SetFloat("u_SizeVariance", m_SizeVariance);
        m_ComputeShader->SetFloat("u_FadeOut", m_FadeOut);

        float zero = 0.0f;
        m_AtomicBuffer = UniFox::StorageBuffer::Create(&zero, sizeof(float));

        static float quadVertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, 1.0f, 1.0f
        };
        UniFox::Ref<UniFox::VertexBuffer> quadVertexBuffer = UniFox::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
        UniFox::BufferLayout particelLayout = {
            {UniFox::ShaderDataType::Float2, "a_QuadPos"},
            {UniFox::ShaderDataType::Float2, "a_TexCoord"}
        };
        quadVertexBuffer->SetLayout(particelLayout);
        m_VAO->AddVertexBuffer(quadVertexBuffer);
        static uint32_t quadIndices[] = {
            0, 1, 2,
            2, 1, 3
        };
        UniFox::Ref<UniFox::IndexBuffer> particleIndexBuffer = UniFox::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
        m_VAO->SetIndexBuffer(particleIndexBuffer);

        m_Texture1 = UniFox::Texture2D::Create("assets/textures/54p_.png");
        m_Texture2 = UniFox::Texture2D::Create("assets/textures/Missing_Texture.png");
        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
    }

    ~Emitter() {
    }

    void OnUpdate(UniFox::Duration dt, UniFox::PerspectiveCamera camera) {
        m_ParticleShader->Bind();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
        transform = glm::scale(transform, {1.0f, 1.0f, 1.0f});
        m_ParticleShader->SetMat4("u_Transform", transform);
        int samplers[2] = {0, 1};
        m_ParticleShader->SetMat4("u_View", camera.GetViewMatrix());
        m_ParticleShader->SetIntV("u_Textures", samplers, 2);

        static float zero[] = {0};
        m_AtomicBuffer->Bind(1);
        m_AtomicBuffer->SetData(zero, sizeof(zero));

        m_ParticlesToSpawn += m_SpawnRate * dt;
        m_ComputeShader->Bind();
        m_ComputeShader->SetFloat("u_Time", UniFox::Clock::RunTime().ms() / 1000.0);
        m_ComputeShader->SetFloat("u_DeltaTime", dt);
        m_ComputeShader->SetFloat("u_ParticlesToSpawn", m_ParticlesToSpawn);
        m_ParticlesToSpawn -= std::floor(m_ParticlesToSpawn);

        UniFox::Renderer::Compute(m_ComputeShader, m_StorageBuffer, {(m_MaxParticles + 255) / 256, 1, 1});
        UniFox::Renderer::SubmitInstanced(m_ParticleShader, m_VAO, transform, m_MaxParticles);
    }
public:
    UniFox::Ref<UniFox::StorageBuffer> m_StorageBuffer, m_AtomicBuffer;
    UniFox::Ref<UniFox::Shader> m_ComputeShader;
    UniFox::Ref<UniFox::VertexArray> m_VAO;
    UniFox::Ref<UniFox::Shader> m_ParticleShader;

    UniFox::Ref<UniFox::Texture2D> m_Texture1, m_Texture2;

    uint32_t m_MaxParticles;
    float m_ParticlesToSpawn;

    float m_SpawnRate;
    float m_Lifetime;
    float m_LifetimeVariance;

    glm::vec3 m_Position;
    int m_PositionShape;
    glm::vec3 m_PositionDirection;
    float m_PositionSize1;
    float m_PositionSize2;

    glm::vec3 m_VelocityDirection;
    int m_VelocityShape;
    glm::vec3 m_VelocityMagnitude;
    float m_VelocitySize1;
    float m_VelocitySize2;

    glm::vec4 m_StartColor;
    glm::vec4 m_EndColor;
    float m_Size;
    float m_SizeVariance;
    float m_FadeOut;
};