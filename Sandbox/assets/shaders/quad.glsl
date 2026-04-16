#type vertex
#version 430

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main() {
    v_TexCoord = a_TexCoord.xy;

    gl_Position = vec4(a_Position, 0.0, 1.0);
}

#type fragment
#version 430

out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D g_Position;
uniform sampler2D g_Normal;
uniform sampler2D g_Albedo;

void main() {
    FragColor = vec4(texture(g_Albedo, v_TexCoord).xyz, 1.0);
    FragColor.rgb *= clamp(dot(texture(g_Normal, v_TexCoord).xyz, normalize(vec3(1, 2, 3))), 0.1, 1.0);
}