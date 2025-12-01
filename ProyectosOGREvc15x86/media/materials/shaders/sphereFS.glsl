#version 330 core

in vec4 vVertex;
in vec3 vNormal;
in vec2 vUv0; // Coordenadas de textura

uniform sampler2D textura;
uniform float threshold;

uniform mat4 modelViewMat; // View*Model matrix (espacio de la vista)
uniform mat3 normalMat; // upper-left 3x3 transpose(inverse(modelView))
uniform vec3 lightAmbient; // Intensidad de la luz ambiente
uniform vec3 lightDiffuse; // Intensidad de la luz difusa
uniform vec4 lightPosition; // Datos de la fuente de luz en view space
                            // lightPosition.w == 0 -> directional light
                            // lightPosition.w == 1 -> positional light
uniform vec3 lightDirection;
uniform vec3 materialDiffuse; // Datos del material ¡Front=Back!

out vec4 fFragColor;


float diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir = lightPosition.xyz;
    if (lightPosition.w == 1)
    lightDir = lightPosition.xyz - cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);
} 


void main() {
    vec3 ambient = lightAmbient * materialDiffuse;

    // Diffuse en view space (front)
    vec3 viewVertex = vec3(modelViewMat * vVertex);
    vec3 viewNormal = normalize(normalMat * vNormal);
    vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
    vec3 vFrontColor = ambient + diffuse;

    // Diffuse en view space (back)
    diffuse = diff(viewVertex, -viewNormal) * lightDiffuse * materialDiffuse;
    vec3 vBackColor = ambient + diffuse;

    vec3 color = texture(textura, vUv0).rgb;
    if(color.r > threshold)
        discard;

    if (gl_FrontFacing)
        color = vFrontColor * color;
    else
        color = normalize(vVertex.rgb*lightDirection);

    fFragColor = vec4(color, 1.0);
}

