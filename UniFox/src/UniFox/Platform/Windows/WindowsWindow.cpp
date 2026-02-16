#include "ufpch.h"
#include "WindowsWindow.h"
#include "UniFox/Log.h"

#include "UniFox/Events/KeyEvent.h"
#include "UniFox/Events/MouseEvent.h"
#include "UniFox/Events/WindowEvent.h"
#include "UniFox/Events/ApplicationEvent.h"

namespace UniFox {
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) {
        UF_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window* Window::Create(const WindowProps& props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        ShutDown();
    }

    void WindowsWindow::Init(const WindowProps& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        UF_CORE_INFO("Creating Window \"{0}\" ({1}, {2})", props.Title, props.Width, props.Height);

        if(!s_GLFWInitialized) {
            int success = glfwInit();

            UF_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowMovedEvent event(xPos, yPos);
            data.EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (focused) {
                case 1: {
                    WindowFocusEvent event = WindowFocusEvent();
                    data.EventCallback(event);
                    break;
                }
                case 0: {
                    WindowUnfocusEvent event = WindowUnfocusEvent();
                    data.EventCallback(event);
                    break;
                }
            }
        });

        //glfwSetCursorEnterCallback
        //glfwSetWindowIconifyCallback
        //glfwSetWindowMaximizeCallback
        //glfwSetCharCallback
        //glfwSetCharModsCallback
        //glfwSetJoystickCallback
        //glfwSetWindowRefreshCallback

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseBUttonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    MouseButtonPressedEvent event(button, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::ShutDown() {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        if(enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const {
        return m_Data.VSync;
    }
}