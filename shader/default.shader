//::vertex::
#version 330 core
layout (location = 0) in vec3 _Pos;
layout (location = 1) in vec3 _Color;

out vec3 f_Color;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main() {
	f_Color = _Color;
	gl_Position =  proj *  view * model *  vec4(_Pos,1.f);
}

//::fragment::
#version 330 core
out vec4 FragColor;
in vec3 f_Color;

void main()
{	
	FragColor = vec4(f_Color,1.f);
}
