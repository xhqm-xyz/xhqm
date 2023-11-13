#ifndef XHQM_PLUGIN
#define XHQM_PLUGIN
#include "../pattern/instance.h"

namespace xhqm
{
	template<class type> class plugin;

	//插件列表
	template<class type>
	class pluginlist
		: public std::vector<xhqm::plugin<type>*>
	{
	public:
		pluginlist() {};
		bool find(type* action)
		{
			if (!action) return false;
			for (auto& pluginit : (*this))
				if (pluginit->action == action)
					return true;
			return false;
		}
		void sub(xhqm::plugin<type>* plugin)
		{
			for (auto iter = this->begin(); iter != this->end(); ++iter)
			{
				if (plugin == (*iter))
				{
					this->erase(iter);
					return;
				}
			}
		}
	};


	//插件
	template<class type>
	class plugin
	{
		plugin(const plugin&) = delete;
		plugin(const plugin&&) = delete;
		std::mutex m_mutex;
	public:
		type* action = nullptr;

		void lock()
		{
			m_mutex.lock();
		}
		void unlock()
		{
			m_mutex.unlock();
		}
		plugin(type* act)
		{
			if (!xhqm::instance<xhqm::pluginlist<type>>::get().find(act))
			{
				xhqm::instance<xhqm::pluginlist<type>>::get().push_back(this);
				action = act;
			}
		}
		~plugin()
		{
			std::lock_guard lock(m_mutex);
			xhqm::instance<xhqm::pluginlist<type>>::get().sub(this);
			xhqm_delete(action);
		}


		static pluginlist<type> plugins()
		{
			return xhqm::instance<xhqm::pluginlist<type>>::get();
		}
	};
}
#endif