#type vertex
#version 440 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 TexCoord;

out vec3 pos;
out vec2 texCoord;
uniform mat4 viewProjMat;
uniform mat4 modelMat;

void main()
{
	gl_Position = viewProjMat * modelMat * vec4(position, 1.f);
	pos = position + vec3(.5f);
	texCoord = TexCoord;
}

#type fragment
#version 440 core

in vec3 pos;
in vec2 texCoord;
uniform sampler2D u_texture;

void main()
{
	gl_FragColor = texture(u_texture, texCoord);
}