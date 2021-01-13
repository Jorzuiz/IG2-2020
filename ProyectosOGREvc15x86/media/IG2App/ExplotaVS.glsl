#version 330 core // archivo ExplotaVS.glsl
// VERTEX SHADER -> Geometry Shader -> Fragment Shader

uniform mat4 modelViewMat; 		// View*Model matrix
uniform mat4 normalMat; 		// = transpose(inverse(modelView))

in vec3 normal;
in vec4 vertex;
in vec2 uv0;

// Outs directos para el FS
out vec2 vUv0; 
out vec3 viewNormal; 	// coordenadas de la normal en  Xxx space
out vec3 viewVertex; 	// coordenadas de el vértice en Xxx space

void main() {

	viewVertex = vec3(modelViewMat * vertex);
	viewNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));

	vUv0 = uv0;		// Directo al Fragment Shader

	gl_Position = vertex;	
	// El GS tiene que transformar las coordenadas
	// de gl_Position al espacio de corte (modelViewProjMat)
}