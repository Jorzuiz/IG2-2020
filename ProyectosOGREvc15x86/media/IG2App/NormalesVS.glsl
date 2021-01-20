#version 330 core // archivo NormalesVS.glsl

in vec4 vertex;
in vec3 normal; 

// out del VS (gNormal) al GS (gNormal[])
// El GS agrupa las entradas en primitiva de triangulos; Vec3
out vec3 gNormal; 

void main() {

	// Normalize devuelve un Vec3
	gNormal = normalize(normal); 
	gl_Position = vertex;

} 
// out del VS (gl_Position) al GS (gl_in[].gl_Position)