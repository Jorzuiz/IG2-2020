#version 330 core // archivo ExplotaVS.glsl
// VERTEX SHADER -> Geometry Shader -> Fragment Shader

uniform mat4 modelViewMat; 		// View*Model matrix
uniform mat4 normalMat; 		// = transpose(inverse(modelView))

in vec3 normal;
in vec4 vertex;
in vec2 uv0;

// No podemos pasarlo directamente al FS
// Y el GS no lo admite a menos que no esté agrupado en un array 
out VS_OUT{
	vec2 GS_vUv0; 
	vec3 GS_viewNormal; 	// coordenadas de la normal en  Xxx space
	vec3 GS_viewVertex; 	// coordenadas de el vértice en Xxx space
} vs_out;

void main() {

	vs_out.GS_viewVertex = vec3(modelViewMat * vertex);
	vs_out.GS_viewNormal = normalize(vec3(normalMat * vec4(normal, 0.0)));
	vs_out.GS_vUv0 = uv0;		// Directo al Fragment Shader
	
	gl_Position = vertex;	
	// El GS tiene que transformar las coordenadas
	// de gl_Position al espacio de corte (modelViewProjMat)
}