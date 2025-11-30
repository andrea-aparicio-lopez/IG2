#version 330 core
in vec4 vertex; // Posición del vértice
in vec3 normal; // Normal
in vec2 uv0; // Coordenadas de textura 0

uniform mat4 modelViewMat; // View*Model matrix (espacio de la vista)
uniform mat4 modelViewProjMat; // Projection*View*Model matrix (espacio clip)
uniform mat4 normalMat; // upper-left 3x3 transpose(inverse(modelView))
uniform vec3 lightAmbient; // Intensidad de la luz ambiente
uniform vec3 lightDiffuse; // Intensidad de la luz difusa
uniform vec4 lightPosition; // Datos de la fuente de luz en view space
                            // lightPosition.w == 0 -> directional light
                            // lightPosition.w == 1 -> positional light
uniform vec3 materialDiffuse; // Datos del material ¡Front=Back!

out vec2 vUv0; // Coordenadas de textura
out vec3 vFrontColor; // Color RGB de la iluminación de la cara Front (normal)
out vec3 vBackColor; // Color RGB de la iluminación de la cara Back (-normal)


float diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir = lightPosition.xyz;
    if (lightPosition.w == 1)
    lightDir = lightPosition.xyz - cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);
} 


void main() {
    vec3 ambient = lightAmbient * materialDiffuse;

    // Diffuse en view space (front)
    vec3 viewVertex = vec3(modelViewMat * vertex);
    vec3 viewNormal = normalize(normalMat * normal);
    vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
    vFrontColor = ambient + diffuse;


    vUv0 = uv0;
    vFrontColor = vec4(1,1,1,1);
    vBackColor = vec4(1,1,1,1);
    gl_Position = modelViewProjMat * vertex;
}