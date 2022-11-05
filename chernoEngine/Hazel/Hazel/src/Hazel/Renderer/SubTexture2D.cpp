#include "hzpch.h"
#include "SubTexture2D.h"


namespace Hazel
{

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) //min : ���� max:���� uv����
		:m_texture(texture)
	{
		m_textureCoord[0] = { min.x,min.y };
		m_textureCoord[1] = { max.x,min.y };
		m_textureCoord[2] = { max.x,max.y };
		m_textureCoord[3] = { min.x,max.y };
	}

	//cellsize: ͼ�������Ԫ���С,spritesize:��������cellΪ��λ�Ĵ�С  
	Ref<SubTexture2D> SubTexture2D::CreateFromCroods(const Ref<Texture2D>& texture, const glm::vec2& coord, const glm::vec2& cellsize ,const glm::vec2& spriteSize )
	{

		float sheedWidth = (float)texture->GetWidth(), sheedHeight = (float)texture->GetHeight();
		glm::vec2 min = { coord.x * cellsize.x / sheedWidth,coord.y * cellsize.y / sheedHeight };
		glm::vec2 max = { (coord.x + spriteSize.x) * cellsize.x / sheedWidth,(coord.y + spriteSize.y) * cellsize.y / sheedHeight };

		return CreateRef<SubTexture2D>(texture, min, max);

	}

}