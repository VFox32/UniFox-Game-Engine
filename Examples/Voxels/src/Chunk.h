#pragma once
#include "UniFox.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <array>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>
class PerlinNoise {
public:
    PerlinNoise(unsigned int seed = 2024) {
        // Fill permutation with values 0..255
        std::iota(p.begin(), p.begin() + 256, 0);

        // Shuffle using seed
        std::default_random_engine engine(seed);
        std::shuffle(p.begin(), p.begin() + 256, engine);

        // Duplicate the permutation table
        for (int i = 0; i < 256; ++i)
            p[256 + i] = p[i];
    }

    // Get Perlin noise height at (x, y)
    double noise(double x, double y) const {
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        x -= std::floor(x);
        y -= std::floor(y);

        double u = fade(x);
        double v = fade(y);

        int aa = p[p[X] + Y];
        int ab = p[p[X] + Y + 1];
        int ba = p[p[X + 1] + Y];
        int bb = p[p[X + 1] + Y + 1];

        double res = lerp(v,
            lerp(u, grad(aa, x, y), grad(ba, x - 1, y)),
            lerp(u, grad(ab, x, y - 1), grad(bb, x - 1, y - 1))
        );

        // Normalize result to range [0, 1]
        return (res + 1.0) / 2.0;
    }

private:
    std::array<int, 512> p{};

    static double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    static double grad(int hash, double x, double y) {
        int h = hash & 7; // 8 gradient directions
        double u = h < 4 ? x : y;
        double v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
    }
};

class Chunk {
public:
    struct Node {       // leaf     | not leaf
        uint32_t a = 0; // other    | [8:31] child index [0:7] child mask
        uint32_t b = 0; // material | material (for LOD)
    };

    Chunk(glm::vec3 position) 
        : m_Position(position) {
        m_Transform = glm::translate(glm::mat4(1.0f), position);

        Generate();
        GenMesh();
    }

    void Generate() {
        PerlinNoise noise(12345);
        for(float x = m_Position.x; x < 32.0 + m_Position.x; x++)
        for(float y = m_Position.y; y < 32.0 + m_Position.y; y++)
        for(float z = m_Position.z; z < 32.0 + m_Position.z; z++) {
            float height = noise.noise(x / 32.0, z / 32.0) * 32.0;
            uint32_t fill = height > y ? 1 : 0;
            nodes.push_back(Node(0, fill));
        }

        m_SBO = UniFox::StorageBuffer::Create((float*)(void*)nodes.data(), nodes.size() * sizeof(Node));
    }

    glm::ivec3 GetPos(const uint32_t index) const {
        return {index%32, (index/32)%32, (index/32/32)%32};
    }
    uint32_t GetIndex(const glm::ivec3 pos) const {
        uint32_t index = pos.x + pos.z*32 + pos.y*32*32;
        if(index >= 32*32*32) index = 0;
        return index;
    }

    void GenMesh() {
        float vertices[] = {
             0.0f,  0.0f,  0.0f,
             0.0f,  0.0f, 32.0f,
             0.0f, 32.0f,  0.0f,
             0.0f, 32.0f, 32.0f,
            32.0f,  0.0f,  0.0f,
            32.0f,  0.0f, 32.0f,
            32.0f, 32.0f,  0.0f,
            32.0f, 32.0f, 32.0f
        };
        uint32_t indices[] = {
            0, 2, 1, 1, 2, 3,
            4, 5, 6, 6, 5, 7,
            0, 1, 4, 4, 1, 5,
            2, 6, 3, 3, 6, 7,
            0, 4, 2, 2, 4, 6,
            1, 3, 5, 5, 3, 7
        };
        
        m_VAO = UniFox::VertexArray::Create();
        UniFox::Ref<UniFox::VertexBuffer> vertexBuffer = UniFox::VertexBuffer::Create(vertices, sizeof(vertices));
        static UniFox::BufferLayout layout = {
            {UniFox::ShaderDataType::Float3, "a_Position"}
        };
        vertexBuffer->SetLayout(layout);
        m_VAO->AddVertexBuffer(vertexBuffer);
        UniFox::Ref<UniFox::IndexBuffer> indexBuffer = UniFox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VAO->SetIndexBuffer(indexBuffer);
    }
public:
    std::vector<Node> nodes;
    UniFox::Ref<UniFox::VertexArray> m_VAO;
    UniFox::Ref<UniFox::StorageBuffer> m_SBO;
    glm::mat4 m_Transform;
    glm::vec3 m_Position;
};