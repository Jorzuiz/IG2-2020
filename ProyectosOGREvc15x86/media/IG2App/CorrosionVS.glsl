// archivo Ejemplo2VS.glsl
// Vertex Shader rasteriza

#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;	// Normal del plano que compone la cara

in vec2 uv0; // coordenadas de textura 0

out vec3 vWvertex;
out vec3 vWnormal;

out vec2 vUv0; // out del vertex shader

uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 wMatrix;

void main() {

	vWvertex = vec3(wMatrix * vertex);
	vWnormal = mat3(wMatrix * normal);

	vUv0 = uv0; // se pasan las coordenadas de textura
	
	gl_Position = modelViewProjMat * vertex; //obligatorio
	// (Clipping coordinates)
}