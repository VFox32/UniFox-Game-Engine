#include "ufpch.h"
#include "RenderCommand.h"

#include "UniFox/Platform/OpenGL/OpenGLRendererAPI.h"

namespace UniFox {
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}