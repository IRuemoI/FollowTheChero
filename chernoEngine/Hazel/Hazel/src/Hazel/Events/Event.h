#pragma once

#include "Hazel/Core/Base.h"

#include "hzpch.h"



//now it is block .
//when something happened ,for delivery of the message,
//would stop other code
namespace Hazel
{
	enum class  EventType //enum class Ϊö���ṩ��ö������������
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,KeyTyped,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled
	};

	enum HAZEL_API EventCategory //������,���ཫʹ��λ�������ж�
	{
		None = 0,
		EventCategoryApplication = BIT(0),//1
		EventCategoryInput = BIT(1),//10
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)


	};

	//�괴����Щ����ĺ���

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName()const override{ return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override{return category;}\

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const=0;
		virtual const char* GetName() const =0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		bool Handled = false;

		inline bool IsInCategory(EventCategory eventcategory)
		{
			return GetCategoryFlags() & eventcategory; //λ������
		}

		

	};

	class  EventDispatcher //������
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>; //std::function ���������� ��װһ��bool����,(T&)�βεĺ���/lambda/α����,����ʹ����ģ��
	private:
		Event& m_event;
	
	public:
		EventDispatcher(Event& event)
			:m_event(event) {};//�������յ��¼�
		template <typename T>
		bool DisPatch(EventFn<T> func)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.Handled = func(*(T*)&m_event); //�������������¼����� ͬ���¼���ĺ���, �� event ���� ��Ӧevent�Ķ���/����,���event�������,�Ƿ��������?��func����
					return true;
			}
			return false;//����ʧ��
		};

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& a)
	{
		return os << a.ToString(); //tostring�Զ���
	}

}
