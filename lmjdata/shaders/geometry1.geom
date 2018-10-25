#version 330

layout(triangles) in;
layout(triangle_strip) out;
layout(max_vertices = 9) out;

uniform mat4 osg_ModelViewProjectionMatrix;

in vec4 vColor[];
in vec3 vNormal[];
in vec2 vTexCoord[];

out vec2 gTexCoord;
out vec4 gColor;
out vec3 gNormal;

void main()
{
	for (int i=0; i<gl_in.length(); i++) {
		gl_Position = osg_ModelViewProjectionMatrix * gl_in[i].gl_Position;
		gTexCoord = vTexCoord[i];
		gColor = vColor[i];
		gNormal = vNormal[i];
		EmitVertex();	
	}
	EndPrimitive();

	gl_Position = osg_ModelViewProjectionMatrix * gl_in[0].gl_Position;
	gTexCoord = vTexCoord[0];
	gColor = vColor[0];
	//gColor = vec4(1.0, 0.0, 0.0, 0.5);
	gNormal = vNormal[0];
	EmitVertex();

	gl_Position = osg_ModelViewProjectionMatrix * gl_in[2].gl_Position;
	gTexCoord = vTexCoord[2];
	gColor = vColor[2];
	//gColor = vec4(0.0, 1.0, 0.0, 0.5);
	gNormal = vNormal[2];
	EmitVertex();

        gl_Position = osg_ModelViewProjectionMatrix * vec4(1.0, 0.0, 0.0, 1.0);
	gTexCoord = vTexCoord[1];
	gColor = vColor[1];
	//gColor = vec4(0.0, 0.0, 1.0, 0.5);
	gNormal = vNormal[0];
	EmitVertex();
	
	EndPrimitive();
}	
	
