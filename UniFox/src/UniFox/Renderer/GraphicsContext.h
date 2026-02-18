#pragma once

namespace UniFox {
    class GraphicsContext {
    public:
        virtual void SwapBuffers() = 0;
        virtual void Init() = 0;
    };
}
