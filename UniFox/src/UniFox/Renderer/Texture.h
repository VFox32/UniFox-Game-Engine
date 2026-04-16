#pragma once

#include <string>

#include "UniFox/Core/Core.h"

namespace UniFox {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetDepth() const = 0;
        virtual unsigned int GetRendererID() const = 0;
        
        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture {
    public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, unsigned int format);
		static Ref<Texture2D> Create(const std::string& path);

        virtual void Resize(uint32_t width, uint32_t height) = 0;
    };

    class Texture3D : public Texture {
    public:
		static Ref<Texture3D> Create(uint32_t width, uint32_t height, uint32_t depth, unsigned int format);
		static Ref<Texture3D> Create(const std::string& path);

        virtual void Resize(uint32_t width, uint32_t height, uint32_t depth) = 0;
    };
}