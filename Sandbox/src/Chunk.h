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
    Chunk(glm::vec3 position) 
        : m_Position(position) {
        m_Transform = glm::translate(glm::mat4(1.0f), position);

        Generate();
        GenMesh();
    }

    void Generate() {
        PerlinNoise perlin(12345);
        for(int z = 0; z < 32; z++)
        for(int x = 0; x < 32; x++) {
            //float height = glm::sin((m_Position.x+(float)x)/4.0) + sin((m_Position.z+(float)z)/4.0) + 8.0f;
            float height = perlin.noise((x+m_Position.x)/32.0, (z+m_Position.z)/32.0) * 31.0;
            m_Occupied[x+z*32] = 0;
            for(int y = 0; y < 32; y++) {
                uint8_t type = 0;
                if(m_Position.y+(float)y < height) {
                    type = 1;
                    m_Occupied[x+z*32] |= (1 << y);
                }
                m_Blocks[GetIndex({x, y, z})] = type;
            }
        }
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
        std::vector<float> vertices;
        std::vector<uint32_t> indices;

        uint32_t vertexOffset = 0;
        for(float z = 0.0f; z < 32.0f; z++)
        for(float y = 0.0f; y < 32.0f; y++)
        for(float x = 0.0f; x < 32.0f; x++) {
            //uint8_t type = m_Blocks[GetIndex({x, y, z})];
            //if(type == 0) continue;
            bool filled = m_Occupied[(int)x+(int)z*32] & (1 << (int)y);
            if(!filled) continue;

            if(m_Blocks[GetIndex({x, y, z + 1})] == 0 || z == 31.0) {
                vertices.push_back(0.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);

                indices.push_back(vertexOffset + 0);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 3);
                vertexOffset += 4;
            }
            if(m_Blocks[GetIndex({x, y, z - 1})] == 0 || z == 0.0) {
                vertices.push_back(0.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);

                indices.push_back(vertexOffset + 0);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 3);
                vertexOffset += 4;
            }
            if(m_Blocks[GetIndex({x, y + 1, z})] == 0 || y == 31.0) {
                vertices.push_back(0.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);

                indices.push_back(vertexOffset + 0);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 3);
                vertexOffset += 4;
            }
            if(m_Blocks[GetIndex({x, y - 1, z})] == 0 || y == 0.0) {
                vertices.push_back(0.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(0.0f);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);

                indices.push_back(vertexOffset + 0);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 3);
                vertexOffset += 4;
            }
            if(m_Blocks[GetIndex({x + 1, y, z})] == 0 || x == 31.0) {
                vertices.push_back(1.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);

                indices.push_back(vertexOffset + 0);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 3);
                vertexOffset += 4;
            }
            if(m_Blocks[GetIndex({x - 1, y, z})] == 0 || x == 0.0) {
                vertices.push_back(0.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(0.0f + z);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(0.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(0.0f + x);
                vertices.push_back(1.0f + y);
                vertices.push_back(1.0f + z);
                vertices.push_back(-1.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);
                vertices.push_back(1.0f);

                indices.push_back(vertexOffset + 0);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 2);
                indices.push_back(vertexOffset + 1);
                indices.push_back(vertexOffset + 3);
                vertexOffset += 4;
            }
        }
        
        m_VAO = UniFox::VertexArray::Create();
        UniFox::Ref<UniFox::VertexBuffer> vertexBuffer = UniFox::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
        static UniFox::BufferLayout layout = {
            {UniFox::ShaderDataType::Float3, "a_Position"},
            {UniFox::ShaderDataType::Float3, "a_Normal"},
            {UniFox::ShaderDataType::Float2, "a_TexCoord"}
        };
        vertexBuffer->SetLayout(layout);
        m_VAO->AddVertexBuffer(vertexBuffer);
        UniFox::Ref<UniFox::IndexBuffer> indexBuffer = UniFox::IndexBuffer::Create(indices.data(), indices.size());
        m_VAO->SetIndexBuffer(indexBuffer);
    }
public:
    uint8_t m_Blocks[32 * 32 * 32];
    uint32_t m_Occupied[32*32];
    UniFox::Ref<UniFox::VertexArray> m_VAO;
    glm::mat4 m_Transform;
    glm::vec3 m_Position;
};