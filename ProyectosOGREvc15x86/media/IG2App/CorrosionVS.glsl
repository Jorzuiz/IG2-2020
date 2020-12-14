// archivo Ejemplo2VS.glsl
// Vertex Shader rasteriza

#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;	// Normal del plano que compone la cara
in vec2 uv0; // coordenadas de textura 0
//in vec3 eye; //coord.camera
//transformaciones
//uniform mat4 normalMat;// = transpose(inverse(modelView))
//vec3 nt = normalize(vec3(normalMat*vec4(normal,0.0)));
uniform mat4 modelViewProjMat;  // constante de programa
uniform mat4 ITWMatrix;
uniform mat4 WVMatrix;

out vec2 vUv0; 			// coordenadas de textura
//out vec3 vFrontColor;	
//out vec4 vBackColor;
out vec4 fFragColor;	
out vec3 vXxxNormal; // coordenadas de la normal en Xxx space
out vec3 vXxxVertex; // coordenadas del vértice en Xxx space


void main() {

	// Luz difusa
	//vec3 viewVertex = vec3(modelViewMat * vertex);
	//vec3 viewNormal = normalize(vec3(normalMat * vec4(normal, 0)));
	//vec3 diffuse = diff(viewVertex, viewNormal) *	lightDiffuse * materialDiffuse;

	vXxxVertex = vec3(ITWMatrix*vertex);// ITWMatrix * vertex;
    vXxxNormal = vec3(WVMatrix * vec4(normal,0.0));
	vUv0 = uv0; // se pasan las coordenadas de textura
	gl_Position = modelViewProjMat * vertex; //obligatorio
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


