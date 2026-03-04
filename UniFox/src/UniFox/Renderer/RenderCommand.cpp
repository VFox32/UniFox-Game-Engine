#include "ufpch.h"
#include "RenderCommand.h"

#include "UniFox/Platform/OpenGL/OpenGLRendererAPI.h"

namespace UniFox {
    Ref<RendererAPI> RenderCommand::s_RendererAPI = MakeRef<OpenGLRendererAPI>();
}