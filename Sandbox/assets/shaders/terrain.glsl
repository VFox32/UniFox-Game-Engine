#type vertex
#version 430

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main() {
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
    v_Normal = vec3(0);
    v_TexCoord = vec2(0);

    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 430

struct Node {
    uint a;
    uint b;
};

layout(std430, binding = 0) buffer Octree {
    Node nodes[];
};

layout(location = 0) out vec4 g_Position;
layout(location = 1) out vec4 g_Normal;
layout(location = 2) out vec4 g_Albedo;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec3 u_Position;
uniform sampler2D u_Texture;

uniform vec3 u_ChunkPos;

void main() {
    vec3 rayPos = u_Position - u_ChunkPos;
    vec3 rayDir = normalize(v_Position - u_Position);

    vec3 boxMin = vec3(0.0);
    vec3 boxMax = boxMin + vec3(32.0);
    vec3 invDir = 1.0 / rayDir;
    vec3 t0 = (boxMin - rayPos) * invDir;
    vec3 t1 = (boxMax - rayPos) * invDir;
    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);
    float tEnter = max(max(tmin.x, tmin.y), tmin.z);
    float tExit  = min(min(tmax.x, tmax.y), tmax.z);
    if (tExit < max(tEnter, 0.0)) {
        discard;
    }
    float tStart = max(tEnter, 0.0);
    rayPos = rayPos + rayDir * tStart;
    rayPos += rayDir * 0.0001;

    ivec3 voxelPos = ivec3(floor(rayPos));
    ivec3 rayStep = ivec3(sign(rayDir));
    vec3 iRayDir = 1.0 / max(abs(rayDir), vec3(1e-8));
    vec3 rayDelta = abs(1.0 / rayDir);
    vec3 nextBoundary = vec3(voxelPos) + vec3(rayStep) * 0.5 + 0.5;
    vec3 tMax;// = (nextBoundary - rayPos) * iRayDir;
    tMax.x = ((voxelPos.x + (rayStep.x > 0 ? 1.0 : 0.0)) - rayPos.x) * invDir.x;
    tMax.y = ((voxelPos.y + (rayStep.y > 0 ? 1.0 : 0.0)) - rayPos.y) * invDir.y;
    tMax.z = ((voxelPos.z + (rayStep.z > 0 ? 1.0 : 0.0)) - rayPos.z) * invDir.z;

    vec3 prev;
    for(float steps = 0.0; steps < 128.0; steps++) {
        if(voxelPos.x < 0 || voxelPos.x >= 32 ||
           voxelPos.y < 0 || voxelPos.y >= 32 ||
           voxelPos.z < 0 || voxelPos.z >= 32) {
            discard;
        }

        int i = voxelPos.x + voxelPos.y*32 + voxelPos.z*32*32;
        if(nodes[i].b != 0u) {
            tMax = prev;
            float tHit = min(tMax.x, min(tMax.y, tMax.z));
            vec3 hitPos = rayPos + rayDir * tHit;

            vec3 normal = vec3(0.0);
            vec2 uv;
            if (tMax.x < tMax.y && tMax.x < tMax.z) {
                //normal = vec3(-rayStep.x, 0, 0);
                normal = vec3(sign(tMax.y), 0.0, 0.0);
                uv = hitPos.yz;
            } else if (tMax.y < tMax.z) {
                //normal = vec3(0, -rayStep.y, 0);
                normal = vec3(0.0, sign(tMax.y), 0.0);
                uv = hitPos.xz;
            } else {
                //normal = vec3(0, 0, -rayStep.z);
                normal = vec3(0.0, 0.0, sign(tMax.z));
                uv = hitPos.xy;
            }

            g_Position = vec4(hitPos, 0.0);
            g_Normal = vec4(normal, 0.0);
            g_Albedo = vec4(texture(u_Texture, uv).xyz, 1.0);// * dot(normal, normalize(vec3(1, 2, 3)));
            return;
        }
        
        prev = tMax;
        if (tMax.x < tMax.y) {
            if (tMax.x < tMax.z) {
                voxelPos.x += rayStep.x;
                tMax.x += rayDelta.x;
            } else {
                voxelPos.z += rayStep.z;
                tMax.z += rayDelta.z;
            }
        } else {
            if (tMax.y < tMax.z) {
                voxelPos.y += rayStep.y;
                tMax.y += rayDelta.y;
            } else {
                voxelPos.z += rayStep.z;
                tMax.z += rayDelta.z;
            }
        }
    }
    discard;
}