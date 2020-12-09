// Archivo Ejemplo2FS.glsl
// Fragment Shader mezcla 2 texturas

#version 330 core

uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;

// luz ambiente uniform vec3 luzDiff; uniform vec3 luzDir;
uniform vec4 InColor;	// Colores de la parte interior
uniform vec4 OutColor; 	// Colores de la parte exterior
uniform float Flipping;
// Luces
uniform vec3 luzUnicaPosition;
uniform vec3 luzUnicaDifusa;
//in vec3 vFrontColor; // color de la iluminación interpolado
//in vec3 vBackColor; // color de la iluminación interpolado

in vec3 vXxxNormal;
in vec3 vXxxVertex;
in vec2 vUv0; 			// out del vertex shader
out vec4 fFragColor; 	// out del fragment shader

//uniform sampler2D materialTex; // Front = Back

void main() {

	vec4 color;	// Color final a representar
	vec3 normal; // normales finales direccion de refraccion de la luz
	//Colores de las texturas, una es la transparencia, la otra se representa	
	vec3 corrosion = texture(texturaCorrosion, vUv0).rgb; // Transforma a vec3
	vec3 metal = texture(texturaBumpy, vUv0).rgb;		  // Transforma a vec3

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;
	// Color que queremos esliminar para hacerlo transparente
	// En este caso es cualquier rojo sobre 0.6
	if (corrosion.r > 0.6) { discard; }

	// Usa un color u otro en base a la parte que estemos mirando
	if (frontFacing) {
		color = OutColor * vec4(metal, 1.0); 
		normal = normalize(vXxxNormal); 
	}
	else {
		color = InColor * vec4(1.0, 1.0, 0.0 , 1.0);
		normal = -normalize(vXxxNormal);
	}
	float diff = max(dot(normal, luzUnicaPosition), 0.0);
    vec3 diffuse = diff * luzUnicaDifusa;
     
    vec4 result = vec4(diffuse, 1.0);    

    // salida
    fFragColor = vec4(result * color);
}