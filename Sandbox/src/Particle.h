#pragma once

#include "UniFox.h"

#include <random>

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    float size;
    float lifetime;
    bool alive = false;
};

class Emitter {
public:
    Emitter(UniFox::Ref<UniFox::VertexArray> vao, glm::vec3 position, glm::vec3 positionVariance, glm::vec3 velocity, glm::vec3 velocityVariance, glm::vec4 startColor, glm::vec4 endColor, float size, float sizeVariance, float lifetime, float lifetimeVariance, float fadeOut, float spawnRate) 
        : m_VAO(vao), m_Position(position), m_PositionVariance(positionVariance), m_Velocity(velocity), m_VelocityVariance(velocityVariance), m_StartColor(startColor), m_EndColor(endColor), m_Size(size), m_SizeVariance(sizeVariance), m_Lifetime(lifetime), m_LifetimeVariance(lifetimeVariance), m_FadeOut(fadeOut), m_SpawnRate(spawnRate), m_Gen(m_RD()), m_Dist(0.0f, 1.0f) {
        m_MaxParticles = static_cast<uint32_t>((lifetime + lifetimeVariance) * spawnRate);

        m_Alive = new uint8_t[m_MaxParticles];
        m_LifeTimes = new float[m_MaxParticles];
        m_Positions = new glm::vec3[m_MaxParticles];
        m_Velocities = new glm::vec3[m_MaxParticles];
        m_Colors = new glm::vec4[m_MaxParticles];
        m_Sizes = new float[m_MaxParticles];
        m_TextureIDs = new float[m_MaxParticles];

        m_Vertices = new float[m_MaxParticles * 4 * 10]; // 4 vertices per particle, 7 floats per vertex (vec3 pos, vec4 col, vec2 uv, float texID)
        m_Indices = new uint32_t[m_MaxParticles * 6]; // 6 indices per particle

        for (uint32_t i = 0; i < m_MaxParticles; i++) {
            m_Alive[i] = 0;
            m_LifeTimes[i] = 0.0f;
        }

        m_ParticlesToSpawn = 0.0f;
    }

    ~Emitter() {
        delete[] m_Alive;
        delete[] m_LifeTimes;
        delete[] m_Positions;
        delete[] m_Velocities;
        delete[] m_Colors;
        delete[] m_Sizes;
        delete[] m_TextureIDs;

        delete[] m_Vertices;
        delete[] m_Indices;
    }

