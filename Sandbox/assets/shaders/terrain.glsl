#type vertex
#version 430

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec3 v_Normal;

void main() {
    v_TexCoord = a_TexCoord;
    v_Normal = a_Normal;

    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 430

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;
uniform vec3 u_Sun;

void main() {
    color = texture(u_Texture, v_TexCoord);
    color.xyz *= clamp(dot(u_Sun, v_Normal), 0.1, 1.0);
}