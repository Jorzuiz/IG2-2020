#version 330 core // archivo ExplotaGS.glsl
// Vertex Shader -> GEOMETRY SHADER -> Fragment Shader


layout (triangles) in; // Agrupa los vertices del VS en una primitiva de entrada
layout (triangle_strip, max_vertices = 3) out; // Primitiva de salida en forma de Triangle Strip
// al no declarar ninguna variable in, estamos suponiendo que el VS no tiene out,
// los vértices no traen asociados atributos, solo las coordenadas

uniform mat4 modelViewProjMat; // para pasar a Clip-Space
const float VD = 1; // longitud del desplazamiento

vec3 normalVec(vec3 vertex[3]) {
	// Formula del libro
	vec3 U = vertex[1] - vertex[0];
	vec3 V = vertex[2] - vertex[0];

	float NormalX = (U.y * V.z) - (U.z * V.y);
	float NormalY = (U.z * V.x) - (U.x * V.z);
	float NormalZ = (U.x * V.y) - (U.y * V.x);

	return vec3(NormalX, NormalY, NormalZ);

} // vector normal al triángulo

// Cuando existe un GS, el VS agrupa los vertices en grupos basandose en la primitiva

void main() {
	// La primitiva es tirangulos asique tiene dimension 3
	vec3 vertices[3] = vec3[](gl_in[0].gl_Position.xyz,
		gl_in[1].gl_Position.xyz,
		gl_in[2].gl_Position.xyz);

	// NormalVec coge 3 vertices y saca su normal
	vec3 dir = normalVec (vertices); // para los 3 vértices

	for (int i=0; i<3; ++i) { 		// para emitir 3 vértices
		vec3 posDes = vertices[i] + dir * VD;
		// vértice desplazado (los 3 en la misma dirección)
		
		// Transformamos los vertices a Clip-Space (modelViewProjMat)
		gl_Position = modelViewProjMat * vec4(posDes, 1.0);
		
		// Emitimos los vertices al resto de la tubería
		EmitVertex(); 

		// al no declarar ninguna variable out, los vertices del
		// triángulo emitido no llevan asociados atributos, solo las coordenadas
		}

	// Hace un Out de los vertices agrupados en la primitiva indicada
	EndPrimitive();	// Finaliza la emision de la primitiva
}