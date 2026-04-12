#pragma once

#include "UniFox/Renderer/Buffer.h"

namespace UniFox {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertecies, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetData(float* vertecies, uint32_t size) override;

        virtual const BufferLayout& GetLayout() const override {
            return m_Layout;
        }

        virtual void SetLayout(const BufferLayout& layout) override {
            m_Layout = layout;
        }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetData(uint32_t* indices, uint32_t count) override;

        virtual uint32_t GetCount() const {return m_Count;}
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

    class OpenGLStorageBuffer : public StorageBuffer {
    public:
        OpenGLStorageBuffer(float* data, uint32_t size);
        virtual ~OpenGLStorageBuffer();

        virtual void Bind(unsigned int index) const override;
        virtual void Unbind() const override;
        virtual void SetData(float* data, uint32_t size) override;

        virtual const BufferLayout& GetLayout() const override {
            return m_Layout;
        }

        virtual void SetLayout(const BufferLayout& layout) override {
            m_Layout = layout;
        }
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        OpenGLFrameBuffer(uint32_t width, uint32_t height);
        virtual ~OpenGLFrameBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void Attach(const Ref<Texture2D> texture) override;
        virtual void Draw() override;
        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual Ref<Texture2D> GetColorAttachment(uint32_t index) const override {return m_ColorAttachments[index];}

        virtual bool IsComplete() const override;
    private:
        uint32_t m_RendererID;

        std::vector<Ref<Texture2D>> m_ColorAttachments;
        unsigned int m_RenderBuffer;
    };
}