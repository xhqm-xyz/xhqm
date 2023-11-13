#ifndef XHQM_OBSERVER
#define XHQM_OBSERVER
#include "../head.h"
#include "../software/signalslot_events.h"
namespace xhqm 
{
	template<class ...values_type> class subject;

	template<class ...values_type>
	class observer //观察者
	{
	protected:
		std::mutex m_mutex;
	public:
		observer() = default;
		observer(observer&&) = default;
		observer(const observer&) = delete;

		using subject = subject<values_type...>;

		inline void lock() { m_mutex.lock(); }

		inline void unlock() { m_mutex.unlock(); }

		inline void regist(subject* object) {
			if (object) {
				std::lock_guard lock(object->m_mutex);
				object->m_observers.push_back(this);
			}
		}

		inline void remove(subject* object) {
			if (object) {
				std::lock_guard lock(object->m_mutex);
				object->m_observers.remove_if([this](const observer*& select) { return this == select; });
			}
		}

		virtual void response(subject* object, values_type...values) = 0; //反应
	};

	template<class ...values_type>
	class subject //目标
	{
		friend class observer<values_type...>;
	protected:
		std::mutex m_mutex;
		std::list<observer<values_type...>*> m_observers;
	public:
		subject() = default;
		subject(subject&&) = default;
		subject(const subject&) = delete;

		inline void lock() { m_mutex.lock(); }

		inline void unlock() { m_mutex.unlock(); }

		virtual void notify(values_type...values)//通知
		{
			for (auto& server : m_observers)
			{
				server->response(this, values...);
			}
		}
	};

	template<class ...values_type>
	class notifier //通知者
	{
	protected:
		struct receiver
		{
			std::function<void(values_type...)> lambda;
			xhqm::software::_adress adress;
		};
		std::list<receiver> m_receivers;
	public:
		notifier() = default;
		notifier(notifier&&) = default;
		notifier(const notifier&) = default;

		inline void notify(values_type ...values)
		{
			for (auto& hander : m_receivers)
			{
				hander.lambda(values...);
			}
		}

		inline void operator() (values_type...values)
		{
			notify(std::forward<values_type>(values)...);
		}


		inline void regist(const std::function<void(values_type...)>& lambda, const xhqm::software::_adress& adress)
		{
			m_receivers.push_back(receiver{ lambda,adress });
		}

		//仿函数
		inline void regist(const std::function<void(values_type...)>& lambda)
		{
			regist(lambda, xhqm::software::_adress());
		}
		//普通函数
		template<class return_type>
		inline void regist(return_type(*function)(values_type...))
		{
			regist(function, xhqm::software::_adress(function));
		}
		//成员函数
		template<class object_type, class return_type>
		inline void regist_notconst(object_type* object, return_type(object_type::* function)(values_type...))
		{
			std::function<void(values_type...)> lambda = [=](values_type&&...values)
			{
				(object->*function)(std::forward<values_type>(values)...);
			};
			regist(lambda, xhqm::software::_adress(object, function));
		}
		template<class object_type, class return_type>
		inline void regist_hasconst(object_type* object, return_type(object_type::* function)(values_type...) const)
		{
			std::function<void(values_type...)> lambda = [=](values_type&&...values)
			{
				(object->*function)(std::forward<values_type>(values)...);
			};
			regist(lambda, xhqm::software::_adress(object, function));
		}
		template<class object_type, class return_type>
		inline void regist(object_type* object, return_type(object_type::* function)(values_type...))
		{
			regist_notconst<object_type, return_type>(object, function);
		}
		template<class object_type, class return_type>
		inline void regist(object_type* object, return_type(object_type::* function)(values_type...) const)
		{
			regist_hasconst<object_type, return_type>(object, function);
		}

		inline void remove()
		{
			m_receivers.clear();
		}

		//仿函数
		inline void remove(const std::function<void(values_type...)>& lambda)
		{
			m_receivers.remove_if([](const receiver& select)
				{
					return xhqm::software::_adress() == select.adress;
				});
		}
		//普通函数
		template<class return_type>
		inline void remove(return_type(*function)(values_type...))
		{
			xhqm::software::_adress adress(function);
			m_receivers.remove_if([adress](const receiver& select)
				{
					return adress == select.adress;
				});
		}
		//成员函数
		template<class object_type, class return_type>
		inline void remove_notconst(object_type* object, return_type(object_type::* function)(values_type...))
		{
			xhqm::software::_adress adress(object, function);
			m_receivers.remove_if([adress](const receiver& select)
				{
					return adress == select.adress;
				});
		}
		template<class object_type, class return_type>
		inline void remove_hasconst(object_type* object, return_type(object_type::* function)(values_type...) const)
		{
			xhqm::software::_adress adress(object, function);
			m_receivers.remove_if([adress](const receiver& select)
				{
					return adress == select.adress;
				});
		}
		template<class object_type, class return_type>
		inline void remove(object_type* object, return_type(object_type::* function)(values_type...))
		{
			remove_notconst<object_type, return_type>(object, function);
		}
		template<class object_type, class return_type>
		inline void remove(object_type* object, return_type(object_type::* function)(values_type...) const)
		{
			remove_hasconst<object_type, return_type>(object, function);
		}
	};
}
#endif

