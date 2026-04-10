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

layout(std430, binding = 1) buffer Counter {
    int spawnCount;
};

uniform float u_Time;
uniform float u_DeltaTime;
uniform float u_ParticlesToSpawn;

uniform float u_Lifetime;
uniform float u_LifetimeVariance;

uniform vec3 u_Position;
uniform int u_PositionShape;
uniform vec3 u_PositionShapeDirection;
uniform float u_PositionSize1;
uniform float u_PositionSize2;

uniform vec3 u_VelocityDirection;
uniform int u_VelocityShape;
uniform vec3 u_VelocityMagnitude;
uniform float u_VelocitySize1;
uniform float u_VelocitySize2;

uniform vec4 u_StartColor;
uniform vec4 u_EndColor;

uniform float u_Size;
uniform float u_SizeVariance;

uniform float u_FadeOut;

uint murmurHash11(uint src) {
    const uint M = 0x5bd1e995u;
    uint h = 1190494759u;
    src *= M; src ^= src>>24u; src *= M;
    h *= M; h ^= src;
    h ^= h>>13u; h *= M; h ^= h>>15u;
    return h;
}
float hash11(float src) {
    uint h = murmurHash11(floatBitsToUint(src));
    return uintBitsToFloat(h & 0x007fffffu | 0x3f800000u) - 1.0;
}
uvec2 murmurHash21(uint src) {
    const uint M = 0x5bd1e995u;
    uvec2 h = uvec2(1190494759u, 2147483647u);
    src *= M; src ^= src>>24u; src *= M;
    h *= M; h ^= src;
    h ^= h>>13u; h *= M; h ^= h>>15u;
    return h;
}
vec2 hash21(float src) {
    uvec2 h = murmurHash21(floatBitsToUint(src));
    return uintBitsToFloat(h & 0x007fffffu | 0x3f800000u) - 1.0;
}
uvec3 murmurHash31(uint src) {
    const uint M = 0x5bd1e995u;
    uvec3 h = uvec3(1190494759u, 2147483647u, 3559788179u);
    src *= M; src ^= src>>24u; src *= M;
    h *= M; h ^= src;
    h ^= h>>13u; h *= M; h ^= h>>15u;
    return h;
}
vec3 hash31(float src) {
    uvec3 h = murmurHash31(floatBitsToUint(src));
    return uintBitsToFloat(h & 0x007fffffu | 0x3f800000u) - 1.0;
}

vec3 randDir(float seed) {
    vec2 r = hash21(seed);

    float theta = r.x * 6.283185;
    float phi = acos(r.y * 2.0 - 1.0);

    float radius = sin(phi);
    return vec3(
        radius * cos(theta),
        radius * sin(theta),
        cos(phi)
    );
}

vec3 randDisk() {
    return vec3(0);
}

vec3 randSphere(float seed, float sizeIn, float sizeOut) {
    float w = hash11(seed + 2.345);
    float r = pow(
        mix(pow(sizeIn, 3.0), pow(sizeOut, 3.0), w),
        1.0 / 3.0
    );
    return randDir(seed) * r;
}

vec3 randBox(float seed) {
    return hash31(seed) * 2.0 - 1.0;
}

vec3 randCone(vec3 dir, float angle, float seed) {
    vec2 r = hash21(seed);

    float cosAngle = cos(angle);
    float z = mix(cosAngle, 1.0, r.x); // bias toward center
    float theta = r.y * 6.283185;

    float sinTheta = sqrt(1.0 - z*z);

    vec3 local = vec3(
        cos(theta) * sinTheta,
        sin(theta) * sinTheta,
        z
    );

    vec3 up = abs(dir.y) < 0.999 ? vec3(0,1,0) : vec3(1,0,0);
    vec3 right = normalize(cross(up, dir));
    vec3 forward = cross(dir, right);

    return normalize(
        local.x * right +
        local.y * forward +
        local.z * dir
    );
}

void main() {
    uint i = gl_GlobalInvocationID.x;
    //float seed = float(i) * 12.9898 + u_Time * 78.233;
    float seed = float(i) + u_Time;
    //seed = hash11(seed);

    if (particles[i].other.x <= 0.0) {
        int id = atomicAdd(spawnCount, 1);
        //if(float(id) < u_ParticlesToSpawn) {
            if(u_PositionShape == 0) {
                particles[i].position.xyz = u_Position;
            } else if(u_PositionShape == 1) {
                particles[i].position.xyz = u_Position + randSphere(seed+1.0, u_PositionSize1, u_PositionSize2);
            } else if(u_PositionShape == 2) {
                particles[i].position.xyz = u_Position + randBox(seed+1.0);
            }

            if(u_VelocityShape == 0) {
                particles[i].velocity.xyz = u_VelocityDirection * u_VelocityMagnitude;
            } else if(u_VelocityShape == 1) {
                particles[i].velocity.xyz = u_Position + randSphere(seed+1.0, u_VelocitySize1, u_VelocitySize2) * u_VelocityMagnitude;
            } else if(u_VelocityShape == 2) {
                particles[i].velocity.xyz = u_Position + randCone(u_VelocityDirection, u_VelocitySize1, seed) * u_VelocityMagnitude;
            } 

            particles[i].other.x = u_Lifetime + u_LifetimeVariance * ((hash11(seed+3.0) * 2.0 - 1.0));
            particles[i].other.y = u_Size + u_SizeVariance * ((hash11(seed+4.0) * 2.0 - 1.0));
            particles[i].other.z = floor(hash11(seed+5.0) * 2.99999999999 - 1.0);
        //}
    } else {
        particles[i].other.x -= u_DeltaTime;

        particles[i].velocity.xyz += vec3(0, -1, 0) * u_DeltaTime;
        particles[i].position.xyz += particles[i].velocity.xyz * u_DeltaTime;

        float t = particles[i].other.x / u_Lifetime;
        t = clamp(t, 0.0, 1.0);
        particles[i].color = vec4(1);
        particles[i].color = u_StartColor * t + u_EndColor * (1.0 - t);
        particles[i].color.w *= min(1.0f, particles[i].other.x / u_FadeOut);
    }
}