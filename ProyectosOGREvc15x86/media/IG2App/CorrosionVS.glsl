// archivo Ejemplo2VS.glsl
// Vertex Shader rasteriza

#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
//in vec3 normal;	// Normal del plano que compone la cara
in vec2 uv0; // coordenadas de textura 0

out vec2 vUv0; 			// coordenadas de textura
//out vec3 vXxxNormal;	// coordenadas de la normal en Xxx space
//out vec3 vXxxVertex;	// coordenadas del vértice en Xxx space

uniform mat4 modelViewProjMat;  // constante de programa
//uniform mat4 modelViewMat; 		// View*Model matrix
//uniform mat4 normalMat; 		// = transpose(inverse(modelView))

void main() {

	// Luz difusa
	//vec3 viewVertex = vec3(modelViewMat * vertex);
	//vec3 viewNormal = normalize(vec3(normalMat * vec4(normal, 0)));
	//vec3 diffuse = diff(viewVertex, viewNormal) *	lightDiffuse * materialDiffuse;

	vUv0 = uv0; // se pasan las coordenadas de textura
	gl_Position = modelViewProjMat * vertex; //obligatorio
	// (Clipping coordinates)
}