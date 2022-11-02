#include "hzpch.h"
#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Hazel
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) //���ĸ�,���ӳ���С,����ֻ�ṩ2Dƽ�����,�����ǵ�ͶӰ�������z��ļ���
		:m_ProjectionMartix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_pos(glm::vec3(0.0f,0.0f,0.0f)),m_rotation(0.0f)
	{
		HZ_PROFILE_FUNCTION();

		m_ViewMartix = glm::mat4(1.0f);
		m_ViewProjectionMartix = m_ProjectionMartix*m_ViewMartix; //
	}

	OrthographicCamera::~OrthographicCamera()
	{

	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		HZ_PROFILE_FUNCTION();	
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_pos);  //�����Լ�������ԭ��ȥ!
		//transform =  glm::rotate(transform, m_rotation, { 0.0f,0.0f,1.0f });
		//�ȼ� ...����ת������ƽ������������,transform �Ǳ任 ,�в��ɵ������λ�õ�һ������
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_pos)* glm::rotate(glm::mat4(1.0f),glm::radians(m_rotation), { 0.0f,0.0f,1.0f }); 
		//m_rot�ǽǶ�,����תΪ����

		m_ViewMartix = glm::inverse(transform);//����任
		m_ViewProjectionMartix = m_ProjectionMartix * m_ViewMartix;


	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		HZ_PROFILE_FUNCTION();

		m_ProjectionMartix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); 
		m_ViewProjectionMartix = m_ProjectionMartix * m_ViewMartix;
	}

}