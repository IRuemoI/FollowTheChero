
#include "Event.h"

#include "hzpch.h"
namespace Hazel
{

	class HAZEL_API KeyEvent:public Event  //����д�ĺ�������ᱻ��Ϊinline
	{
	public:
		
		inline int GetKeyCode() const{return m_keycode;}
		
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard ) // | �����㸳
	protected://�����������
		KeyEvent(int Event):m_keycode(Event){} //��������
		int m_keycode;
	};

	class HAZEL_API KeyPressedEvent :public KeyEvent //���°��� �ڰ�һ�κͳ�������Ҫ����ʱ��������������ֿ�
	{
		

	public:
		inline int GetRepeatcount() const { return m_repeatCount; }

		KeyPressedEvent(int keycode, int repeatc)
			:KeyEvent(keycode), m_repeatCount(repeatc) {}; //���û��๹�캯��
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << "(" << m_repeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_repeatCount;
	};

	class HAZEL_API KeyReleasedEvent :public KeyEvent //���°��� �ڰ�һ�κͳ�������Ҫ����ʱ��������������ֿ�
	{


	public:

		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}; //���û��๹�캯��

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};


}