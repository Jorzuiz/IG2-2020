// Archivo Ejemplo2FS.glsl
// Fragment Shader mezcla 2 texturas

#version 330 core

uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform sampler2D texturaM; // -> unidades de textura (int)
uniform float BF; 			// blending factor
//uniform float intLuzAmb; 	// luz ambiente blanca

in vec2 vUv0; 			// viene del vertex shader
in vec2 vUv1;			// viene del vertex shader
out vec4 fFragColor; 	// out del fragment shader

void main() {

	vec3 colorL = vec3(texture(texturaL, vUv0)); // acceso a téxel
	vec3 colorM = vec3(texture(texturaM, vUv1)); // configuración!

	vec3 color = colorL * colorM * BF;//mix(colorL, colorM, BF);// * intLuzAmb;
				// mix -> (1‐BF).colorL + BF.colorM
	
	fFragColor = vec4(color, 1.0); // out
}