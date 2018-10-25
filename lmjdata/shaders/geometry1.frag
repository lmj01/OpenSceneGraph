#version 330

layout (location=0) out vec4 fragData;

uniform sampler2D map1;
in vec4 gColor;
in vec3 Normal;
in vec2 TexCoord;

void main()
{
	vec4 texColor = texture(map1, TexCoord) * gColor;
	//vec4 texColor = vec4(1.0, 0.0, 0.0, 1.0);
	fragData = texColor;
}

