#version 330 core // archivo ExplotaFS.glsl
// Vertex Shader -> Geometry Shader -> FRAGMENT SHADER

in vec2 vUv0;

out vec4 fFragColor;

uniform float Flipping;
uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;

void main() {

	vec4 color;

	vec3 corrosion = texture(texturaCorrosion, vUv0).rgb;
	vec3 metal = texture(texturaBumpy, vUv0).rgb;

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;

	if (frontFacing) 
	{	color = vec4(metal, 1.0);  }
	else 
	{	color = vec4(corrosion, 1.0);	}

	fFragColor = color;
	//fFragColor = vec4(0.5, 0.5, 0.5, 1.0);
}