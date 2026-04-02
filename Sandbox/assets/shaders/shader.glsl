#type vertex
#version 430

layout(location = 0) in vec2 a_QuadPos;

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

void main()
{
    Particle p = particles[gl_InstanceID];

    v_Color = p.color;

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
out vec4 FragColor;

void main() {
    FragColor = v_Color;
}