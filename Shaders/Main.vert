#version 450 
in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;

uniform vec2 offset = vec2(0.0, 0.0);

void main()
{
	colorOut = colorIn;
	gl_Position = vec4(vertexIn.x + offset.x, vertexIn.y + offset.y, vertexIn.z, 1.0);
}

