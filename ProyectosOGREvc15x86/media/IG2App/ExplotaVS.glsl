#version 330 core // archivo ExplotaVS.glsl
// VERTEX SHADER -> Geometry Shader -> Fragment Shader

in vec4 vertex;
in vec2 uv0;

out vec2 vUv0; 

void main() {

	vUv0 = uv0;		// Directo al Fragment Shader

	gl_Position = vertex;	
	// El GS tiene que transformar las coordenadas
	// de gl_Position al espacio de corte (modelViewProjMat)
}