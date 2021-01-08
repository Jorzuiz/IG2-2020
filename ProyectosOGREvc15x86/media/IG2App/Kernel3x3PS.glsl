
#version 330 core 
//(textura con ella misma desplazada)



in vec2 vUv0; // en [0, 1]
uniform sampler2D RTT0;
out vec4 fFragColor;
//const float OFFSET = 10.0; // desplazamiento

uniform float kernel[9];

void main() {

    ivec2 texSize = textureSize(RTT0, 0);
    float incS = 1.0 / float(texSize.s);
    float incT = 1.0 / float(texSize.t);

    vec2 incUV[9] = vec2[]( // incrementos para acceder a
    vec2(-incS,incT), // top‐left s=ancho t=alto
    vec2(0, incT), // top‐center
    vec2(incS, incT), // top‐right
    vec2(-incS, 0), // center‐left
    vec2(0, 0), // center‐center
    vec2(incS, 0), // center‐right
    vec2(-incS, -incT), // bottom‐left
    vec2(0, -incT), // bottom‐center
    vec2(incS, -incT)); // bottom‐right
    
    //vec4 texel = texture(RTT0, vUv0); // téxel en vUv0
    
    vec4 color = vec4(0.0);
    //solo util si kernel > 1
    //float total = 0;
    //for(int i=0;i<9;i++){
        //total+=kernel[i];
    //}

    for(int i=0;i<9;i++){ 
        vec2 uv0f = vUv0 + incUV[i];
        vec4 texelD = texture(RTT0,uv0f);
        color += texelD * (kernel[i]);//  (dividir kernel[i] / total);

    }
    

    //vec2 incOf = OFFSET / float(texSize.s); // desplazamiento
    //vec2 uvOf = vUv0 + vec2(incOf, 0); // uvOf.s en [0, 1+…] !?
    //vec4 texelD = texture(RTT0, uvOf); // téxel en uvOf !? ‐>
    //if(uvOf.s > 1) texelD = texel; // ‐> borde sin mezcla
    fFragColor = color;
}



