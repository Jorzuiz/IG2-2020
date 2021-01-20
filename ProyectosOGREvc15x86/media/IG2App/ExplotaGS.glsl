#version 330 core // archivo ExplotaGS.glsl
// Vertex Shader -> GEOMETRY SHADER -> Fragment Shader


layout (triangles) in; // Agrupa los vertices del VS en una primitiva de entrada
layout (triangle_strip, max_vertices = 3) out; // Primitiva de salida en forma de Triangle Strip
// al no declarar ninguna variable in, estamos suponiendo que el VS no tiene out,
// los vértices no traen asociados atributos, solo las coordenadas

uniform mat4 modelViewProjMat; // para pasar a Clip-Space
uniform float SinTiempo;

const float VD = 50; // longitud del desplazamiento

in VS_OUT
{
	vec2 GS_vUv0; 
	vec3 GS_viewNormal;
	vec3 GS_viewVertex; 
} gs_in[];


out GS_OUT
{
	vec2 FS_vUv0; 
	vec3 FS_viewNormal;
	vec3 FS_viewVertex;
} gs_out;

// Cuando existe un GS, el VS agrupa los vertices en grupos basandose en la primitiva

void main() {
	// La primitiva es tirangulos asique tiene dimension 3
	vec3 vertices[3] = vec3[](	gl_in[0].gl_Position.xyz,
								gl_in[1].gl_Position.xyz,
								gl_in[2].gl_Position.xyz);

	// NormalVec coge 3 vertices y saca su normal
	vec3 cross_vec = cross((vertices[2]-vertices[1]), (vertices[0]-vertices[1]));
	vec3 normalize_vec = normalize(cross_vec);

	vec3 dir = normalize_vec * SinTiempo;

	for (int i=0; i<3; ++i) { 		// para emitir 3 vértices
		vec3 posDes = vertices[i] + dir * VD;
		// vértice desplazado (los 3 en la misma dirección)
		
		// Transformamos los vertices a Clip-Space (modelViewProjMat)
		gl_Position = modelViewProjMat * vec4(posDes, 1.0);
		
		gs_out.FS_vUv0 = gs_in[i].GS_vUv0; 
		gs_out.FS_viewNormal = gs_in[i].GS_viewNormal;
		gs_out.FS_viewVertex = gs_in[i].GS_viewVertex;

		// Emitimos los vertices al resto de la tubería
		EmitVertex(); 

		// al no declarar ninguna variable out, los vertices del
		// triángulo emitido no llevan asociados atributos, solo las coordenadas
		}

	// Hace un Out de los vertices agrupados en la primitiva indicada
	EndPrimitive();	// Finaliza la emision de la primitiva

}