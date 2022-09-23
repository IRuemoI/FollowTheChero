#shader vertex
#version 330 core
//�ǵü���﷨!!!
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord; //for uv coordnate
//vec4:opengl��λ�þ���һ��vec4,û�취,������ֱ�Ӳ�����. 
//loaction ��Ӧ�������� position:Ϊ����������

uniform mat4 u_MVP;

out vec2 v_TexCoord; //in out ���
//Ϊ�˶��������Լ���ͬ��ɫ��֮���ͨ��(ʹ�ý�varying�Ķ���)
//�����������
void main()
{
	gl_Position = u_MVP*position;  //gl_Position������Դ�����Ļ�ռ�
	v_TexCoord = textCoord;
}
; //���,ǿ�и�ֵ

#shader fragment
#version 330 core  //ʹ�� glsl(opengl����)330version ,core:������ʹ�������÷���

in vec2 v_TexCoord; //���� v_TexCoord
//ͳһ����

uniform sampler2D u_Texture;//ȡ�����
uniform vec4 u_Color; //����û���õ�,ʵ����,��������ᱻɾ�����������Ҳ���

layout(location = 0) out vec4 color;   //vec4:opengl����ɫҲ��һ��vec4. 
void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord); 
	color = texColor;  //ָ����ɫ rgba
}
; //���