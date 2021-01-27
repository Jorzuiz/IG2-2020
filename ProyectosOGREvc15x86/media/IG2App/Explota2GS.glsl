#version 330 core // archivo ExplotaGS.glsl
// Vertex Shader -> GEOMETRY SHADER -> Fragment Shader


layout (triangles) in; // Agrupa los vertices del VS en una primitiva de entrada
layout (triangle_strip, max_vertices = 3) out; // Primitiva de salida en forma de Triangle Strip
// al no declarar ninguna variable in, estamos suponiendo que el VS no tiene out,
// los vértices no traen asociados atributos, solo las coordenadas

uniform mat4 modelViewProjMat; // para pasar a Clip-Space
uniform mat4 modelViewMat; 		// View*Model matrix
uniform mat4 normalMat; 		// = transpose(inverse(modelView))
uniform float tiempo2pi;
uniform float tiempo;

const float Escala = 3;
const float VD = 5; // longitud del desplazamiento

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

	// Punto de Baricentro del triangulo
	vec3 bari = vec3(vertices[0] + vertices[1] + vertices[2])/3;
	// Normalizamos para hallar el vector
	bari = normalize(bari);

	for (int i=0; i<3; ++i) {

		vec3 normalize_vec = normalize(vec3(normalMat * vec4(gs_in[i].GS_viewNormal, 0.0)));
		
		// Nos desplazamos usando el baricentro, no la normal como antes
		vec3 posDes = vertices[i] * Escala + bari * VD * tiempo;

		//***************YAW********
		//mat3 yaw = (vec3(cos(tiempo2pi), -sin(tiempo2pi), 0),
		//vec3( sin(tiempo2pi), cos(tiempo2pi), 0), vec3(0,0,1));
		//vec3 posDes = posDes * yaw;
		vec3 yaw;
        yaw.x = posDes.x * (cos(tiempo2pi)) + posDes.z * (-sin(tiempo2pi));
        yaw.y = posDes.y;
        yaw.z = posDes.x * (sin(tiempo2pi)) + posDes.z * (cos(tiempo2pi));
		// Transformamos los vertices a Clip-Space (modelViewProjMat)
		gl_Position = modelViewProjMat * vec4(yaw, 1.0);



		gs_out.FS_vUv0 = gs_in[i].GS_vUv0; 
		gs_out.FS_viewNormal = normalize_vec; //normalize(yaw); //gs_in[i].GS_viewNormal;
		gs_out.FS_viewVertex = gs_in[i].GS_viewVertex;
		
		// Emitimos los vertices al resto de la tubería
		EmitVertex(); 

		// al no declarar ninguna variable out, los vertices del
		// triángulo emitido no llevan asociados atributos, solo las coordenadas
		}

	// Hace un Out de los vertices agrupados en la primitiva indicada
	EndPrimitive();	// Finaliza la emision de la primitiva

}