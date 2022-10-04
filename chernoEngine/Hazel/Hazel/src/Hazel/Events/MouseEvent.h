#include "Event.h"
#include "hzpch.h"


namespace Hazel
{

	class HAZEL_API MouseMoveEvent :public Event
	{
	public:
		MouseMoveEvent(float x, float y)
			:m_x(x), m_y(y) {};
		inline int GetX() const { return m_x; }
		inline int GetY() const { return m_y; }
		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse); // | ��λ������

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << "x:" << m_x<< ",y:" << m_y;
			return ss.str();
		}
	protected://�����������
	private: 
		float m_x, m_y;
	};


	class HAZEL_API MouseScorllEvent :public Event
	{
	public:
		MouseScorllEvent(float offsetx,float offsety)
			:m_OffSetx(offsetx),m_OffSety(offsety) {};
		
		inline int GetXOffset() const { return m_OffSetx; }
		inline int GetYOffset() const { return m_OffSety; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScorllEvent: " << "x:" << m_OffSetx << ",y:" << m_OffSety;
			return ss.str();
		}


		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse); // | ��λ������


	private:
		float m_OffSetx, m_OffSety;
	};

	class HAZEL_API MouseButtonEvent:public Event  //����д�ĺ�������ᱻ��Ϊinline
	{
	public:

		inline int GetMouseButtonCode() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse) // | �����㸳
	protected://�����������
		MouseButtonEvent(int Event) : m_Button(Event) {} //��������
		int m_Button;
	};


	class HAZEL_API MouseButtonPressedEvent :public MouseButtonEvent 
	{
	public:

		MouseButtonPressedEvent(int keycode)
			:MouseButtonEvent(keycode) {}; //���û��๹�캯��

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed);

	};
	class HAZEL_API MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {}; //���û��๹�캯��

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased);

	};


}