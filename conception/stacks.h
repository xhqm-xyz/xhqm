#ifndef XHQM_STACKS
#define XHQM_STACKS
#include "../head.h"
#include "../pattern/instance.h"
namespace xhqm
{
	//栈 先进后出
	template<class type>
	class stacks {
		std::list<type> m_stacks;
		std::mutex m_mutex;
	public:
		inline stacks() {};

		inline void set(type& dataref)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_stacks.emplace_back(dataref);
		}

		inline bool get(type& dataref)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_stacks.size())
			{
				dataref = m_stacks.back();
				m_stacks.pop_back();
				return true;
			}
			return false;
		}

		inline void get_if(std::function<bool(const type&)> fun, type& dataref)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_stacks.size())
			{
				if (fun(m_stacks.back()))
				{
					get(dataref);
				}
			}
		}

		inline void pop_if(std::function<bool(const type&)> fun)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_stacks.size())
			{
				if (fun(m_stacks.back()))
				{
					m_stacks.pop_back();
				}
			}	
		}

		static stacks& instance()
		{
			return xhqm::instance<stacks>::get();
		};

	};
}
#endif

