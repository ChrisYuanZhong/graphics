#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 vertexColor;

uniform vec3 dominatingColor;
uniform float yFlip;
uniform vec3 scale;

out vec3 theColor;

void main()
{
	gl_Position = vec4(position * scale, 1.0);
	gl_Position.y = gl_Position.y * yFlip;
	theColor = dominatingColor;
	// Change the scale of the object
	//gl_Position.x = gl_Position.x * scale.x;
	//gl_Position.y = gl_Position.y * scale.y;
	//gl_Position.z = gl_Position.z * scale.z;
}