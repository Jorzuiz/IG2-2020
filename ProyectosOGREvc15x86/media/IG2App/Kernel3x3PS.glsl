
#version 330 core 
//(textura con ella misma desplazada)



in vec2 vUv0; // en [0, 1]
uniform sampler2D RTT0;
out vec4 fFragColor;
const float OFFSET = 10.0; // desplazamiento

uniform float kernel[9];

void main() {
    

    vec4 texel = texture(RTT0, vUv0); // téxel en vUv0
    ivec2 texSize = textureSize(RTT0, 0); // dimensiones
    vec2 incOf = OFFSET / float(texSize.s); // desplazamiento
    vec2 uvOf = vUv0 + vec2(incOf, 0); // uvOf.s en [0, 1+…] !?
    vec4 texelD = texture(RTT0, uvOf); // téxel en uvOf !? ‐>
    if(uvOf.s > 1) texelD = texel; // ‐> borde sin mezcla
    fFragColor = mix(texel, texelD, 0.5);
}



