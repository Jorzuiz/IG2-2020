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
	
	// Sumarle al vertice el valor 0.5 y restarselo luego hace que 
	// la transformación de tamñano se centre en la imagen en vez de 
	// en su esquina de arriba a la derecha

	// SinTiempo es una onda que oscila entre -1 y 1
	// Dividirla entre 4 la hace socilar entre -0.25 y 0.25
	// Sumarla 0.75 la localiza en ese punto y hace que oscile entre 0.5 y 1.0
	vUv1 = ((uv0-0.5) *			// Esto centra el otrigen en elc entro de la imagen
	 ((SinTiempo / 4) + 0.75) 	// esto la escala en ese nuevo origen
	 + 0.5); 					// esto retorna el centro a la esquina
	 		
	gl_Position = modelViewProjMat * vertex; //obligatorio
	// (Clipping coordinates)
}