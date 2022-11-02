#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel
{

	LayerStack::LayerStack()
	{
		

	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : m_layerstack  )
			delete layer ; //ɾ�����в� -> layerStackӵ��layer����Ȩ
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();
		m_layerstack.emplace(m_layerstack.begin()+m_LayerInsertIndex,layer); 
		m_LayerInsertIndex++;	
		//m_LayerInsert++,ԭλ�ò�����layer  ����: 1 2 3 4 _<-Insert ,over1,over2, 
		//���Ͳ� _ ���ǲ� ,���ǲ���Զ�����Ͳ�֮��,m_layerInsertָ���Ͳ����һ��,����ǰ��������Ͳ����

	}

	void LayerStack::PushOverLayer(Layer* layer)
	{

		m_layerstack.emplace_back(layer); //���ǲ�
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		//��Ҫ�Լ�ά����Щ�������Ͱ�....
		auto it = std::find(m_layerstack.begin(), m_layerstack.end(), layer);//����,����layerstackʧȥ������Ȩ,layer������֮ɾ��	
		if (it != m_layerstack.end()) 
		{
			m_layerstack.erase(it);
			m_LayerInsertIndex--;
		}

	}

	void LayerStack::PopOverLayer(Layer* layer)
	{
		auto it = std::find(m_layerstack.begin(), m_layerstack.end(), layer);
		if (it != m_layerstack.end()) // = .end() Ӧ����û�ҵ������
		{
			m_layerstack.erase(it);
		}
	}

}
