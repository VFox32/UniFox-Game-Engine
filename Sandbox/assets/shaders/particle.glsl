#type compute
#version 430

layout(local_size_x = 256) in;

struct Particle {
    vec4 position;
    vec4 velocity;
    vec4 color;
    vec4 other; // x = lifetime, y = size, z = textureID
};

layout(std430, binding = 0) buffer Particles {
    Particle particles[];
};

uniform float u_DeltaTime;

uniform float u_Lifetime;
uniform float u_LifetimeVariance;
uniform vec3 u_Position;
uniform vec3 u_PositionVariance;
uniform vec3 u_Velocity;
uniform vec3 u_VelocityVariance;
uniform vec4 u_StartColor;
uniform vec4 u_EndColor;
uniform float u_Size;
uniform float u_SizeVariance;
float u_FadeOut;

float hash11(float p) {
    p = fract(p * .1031);
    p *= p + 33.33;
    p *= p + p;
    return fract(p);
}
vec3 hash31(float p) {
   vec3 p3 = fract(vec3(p) * vec3(.1031, .1030, .0973));
   p3 += dot(p3, p3.yzx+33.33);
   return fract((p3.xxy+p3.yzz)*p3.zyx); 
}

void main() {
    uint i = gl_GlobalInvocationID.x;

    particles[i].other.x -= u_DeltaTime;

    if (particles[i].other.x <= 0.0) {
        particles[i].position.xyz = u_Position + u_PositionVariance * (hash31(float(i)) * 2.0 - 1.0);
        particles[i].velocity.xyz = u_Velocity + u_VelocityVariance * (hash31(float(i)) * 2.0 - 1.0);

        particles[i].other.x = u_Lifetime + u_LifetimeVariance * (hash11(float(i)) * 2.0 - 1.0);
        particles[i].other.y = u_Size + u_SizeVariance * (hash11(float(i)) * 2.0 - 1.0);
        particles[i].other.z = floor(hash11(float(i)) * 2.99999999999 - 1.0);
    }

    particles[i].velocity.xyz += vec3(0, -1, 0) * u_DeltaTime;
    particles[i].position.xyz += particles[i].velocity.xyz * u_DeltaTime;

    float t = particles[i].other.x / u_Lifetime;
    t = clamp(t, 0.0, 1.0);
    particles[i].color = u_StartColor * t + u_EndColor * (1.0 - t);
    particles[i].color.w *= min(1.0f, particles[i].other.x / u_FadeOut);
}