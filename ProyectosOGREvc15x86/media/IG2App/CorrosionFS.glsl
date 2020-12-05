// Archivo Ejemplo2FS.glsl
// Fragment Shader mezcla 2 texturas

#version 330 core

uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;

// luz ambiente uniform vec3 luzDiff; uniform vec3 luzDir;
uniform vec4 InColor;	// Colores de la parte interior
uniform vec4 OutColor; 	// Colores de la parte exterior
uniform float Flipping;

in vec3 vWvertex;
in vec3 vWnormal;
in vec2 vUv0; 			// out del vertex shader
out vec4 fFragColor; 	// out del fragment shader

void main() {

	vec4 color;
	
	vec3 corrosion = texture(texturaCorrosion, vUv0).rgb;	// Transforma a vec3
	vec3 metal = texture(texturaBumpy, vUv0).rgb;	// Transforma a vec3

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;
	// Color que queremos esliminar para hacerlo transparente
	if (corrosion.r > 0.6) { discard; }

	// Usa un color u otro en base a la parte que estemos mirando
	if (frontFacing) {
		color = OutColor * vec4(metal, 1.0); 
		normal = normalize(vWnormal);
	}
	else {
		color = InColor * vec4(1.0, 1.0, 0.0 , 1.0);
		normal = -normalize(vWnormal);
	}
	
	fFragColor = color; // out
}