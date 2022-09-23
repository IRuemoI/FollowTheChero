#pragma once

#include "renderer.h"

class Texture
{
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_weight, m_height,m_BPP;
public:
	Texture(const std::string& filepath);
	~Texture();
	void Bind(unsigned int slot =0 )const;//slot ������,�ִ������Կ�����32��������
	void Unbind() const;

	inline int GetWeight() const { return m_weight; }
	inline int GetHeight() const { return m_height; }
};

