// Archivo Ejemplo2FS.glsl
// Fragment Shader mezcla 2 texturas

#version 330 core

uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;

uniform float Flipping;

in vec2 vUv0; 			// out del vertex shader
// luz ambiente uniform vec3 luzDiff; uniform vec3 luzDir;

in vec3 viewNormal;
in vec3 viewVertex; 	//v_position
uniform vec3 vFrontColor; 	// color rgb de la iluminación de la cara Front (normal)
uniform vec3 vBackColor; 	// color rgb de la iluminación de la cara Back (-normal)
// Luces
// Variables para la iluminación
//uniform vec3 lightAmbient; 		// intensidades de la luz
uniform vec3 lightDiffuse;
uniform vec3 materialDiffuse; 	// datos del material ¡Front=Back!

uniform vec4 lightPosition; 	// datos de la fuente de luz en view space
								// lightPosition.w == 0 -> Luz Direccional
								// lightPosition.w == 1 -> Luz Posicional
//uniform vec3 luzUnicaPosition; //u_lightpos
//uniform vec3 luzUnicaDifusa;
//in vec3 vFrontColor; // color de la iluminación interpolado
//in vec3 vBackColor; // color de la iluminación interpolado

out vec4 fFragColor; 	// out del fragment shader
//out vec3 normal;

//uniform sampler2D materialTex; // Front = Back
float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz;
	if(lightPosition.w == 1) {lightDir = (lightPosition.xyz - cVertex);}
	return max(dot(cNormal, normalize(lightDir)), 0.0);
	// dot: coseno ángulo
}

void main() {

	vec4 color;	// Color final a representar
	//vec3 normal; // normales finales direccion de refraccion de la luz
	//Colores de las texturas, una es la transparencia, la otra se representa	
	vec3 corrosion = texture(texturaCorrosion, vUv0).rgb; // Transforma a vec3
	vec3 metal = texture(texturaBumpy, vUv0).rgb;		  // Transforma a vec3

	//vec3 ambient = lightAmbient * materialDiffuse;
	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
	vec3 colorF = diffuse; // + specular + ambient

	diffuse =  diff(viewVertex, -viewNormal) * lightDiffuse * materialDiffuse;//
	vec3 colorB =  diffuse; // + specular ambient +
    //vec3 diffuse = diff * luzUnicaDifusa;
	bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;
	// Color que queremos esliminar para hacerlo transparente
	// En este caso es cualquier rojo sobre 0.6
	if (corrosion.r > 0.6) { discard; }

	// Usa un color u otro en base a la parte que estemos mirando
	if (frontFacing) {
		color = vec4(colorF, 1.0) * vec4(metal, 1.0) * vec4(vFrontColor, 1.0);  
		//normal = viewNormal; 
	}
	
	else {
		color = vec4(colorB, 1.0) * vec4(vBackColor, 1.0);
		//normal = -viewNormal;
	}
	
     
    //vec4 result = vec4(diffuse, 1.0);    
	//vec3 vectorlight = normalize(luzUnicaPosition - viewVertex);
	//float diff = max(dot(normal, vectorlight), 0.1);

    // salida
    fFragColor = color;// * diff;//vec4(result * color);
}