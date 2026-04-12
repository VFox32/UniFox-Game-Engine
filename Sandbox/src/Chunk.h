#pragma once
#include "UniFox.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Chunk {
public:
    Chunk(glm::vec3 position) 
        : m_Position(position) {
        m_Transform = glm::translate(glm::mat4(1.0f), position);

        Generate();
        GenMesh();
    }

    void Generate() {
        for(int z = 0; z < 16; z++)
        for(int y = 0; y < 16; y++)
        for(int x = 0; x < 16; x++) {
            uint8_t type = 0;
            if(m_Position.y+(float)y < glm::sin((m_Position.x+(float)x)/4.0) + sin((m_Position.z+(float)z)/4.0) + 8.0f) {
                type = 1;
            }
            m_Blocks[x][y][z] = type;
        }
    }

    void GenMesh() {
        std::vector<float> vertices;
        std::vector<uint32_t> indices;

        uint32_t vertexOffset = 0;
        for(float z = 0.0f; z < 16.0f; z++)
        for(float y = 0.0f; y < 16.0f; y++)
        for(float x = 0.0f; x < 16.0f; x++) {
            uint8_t type = m_Blocks[(int)x][(int)y][(int)z];
            if(type == 0) continue;

            if(m_Blocks[(int)x][(int)y][(int)z + 1] == 0 || z == 15.0) {
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
            if(m_Blocks[(int)x][(int)y][(int)z - 1] == 0 || z == 0.0) {
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
            if(m_Blocks[(int)x][(int)y + 1][(int)z] == 0 || y == 15.0) {
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
            if(m_Blocks[(int)x][(int)y - 1][(int)z] == 0 || y == 0.0) {
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
            if(m_Blocks[(int)x + 1][(int)y][(int)z] == 0 || x == 15.0) {
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
            if(m_Blocks[(int)x - 1][(int)y][(int)z] == 0 || x == 0.0) {
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
    uint8_t m_Blocks[16][16][16];
    UniFox::Ref<UniFox::VertexArray> m_VAO;
    glm::mat4 m_Transform;
    glm::vec3 m_Position;
};