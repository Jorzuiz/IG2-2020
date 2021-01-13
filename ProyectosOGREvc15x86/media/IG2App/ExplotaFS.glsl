#version 330 core // archivo ExplotaFS.glsl
// Vertex Shader -> Geometry Shader -> FRAGMENT SHADER

uniform float Flipping;
uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;

uniform vec3 lightDiffuse;
uniform vec3 materialDiffuse;
uniform vec4 lightPosition;

in vec2 vUv0;
in vec3 viewNormal;
in vec3 viewVertex;

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz;
	if(lightPosition.w == 1) {lightDir = (lightPosition.xyz - cVertex);}
	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {

	vec4 color;

	vec3 corrosion = texture(texturaCorrosion, vUv0).rgb;
	vec3 metal = texture(texturaBumpy, vUv0).rgb;

	// Diffuse Front
	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
	vec3 colorF = diffuse; // + specular + ambient

	// Diffuse Back
	diffuse =  diff(viewVertex, -viewNormal) * lightDiffuse * materialDiffuse;
	vec3 colorB =  diffuse;

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;

	if (frontFacing) 
	{	color = vec4(metal, 1.0) * vec4(colorF, 1.0);  }
	else 
	{	color = vec4(corrosion, 1.0) * vec4(colorB, 1.0);	}

	fFragColor = color;
	//fFragColor = vec4(0.5, 0.5, 0.5, 1.0);
}