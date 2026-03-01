#include "ufpch.h"
#include "OpenGLContext.h"

#include "UniFox/Core/Core.h"
#include "UniFox/Core/Log.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

namespace UniFox {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle) {
            UF_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        UF_CORE_ASSERT(status, "Failed to initialize Glad!");

        UF_CORE_INFO("OpenGLRenderer: {0} {1} {1}", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}