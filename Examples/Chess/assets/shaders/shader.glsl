#type vertex
#version 430

layout(location = 0) in vec2 a_QuadPos;
layout(location = 1) in vec2 a_TexCoord;

struct Particle {
    vec4 position;
    vec4 velocity;
    vec4 color;
    vec4 other; // x = lifetime, y = size, z = textureID
};

layout(std430, binding = 0) buffer Particles {
    Particle particles[];
};

uniform mat4 u_ViewProjection;
uniform mat4 u_View;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out float v_TexIndex;

void main() {
    Particle p = particles[gl_InstanceID];

    v_Color = p.color;
    v_TexIndex = p.other.z;
    v_TexCoord = a_TexCoord;

    vec3 right = normalize(vec3(u_View[0][0], u_View[1][0], u_View[2][0]));
    vec3 up    = normalize(vec3(u_View[0][1], u_View[1][1], u_View[2][1]));
    float size = p.other.y;

    vec3 worldPos =
        p.position.xyz +
        a_QuadPos.x * right * size +
        a_QuadPos.y * up * size;

    gl_Position = u_ViewProjection * vec4(worldPos, 1.0);
}

#type fragment
#version 430

in vec4 v_Color;
in vec2 v_TexCoord;
flat in float v_TexIndex;

out vec4 FragColor;

uniform sampler2D u_Textures[2];

void main() {
    if(v_TexIndex < 0.0)
        FragColor = v_Color;
    else
        FragColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord) * v_Color;
}