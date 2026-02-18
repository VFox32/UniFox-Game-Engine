#pragma once

#include "UniFox/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace UniFox {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void SwapBuffers() override;
        virtual void Init() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}