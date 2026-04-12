#type vertex
#version 430

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main() {
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
    v_Normal = a_Normal;//mat3(transpose(inverse(u_Transform))) * a_Normal;
    v_TexCoord = a_TexCoord;

    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 430

layout(location = 0) out vec4 g_Position;
layout(location = 1) out vec4 g_Normal;
layout(location = 2) out vec4 g_Albedo;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
    g_Position = vec4(v_Position, 1.0);
    g_Normal = vec4(v_Normal, 1.0);
    g_Albedo = texture(u_Texture, v_TexCoord);
}