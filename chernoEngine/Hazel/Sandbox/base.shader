#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Pos; //? v3?v4? ������,��󶼵���v4
layout(location = 1) in vec3 a_Color; //? v3?v4? ������,��󶼵���v4

out vec3 v_Position;	
out vec3 v_Color;	

void main() //a? ��Ȼ��void main
{
	v_Position = a_Pos;
	v_Color = a_Color;
	gl_Position= vec4(a_Pos, 1.0); //gl_Position GLĬ����Ļ�ռ�λ�ò���	

}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position; //������v_Positon�Զ���ֵ��???
in vec3 v_Color; //������v_Positon�Զ���ֵ��???

void main()
{
	color = vec4(v_Color*0.5+0.5, 1.0);
}


