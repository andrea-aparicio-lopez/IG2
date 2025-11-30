#version 330 core
in vec4 vertex;
in vec2 uv0;

uniform mat4 modelViewProjMat;
uniform float t;
uniform float waveSpeed;
uniform float waveLength;
uniform vec4 center;

out vec2 vUv0;

    void main() {
        vec4 vertexCoord = vertex;
        float distanceCenter = distance(center, vertexCoord);

        vertexCoord.y += sin(vertexCoord.x + (t*waveSpeed)) * waveLength + sin(vertexCoord.z + (distanceCenter) + (t*waveSpeed)) * waveLength;

        vUv0 = uv0;
        gl_Position = modelViewProjMat * vertexCoord;
    }
