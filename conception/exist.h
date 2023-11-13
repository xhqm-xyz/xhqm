#ifndef XHQM_EXIST
#define XHQM_EXIST
#include "../head.h"
#include <mutex>
#include <atomic>
#include <thread>
#include <functional>
namespace xhqm
{
	class xhqmclass exist
	{
		std::mutex m_mutex;
		std::thread m_thread;
		std::atomic<bool> m_star = false;
	public:
		bool is_enter()
		{
			return exist::m_star;
		}
		std::mutex& mutex()
		{
			return exist::m_mutex;
		}

		virtual void enter()
		{
			if (!exist::m_star)
			{
				if (exist::m_thread.joinable())
					exist::m_thread.join();
				exist::m_star = true;
				exist::m_thread = std::thread(&exist::runexist, this);
			}
		}
		virtual void leave()
		{
			if (exist::m_star)
			{
				exist::m_star = false;
				if (std::this_thread::get_id() != exist::m_thread.get_id())
				{
					if (exist::m_thread.joinable())
						exist::m_thread.join();
				}
			}
		}

		virtual ~exist()
		{
			exist::m_star = false;
			if (exist::m_thread.joinable())
				exist::m_thread.join();
		}
	protected:
		virtual void runexist()
		{
			doexcept();
			while (exist::m_star)
				runexcept();
			undoexcept();
		}//辅线程执行

		virtual void doexcept() = 0;//辅线程首次执行一次
		virtual void runexcept() = 0;//辅线程循环执行多次
		virtual void undoexcept() = 0;//辅线程末尾执行一次
	};

	template<typename exist_type>
	class xhqmclass exist_fun : public exist
	{
		std::function<void(exist_type*)> m_doexcept;
		std::function<void(exist_type*)> m_runexcept;
		std::function<void(exist_type*)> m_undoexcept;
	public:
		void doexcept(std::function<void(exist_type*)> fun) { m_doexcept = fun; };
		void runexcept(std::function<void(exist_type*)> fun) { m_runexcept = fun; };
		void undoexcept(std::function<void(exist_type*)> fun) { m_undoexcept = fun; };
	protected:
		virtual void doexcept() { if (m_doexcept) m_doexcept(this); };
		virtual void runexcept() { if (m_runexcept) m_runexcept(this); };
		virtual void undoexcept() { if (m_undoexcept) m_undoexcept(this); };
	};
}
#endif
