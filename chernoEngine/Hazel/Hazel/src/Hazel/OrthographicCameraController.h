#pragma once
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel

{
	struct  OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};


	class OrthographicCameraController //it just help user control the camera ,and reduce the camera contains
	{
	public:
		OrthographicCameraController(float aspectratio, bool rotation = false);//aspectratio * 2 units  //���ݱȳ�2����λ
		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_orthographicCamera; };
		const OrthographicCamera& GetCamera() const  { return m_orthographicCamera; };

		void SetZoomLevel(float level) {
			m_zoomLevel = level; CalculateView();
		};
		float GetZoomLevel() {return m_zoomLevel ; };

		inline const OrthographicCameraBounds& GetBound() const { return m_bounds; };

		void OnResiz(float width,float height);
	private:


		bool onMouseScrolled(MouseScorllEvent& event);
		bool onMouseReleased(MouseButtonPressedEvent& event);
		bool onMousePressed(MouseButtonPressedEvent& event);

		bool onWindowResized(WindowsResizeEvent& event);

		void CalculateView();
		
	private:
		//��˵����˳�����ʼ��˳��һ����..

		float m_aspectratio;
		float m_zoomLevel = 1.0f;
		bool m_rotation;

		OrthographicCameraBounds m_bounds;
		OrthographicCamera m_orthographicCamera;

		glm::vec3 m_CameraPosition = {0.f,0.f,0.f};
		float m_CameraRotation =0.f;
		float m_CameraSpeed = 1.0f;
		float m_CameraRotationSpeed =90.0f;
		float m_zoomStepLength =0.2f;

	};

}

