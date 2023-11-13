#ifndef XHQM_QUEUES
#define XHQM_QUEUES
#include <list>
#include "../pattern/instance.h"
namespace xhqm
{
	//队 先进先出
	template<class type>
	class queues {
		std::list<type> m_queues;
		std::mutex m_mutex;
	public:
		inline queues() {};

		inline void set(type& dataref)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queues.emplace_back(dataref);
		}

		inline bool get(type& dataref)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_queues.size())
			{
				dataref = m_queues.front();
				m_queues.pop_front();
				return true;
			}
			return false;
		}

		inline void get_if(std::function<bool(const type&)> fun, type& dataref)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_queues.size())
			{
				if (fun(m_queues.front()))
				{
					get(dataref);
				}
			}
		}

		inline void pop_if(std::function<bool(const type&)> fun)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_queues.size())
			{
				if (fun(m_queues.front()))
				{
					m_queues.pop_front();
				}
			}
		}

		static queues& instance()
		{
			return xhqm::instance<queues>::get();
		};

	};
}
#endif
