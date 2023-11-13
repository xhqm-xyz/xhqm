#ifndef XHQM_SOFTWARE_ACTION
#define XHQM_SOFTWARE_ACTION
#include "../conception/plugin.h"
#include "../conception/exist.h"
#include "mousekey_events.h"

namespace xhqm
{
	namespace software
	{
		struct window
		{
			void* m_window = nullptr;

			window() : m_window(nullptr) {};

			template<typename type>
			window(type* wind) : m_window(wind) {};

			template<typename type>
			operator type*() { return static_cast<type*>(m_window); }

			//template<typename type>
			//operator type&() { return *static_cast<type*>(m_window); }
		};

		//typedef void* window;
		typedef class xhqmclass context
		{
		protected:
			context();
		public:
			void* m_context = nullptr;
			xhqm::software::window m_window;
		public:
			std::mutex m_mutex;
		public:
			template<typename type>
			operator type* () { return static_cast<type*>(m_context); }
			template<typename type>
			operator const type* () const { return static_cast<type*>(m_context); }

			xhqm::software::window& window() { return m_window; };
			const xhqm::software::window& window() const { return m_window; };

			static context* get();
			static void release();
		}*contextptr;


        class xhqmclass action 
			: public xhqm::exist
			, public xhqm::software::except_mousekey_events
		{ 
		protected:
			std::string m_info;
			const std::string m_type;
			const std::string m_icon;
			const std::string m_name;
			const xhqm::natural m_priority;
			xhqm::software::window m_window;
			bool m_hide = false;//是否隐藏
			bool m_need = false;//是否常驻
			bool m_first = false;//首次执行
		public:
			action(std::string name, std::string icon, std::string type, xhqm::natural priority = 0);
            virtual ~action();
		public://功能特性
			bool hide();
			bool need();
			bool first();
			std::string name();
			std::string icon();
			std::string type();
			std::string info();
			xhqm::natural priority();
		public://创建窗口
			xhqm::software::window window();
			virtual xhqm::software::window initwind() { return m_window; };
			virtual xhqm::software::window delewind() { return m_window; };
		public://执行功能
			virtual void enter();
			virtual void leave();
		protected:
			virtual void doexcept();//辅线程首次执行一次
            virtual void runexcept();	//辅线程循环执行多次
			virtual void undoexcept();//辅线程末尾执行一次
		};
	}
}
#define resigtaction(classname) static xhqm::plugin<xhqm::software::action> action##classname(new classname());
#endif

