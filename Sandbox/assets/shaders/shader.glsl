#type vertex
#version 330 core

layout(location = 0) in vec2 a_QuadPos;
layout(location = 1) in vec2 a_UV;

layout(location = 2) in vec3 a_InstancePos;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in float a_Size;
layout(location = 5) in int a_TexIndex;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

uniform mat4 u_View;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out float v_TexID;

void main() {
    v_Color = a_Color;
    v_TexCoord = a_UV;
    v_TexID = a_TexIndex;

    vec3 right = vec3(u_View[0][0], u_View[1][0], u_View[2][0]);
    vec3 up    = vec3(u_View[0][1], u_View[1][1], u_View[2][1]);

    vec3 worldPos =
        a_InstancePos +
        right * a_QuadPos.x * a_Size +
        up    * a_QuadPos.y * a_Size;

    gl_Position = u_ViewProjection * u_Transform * vec4(worldPos, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[2];

in vec4 v_Color;
in vec2 v_TexCoord;
flat in float v_TexID;

void main() {
    if(v_TexID < 0.0) {
        color = v_Color;
    } else {
        int index = int(v_TexID);
        color = texture(u_Textures[index], v_TexCoord) * v_Color;
    }
}