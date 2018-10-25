#version 330

layout (location=0) in vec4 Position;
layout (location=1) in vec4 Color;
layout (location=2) in vec3 Normal;
layout (location=3) in vec2 TexCoord;

uniform mat3 osg_NormalMatrix;

out vec4 vColor;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
	gl_Position = Position;
	vColor = Color;
	vNormal = osg_NormalMatrix * Normal;
	vTexCoord = TexCoord;
}
