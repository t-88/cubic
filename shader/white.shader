//::vertex::
#version 330 core
layout (location = 0) in vec3 _Pos;


uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main() {
	gl_Position =  proj *  view * model *  vec4(_Pos,1.f);
}

//::fragment::
#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.f,1.f,1.f,1.f);
}
