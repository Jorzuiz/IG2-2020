// archivo Ejemplo2VS.glsl
// Vertex Shader rasteriza

#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0

uniform mat4 modelViewProjMat; // constante de programa
uniform float SinTiempo;
uniform float ZF;
out vec2 vUv0; // out del vertex shader
out vec2 vUv1; // otro out de vertexSh
void main() {
	vUv0 = uv0; // se pasan las coordenadas de textura
	//vUv1 = ((uv0-0.5)*ZF) + 0.5; //Zoom fijo
	
	vUv1 = (uv0-0.5) * SinTiempo + 0.5; //Zoom animado
	gl_Position = modelViewProjMat * vertex; //obligatorio
	// (Clipping coordinates)
}