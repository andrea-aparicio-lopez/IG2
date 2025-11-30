#version 330 core

in vec2 vUv0; // Coordenadas de textura
in vec3 vFrontColor; // Color RGB de la iluminación de la cara Front (normal)
in vec3 vBackColor; // Color RGB de la iluminación de la cara Back (-normal)

uniform sampler2D textura;
uniform float threshold;

out vec4 fFragColor;

void main() {
    vec3 color = texture(textura, vUv0).rgb;
    if(color.r > threshold)
        discard;

    if (gl_FrontFacing)
        color = vFrontColor * color;
    else
        color = vBackColor * color; 

    fFragColor = vec4(color, 1.0);
}

