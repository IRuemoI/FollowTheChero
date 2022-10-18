#include "Texture.h"
#include "vendor/stb_image/stb_image.h"//�������Ǵӹ����ļ�Ŀ¼sln��ʼ

Texture::Texture(const std::string& filepath)
	:m_rendererID(0),m_filePath(filepath),m_localBuffer(nullptr),m_height(0),m_weight(0),m_BPP(0)//order
{
	stbi_set_flip_vertically_on_load(1);//��ֱ��ת����,Ϊ�����������ش����½ǿ�ʼ������glҪ��
	//ȡ������������ʽ
	m_localBuffer = stbi_load(filepath.c_str(), &m_weight, &m_height, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D,m_rendererID));//ָ���洢�������ù��� ���������н�������
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//Parameteri:���� MIN_FILTER:��С������ GL_Linear:����
	//����2d����Ĳ���:��С��ʽ(������)Ϊ ����
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));//Parameteri:���� MAG_FILTER:�Ŵ������ GL_Linear:����
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_S:ˮƽ����,CLAMP:Ƕ��
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//Parameteri:���� WRAP_T:��ֱ����,CLAMP:Ƕ��
	//����õ�tex2D�����Լ������������͸�gl,�Կ�������Щ��Ϣ�����ռ� 
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,m_weight,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_localBuffer));//Parameteri:���� WRAP_T:��ֱ����,CLAMP:Ƕ��
	//���:0,
	//�ڲ���ʽ(gl_��ȡ����ķ�ʽ):GL_RGBA8(8bit/ͨ��) ,
	//��,
	//��,
	//�߿����ؿ��,
	//��ʽ(�������ݵ�ʵ�ʸ�ʽ),
	//ͨ�����ݵ�����:8bit/ͨ��->unsigned char :gl�Լ����Ը������ϲ�������ռ�
	//�������ݵ�ָ��(data�ᱻcopy���Կ�) ������ʱ�ǿ�

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_localBuffer)
		stbi_image_free(m_localBuffer);//�ͷ�



}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(unsigned int slot /*=0 */) const
{
	GLCall(glActiveTexture(GL_TEXTURE0+slot)); //ʹ��������1
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
