#type vertex
#version 330 core

layout(location = 0) in vec3 a_Pos; //? v3?v4? ������,��󶼵���v4
layout(location = 1) in vec2 a_UVCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec2 v_UVCoord;

void main() //a? ��Ȼ��void main
{
	v_UVCoord = a_UVCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0); //gl_Position GLĬ����Ļ�ռ�λ�ò���	

}

#type fragment
#version 330 core

uniform sampler2D u_Texture; //2D�����������,int :slot

layout(location = 0) out vec4 color;
in vec2 v_UVCoord;

void main()
{
	color = texture(u_Texture, v_UVCoord);
}


