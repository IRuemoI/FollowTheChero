#pragma once

namespace Hazel
{

	class GraphicsContext //��������,ʵ����platform��
	{
	public:
		virtual void Init()=0;
		virtual void SwapBuffers() =0;

	};


}

