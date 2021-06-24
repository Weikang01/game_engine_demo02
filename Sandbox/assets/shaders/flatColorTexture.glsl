#type vertex
#version 440 core
layout(location = 0) in vec3 position;

uniform mat4 viewProjMat;
uniform mat4 modelMat;

void main()
{
	gl_Position = viewProjMat * modelMat * vec4(position, 1.f);
}

#type fragment
#version 440 core

uniform vec4 color;

void main()
{
	gl_FragColor = color;
}