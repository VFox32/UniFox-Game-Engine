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

        m_Instances = new float[m_MaxParticles * 9];

        m_ParticleCount = 0;

        for (uint32_t i = 0; i < m_MaxParticles; i++) {
            m_Alive[i] = 0;
            m_LifeTimes[i] = 0.0f;
        }

        m_ParticlesToSpawn = 0.0f;

        static float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f
        };
        static uint32_t indices[] = {
            0, 1, 2,
            2, 1, 3
        };

        m_VAO->GetVertexBuffers()[0]->SetData(vertices, sizeof(vertices) * sizeof(float));
        m_VAO->GetIndexBuffer()->SetData(indices, sizeof(indices) / sizeof(uint32_t));
    }

    ~Emitter() {
        delete[] m_Alive;
        delete[] m_LifeTimes;
        delete[] m_Positions;
        delete[] m_Velocities;
        delete[] m_Colors;
        delete[] m_Sizes;
        delete[] m_TextureIDs;

        delete[] m_Instances;
    }

    uint32_t GetCount() const {
        return m_ParticleCount;
    }

    void OnUpdate(UniFox::Duration dt, UniFox::PerspectiveCamera camera) {
        float s = dt.Seconds();
        // update lifetime
        for(int i = 0; i < m_MaxParticles; i++) {
            if(!m_Alive[i]) continue;
            m_LifeTimes[i] -= s;
            if(m_LifeTimes[i] <= 0.0) {
                m_Alive[i] = false;
                m_ParticleCount--;
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
            m_ParticleCount++;
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
        uint32_t instanceOffset = 0;
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

            m_Instances[instanceOffset + 0] = m_Positions[i].x;
            m_Instances[instanceOffset + 1] = m_Positions[i].y;
            m_Instances[instanceOffset + 2] = m_Positions[i].z;
            m_Instances[instanceOffset + 3] = m_Colors[i].r;
            m_Instances[instanceOffset + 4] = m_Colors[i].g;
            m_Instances[instanceOffset + 5] = m_Colors[i].b;
            m_Instances[instanceOffset + 6] = m_Colors[i].a;
            m_Instances[instanceOffset + 7] = m_Sizes[i];
            m_Instances[instanceOffset + 8] = m_TextureIDs[i];
            instanceOffset += 9;
        }

        m_VAO->GetVertexBuffers()[1]->SetData(m_Instances, instanceOffset * sizeof(float));
    }
private:
    UniFox::Ref<UniFox::VertexArray> m_VAO;

    std::random_device m_RD;
    std::mt19937 m_Gen;
    std::uniform_real_distribution<float> m_Dist;

    float rand() {
        return m_Dist(m_Gen);
    }

    float* m_Instances;
    
    float* m_LifeTimes;
    glm::vec3* m_Positions;
    glm::vec3* m_Velocities;
    glm::vec4* m_Colors;
    float* m_Sizes;
    uint8_t* m_Alive;
    float* m_TextureIDs;

    uint32_t m_MaxParticles;
    float m_ParticlesToSpawn;
    uint32_t m_ParticleCount;

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