#include "action.h"
namespace xhqm
{
	namespace software
	{
		context::context() {};
		context* context::get()
		{
			if (!xhqm::instance<context*>::get())
				xhqm::instance<context*>::get() = new context();
			return xhqm::instance<context*>::get();
		}

		void context::release()
		{
			if (xhqm::instance<context*>::get())
				delete xhqm::instance<context*>::get();
			xhqm::instance<context*>::get() = nullptr;
		}

		action::action(std::string name, std::string icon, std::string type, xhqm::natural priority)
            : m_name(name), m_icon(icon), m_type(type), m_priority(priority)
		{
			//m_window = nullptr;
			//m_context = nullptr;
			//m_hide = false;//是否隐藏
			//m_need = false;//是否常驻
			//m_first = false;//首次执行
		}
		action::~action()
		{
			std::cout << m_name << std::endl;
		}

		bool action::hide()
		{
			return m_hide;
		}
		bool action::need()
		{
			return m_need;
		}
		bool action::first()
		{
			return m_first;
		}
		std::string action::name()
		{
			return m_name;
		}
		std::string action::icon()
		{
			return m_icon;
		}
		std::string action::type()
		{
			return m_type;
		}
		std::string action::info()
		{
			return m_info;
		}
		xhqm::natural action::priority()
		{
			return m_priority;
		}
		xhqm::software::window action::window()
		{
			return m_window;
		}

		void action::enter()
		{
            xhqm::exist::enter();
		}
		void action::leave()
		{
            xhqm::exist::leave();
			xhqm::software::keyevent* e = get_event();
			while (e)	//清理事件
			{
                delete e;
				e = get_event();
			}
		}
		void action::doexcept()
		{
		}
		void action::runexcept()
		{
			xhqm::software::keyevent* e = get_event();
			if (e)
			{
				except_event(e);
				delete e;
			}
		}
		void action::undoexcept()
		{
		}
	}
}
