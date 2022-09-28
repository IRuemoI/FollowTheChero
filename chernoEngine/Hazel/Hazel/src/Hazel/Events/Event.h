#pragma once

#include "Hazel/core.h"

#include <string>
#include <functional>


//now it is block .
//when something happened ,for delivery of the message,
//would stop other code
namespace Hazel
{
	enum class EventType //enum class Ϊö���ṩ��ö������������
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled
	};

	enum EventCategory //������,���ཫʹ��λ�������ж�
	{
		None = 0,
		EventCategoryApplication	=BIT(0),
		EventCategoryInput			=BIT(1),
		EventCategoryKeyboard		=BIT(2),
		EventCategoryMouse			=BIT(3),
		EventCategoryMouseButton	=BIT(4)


	};

	//�괴����Щ����ĺ���

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName()const override{ return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override{return category;}\

	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const=0;
		virtual const char* GetName() const =0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };

		inline bool IsInCategory(EventCategory eventcategory)
		{
			return GetCategoryFlags() & eventcategory; //λ������
		}
	protected:
		bool m_Handled = false;

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
				m_Event.m_Handled = func(*(T*)&m_event) //�������������¼����� ͬ���¼���ĺ���, �� event ���� ��Ӧevent�Ķ���/����,���event�������?��func����
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
