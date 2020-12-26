#version 330 core

// in del pixel shader
in vec2 vUv0;

// textura con la escena
uniform sampler2D RTT0;
//pueden haber mas

// out del pixel shader
out vec4 fFragColor;

// weight vector for luminance in sRGB
const vec3 WsRGB = vec3(0.2125, 0.7154, 0.0721);

void main() {
    vec4 sceneColor = texture(RTT0, vUv0);
    float lum = dot(vec3(sceneColor), WsRGB);

     // salida obligatoria
    fFragColor = vec4(lum, lum, lum, sceneColor.a);
}