    void OnUpdate(UniFox::Duration dt, UniFox::PerspectiveCamera camera) {
        float s = dt.Seconds();
        // update lifetime
        for(int i = 0; i < m_MaxParticles; i++) {
            if(!m_Alive[i]) continue;
            m_LifeTimes[i] -= s;
            if(m_LifeTimes[i] <= 0.0) {
                m_Alive[i] = false;
            }
        }

        // spawn new
        m_ParticlesToSpawn += m_SpawnRate * s;
        for(int i = 0; i < m_MaxParticles && m_ParticlesToSpawn >= 1; i++) {
            if(m_Alive[i]) continue;

            m_LifeTimes[i] = m_Lifetime + m_LifetimeVariance * (rand() - 0.5f);
            m_Positions[i].x = m_Position.x + m_PositionVariance.x * (rand() - 0.5f);
            m_Positions[i].y = m_Position.y + m_PositionVariance.y * (rand() - 0.5f);
            m_Positions[i].z = m_Position.z + m_PositionVariance.z * (rand() - 0.5f);
            m_Velocities[i].x = m_Velocity.x + m_VelocityVariance.x * (rand() - 0.5f);
            m_Velocities[i].y = m_Velocity.y + m_VelocityVariance.y * (rand() - 0.5f);
            m_Velocities[i].z = m_Velocity.z + m_VelocityVariance.z * (rand() - 0.5f);
            m_Colors[i] = m_StartColor;
            m_Sizes[i] = m_Size + m_SizeVariance * (rand() - 0.5f);
            m_TextureIDs[i] = round(rand()*2.0f)-1.0f;
            m_Alive[i] = true;

            m_ParticlesToSpawn--;
        }

        // update particles
        for(int i = 0; i < m_MaxParticles; i++) {
            if(!m_Alive[i]) continue;
            m_Velocities[i] += glm::vec3(0, -1, 0) * s;
            m_Positions[i] += m_Velocities[i] * s;

            float ratio = m_LifeTimes[i] / m_Lifetime;
            m_Colors[i] = (m_StartColor * ratio) + (m_EndColor * (1.0f - ratio));
            if(m_FadeOut > 0.0f)
                m_Colors[i].a *= std::min(1.0f, m_LifeTimes[i] / m_FadeOut);
        }

        // generate vertices
        uint32_t vertexOffset = 0;
        for(int i = 0; i < m_MaxParticles; i++) {
            if(!m_Alive[i]) continue;
            float halfSize = m_Sizes[i] * 0.5f;

            glm::vec3 corners[4] = {
                {-halfSize, -halfSize, 0.0f}, // BL
                { halfSize, -halfSize, 0.0f}, // BR
                {-halfSize,  halfSize, 0.0f}, // TL
                { halfSize,  halfSize, 0.0f}, // TR
            };

            static glm::vec2 UVs[4] = {
                {0, 0},
                {1, 0},
                {0, 1},
                {1, 1}
            };

            glm::vec3 particleToCamera = glm::normalize(camera.GetPosition() - m_Positions[i]);
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 right = glm::normalize(glm::cross(worldUp, particleToCamera));
            glm::vec3 up = glm::cross(particleToCamera, right);
            for (int j = 0; j < 4; ++j) {
                glm::vec3 position = m_Positions[i] + corners[j].x * right + corners[j].y * up;
                glm::vec4 color = m_Colors[i];
                glm::vec2 uv = UVs[j];
                m_Vertices[vertexOffset + 0] = position.x;
                m_Vertices[vertexOffset + 1] = position.y;
                m_Vertices[vertexOffset + 2] = position.z;
                m_Vertices[vertexOffset + 3] = color.r;
                m_Vertices[vertexOffset + 4] = color.g;
                m_Vertices[vertexOffset + 5] = color.b;
                m_Vertices[vertexOffset + 6] = color.a;
                m_Vertices[vertexOffset + 7] = uv.x;
                m_Vertices[vertexOffset + 8] = uv.y;
                m_Vertices[vertexOffset + 9] = m_TextureIDs[i];
                vertexOffset += 10;
            }
        }

        // generate indices
        uint32_t indexOffset = 0;
        uint32_t particleOffset = 0;
        for(int i = 0; i < m_MaxParticles; i++) {
            if(!m_Alive[i]) continue;
            m_Indices[indexOffset + 0] = particleOffset + 0;
            m_Indices[indexOffset + 1] = particleOffset + 1;
            m_Indices[indexOffset + 2] = particleOffset + 2;
            m_Indices[indexOffset + 3] = particleOffset + 2;
            m_Indices[indexOffset + 4] = particleOffset + 1;
            m_Indices[indexOffset + 5] = particleOffset + 3;

            indexOffset += 6;
            particleOffset += 4;
        }

        m_VAO->GetVertexBuffers()[0]->SetData(m_Vertices, vertexOffset * sizeof(float));
        m_VAO->GetIndexBuffer()->SetData(m_Indices, indexOffset);
    }
private:
    UniFox::Ref<UniFox::VertexArray> m_VAO;

    std::random_device m_RD;
    std::mt19937 m_Gen;
    std::uniform_real_distribution<float> m_Dist;

    float rand() {
        return m_Dist(m_Gen);
    }

    float* m_Vertices;
    uint32_t* m_Indices;
    
    float* m_LifeTimes;
    glm::vec3* m_Positions;
    glm::vec3* m_Velocities;
    glm::vec4* m_Colors;
    float* m_Sizes;
    uint8_t* m_Alive;
    float* m_TextureIDs;

    uint32_t m_MaxParticles;
    float m_ParticlesToSpawn;

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