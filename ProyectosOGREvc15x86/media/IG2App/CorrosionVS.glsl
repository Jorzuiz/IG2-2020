// Vertex Shader de efecto de Corrosion
#version 330 core

// Valores por defecto
in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;	// Normal del plano que compone la cara
in vec2 uv0; // coordenadas de textura 0

// Matrices para Transformaciones de espacio de coordenadas
uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 modelViewProjMat;  // constante de programa
uniform mat4 normalMat; 		// = transpose(inverse(modelView))

// Valores para el Fragment Shader
out vec2 vUv0; 			// coordenadas de textura

out vec3 viewNormal; 	// coordenadas de la normal en  Xxx space
out vec3 viewVertex; 	// coordenadas de el vértice en Xxx space



void main() {
	// Luz Ambiente
	
	
	// valores en espacio de vista para el FS
	viewVertex = vec3(modelViewMat * vertex);					// Coordenadas para el FS
	viewNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));	// Valores para el FS

	// Luz difusa		
	// Calculos de iluminacion
	

	vUv0 = uv0; 										// se pasan las coordenadas de textura
	gl_Position = modelViewProjMat * vertex;	//, 0.0); 		// Posicion del Fragmento; La matriz determina el espacio de coordenadas
	// (Clipping coordinates)
}



//uniform mat4 modelViewMat; 		// View*Model matrix
//uniform vec3 lightAmbient;  	// intensidades de la luz
//uniform vec3 lightDiffuse;	// lightPosition.w == 0 -> directional light
//uniform vec4 lightPosition;	// lightPosition.w == 1 -> positional light
//uniform vec3 materialDiffuse; // datos del material ¡Front=Back!

//float diff(vec3 cVertex, vec3 cNormal)
//{
//	vec3 lightDir = lightPosition.xyz; // directional light ?
//	if (lightPosition.w == 1) // positional light ?
//	lightDir = lightPosition.xyz ‐ cVertex;
//	return max(dot(cNormal, normalize(lightDir)), 0.0);
//	
//	// ambient
//	vec3 ambient = lightAmbient * materialDiffuse;
//	// diffuse en view space
//	vec3 viewVertex = vec3(modelViewMat * vertex);
//	vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
//	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
//	vFrontColor = ambient + diffuse; // + specular
//	diffuse = diff(viewVertex, ‐viewNormal) * lightDiffuse * materialDiffuse;
//	vBackColor = ambient + diffuse; // + specular
//	
//	vUv0 = uv0;
//	gl_Position = modelViewProjMat * vertex;
//
//}


