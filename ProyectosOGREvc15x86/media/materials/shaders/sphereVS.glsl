#version 330 core
in vec4 vertex; // Posición del vértice
in vec3 normal; // Normal
in vec2 uv0; // Coordenadas de textura 0

uniform mat4 modelViewProjMat; // Projection*View*Model matrix (espacio clip)

out vec4 vVertex;
out vec3 vNormal;
out vec2 vUv0; // Coordenadas de textura

void main() {
    vVertex = vertex;
    vNormal = normal;
    vUv0 = uv0;
    gl_Position = modelViewProjMat * vertex;
}