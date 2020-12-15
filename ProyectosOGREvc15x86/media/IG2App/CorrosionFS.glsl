// Archivo Ejemplo2FS.glsl
// Fragment Shader mezcla 2 texturas

#version 330 core

uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;

uniform float Flipping;

in vec2 vUv0; 			// out del vertex shader
// luz ambiente uniform vec3 luzDiff; uniform vec3 luzDir;
in vec3 vFrontColor; 	// Colores de la parte exterior (Difusa Normal aplicada)
in vec3 vBackColor;		// Colores de la parte interior (Difusa -Normal aplicada)
in vec3 viewNormal;
in vec3 viewVertex; 	//v_position

// Luces
//uniform vec3 luzUnicaPosition; //u_lightpos
//uniform vec3 luzUnicaDifusa;
//in vec3 vFrontColor; // color de la iluminación interpolado
//in vec3 vBackColor; // color de la iluminación interpolado

out vec4 fFragColor; 	// out del fragment shader
//out vec3 normal;

//uniform sampler2D materialTex; // Front = Back

void main() {

	vec4 color;	// Color final a representar
	//vec3 normal; // normales finales direccion de refraccion de la luz
	//Colores de las texturas, una es la transparencia, la otra se representa	
	vec3 corrosion = texture(texturaCorrosion, vUv0).rgb; // Transforma a vec3
	vec3 metal = texture(texturaBumpy, vUv0).rgb;		  // Transforma a vec3

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;
	// Color que queremos esliminar para hacerlo transparente
	// En este caso es cualquier rojo sobre 0.6
	if (corrosion.r > 0.6) { discard; }

	// Usa un color u otro en base a la parte que estemos mirando
	if (frontFacing) {
		color = vec4(vFrontColor, 1.0) * vec4(metal, 1.0);  
		//normal = viewNormal; 
	}
	
	else {
		color = vec4(vBackColor, 1.0) * vec4(1.0, 1.0, 0.0, 1.0);
		//normal = -viewNormal;
	}
	
    //vec3 diffuse = diff * luzUnicaDifusa;
     
    //vec4 result = vec4(diffuse, 1.0);    
	//vec3 vectorlight = normalize(luzUnicaPosition - viewVertex);
	//float diff = max(dot(normal, vectorlight), 0.1);

    // salida
    fFragColor = color;// * diff;//vec4(result * color);
}