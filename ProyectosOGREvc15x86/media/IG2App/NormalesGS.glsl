#version 330 core // archivo NormalesGS.glsl

layout (triangles) in; 			// La entrada de variables se agrupa en triangulos
layout (line_strip, max_vertices = 6) out;	// La salida se agrupa en line strip
											// genera 3 líneas ‐> 3 primitivas cada una de 2 vértices

in vec3 gNormal[]; // 3 vectores normales provenientes del Vertex Shader agrupados en vec3

out vec3 vColor; 	// color para los vértices de la línea. 
					// Al declarar vColor out, cada vértice llevará asociado el color que contenga esta variable en el momento de emitirlo

const float SIZE = 50; // para la longitud de la línea

uniform mat4 modelViewProjMat;

void generateLine(int index) { // normal al vértice index (0, 1, 2)
	
	vColor = vec3 (1.0, 0.0, 0.0);	//gNormal[index];	// El color depende de la orientacion de la normal
	gl_Position = modelViewProjMat * gl_in[index].gl_Position;
	EmitVertex(); // 1er vértice de la línea con color

	vColor = vec3 (1.0, 1.0, 0.0); //gNormal[index]; // ¿color válido? ‐> …
	gl_Position = modelViewProjMat * (gl_in[index].gl_Position	+ vec4(gNormal[index],0) * SIZE);
	EmitVertex(); // 2º vértice de la línea con color y …

	EndPrimitive(); // línea formada por los 2 vértices emitidos
}

void main()
{
	// Repetimos el proceso por cada vertice
	for (int i=0; i<3; ++i)
		generateLine(i);

}