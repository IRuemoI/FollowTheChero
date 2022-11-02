#pragma once


#include "Layer.h"


namespace Hazel
{
	class LayerStack
	{
	private:
		std::vector<Hazel::Layer*> m_layerstack;
		unsigned int m_LayerInsertIndex =0	; //����pinָ��,ά�����Ͳ�β���±�???���ڷ�������������Ⱦ����ĳ��Layer
		
	public:
		LayerStack();
		~LayerStack();

		////���Ͳ�(push) _ ���ǲ�(over) ,���ǲ���Զ�����Ͳ�֮��,m_layerInsertָ���Ͳ�ĩβ��λ,�������Ͳ����
		//���Ǵ�vector��һ��begin ��Ⱦ�� end
		void PushLayer(Layer* layer ); //�� layerInsertָ������λ��
		void PushOverLayer(Layer* layer );
		void PopLayer( Layer* layer );
		void PopOverLayer( Layer* layer );

		std::vector<Hazel::Layer*>::iterator begin() { return m_layerstack.begin(); }
		std::vector<Hazel::Layer*>::iterator end() { return m_layerstack.end(); }

	};
}



