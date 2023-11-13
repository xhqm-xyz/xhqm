#ifndef XHQM_SIGNALSLOTEVENT
#define XHQM_SIGNALSLOTEVENT
#include "../conception/event.h"
#include "../conception/exist.h"
namespace xhqm
{
	enum class signal_type
	{
		signal_auto = 0,//信号
		signal_direct = 1,//立即执行 本线程
		signal_queued = 2,//队列执行 异线程
		signal_waited = 3,//等待执行 异线程
	};
	namespace software
	{
		//函数地址纪录类
		struct xhqmclass _adress
		{
			void* m_function = nullptr;
			void* m_receiver = nullptr;
			std::thread::id m_belong_thread;

			_adress();
            _adress(void* function);
            _adress(void* receiver, void* function);

            template<class return_type, class ...values_type>
            _adress(return_type(*function)(values_type...))
                : m_belong_thread(std::this_thread::get_id())
            {
                m_receiver = nullptr;
                std::memcpy(&m_function, &function, sizeof(void*));
            }

			template<class object_type, class return_type, class ...values_type>
			_adress(object_type* receiver, return_type(object_type::* function)(values_type...))
				: m_belong_thread(std::this_thread::get_id())
			{
				m_receiver = receiver;
				std::memcpy(&m_function, &function, sizeof(void*));
			}

			template<class object_type, class return_type, class ...values_type>
			_adress(object_type* receiver, return_type(object_type::* function)(values_type...) const)
				: m_belong_thread(std::this_thread::get_id())
			{
				m_receiver = receiver;
				std::memcpy(&m_function, &function, sizeof(void*));
			}

			inline operator bool() const { return m_function != nullptr; }
			inline bool this_thread() const { return m_belong_thread == std::this_thread::get_id(); }
			inline bool operator==(const _adress& other) const { return other.m_receiver == m_receiver && other.m_function == m_function; }
		};
		//信号事件抽象类
		struct xhqmclass _signal : public xhqm::event
		{
			using signal_func = std::function<void()>;
			std::atomic<bool> is_exec = false;
			std::thread::id m_belong_thread;
			signal_type exec_type;
			signal_func exec_func;

			_signal();
			_signal(const _signal* copy);
			virtual event* copy() const { return new _signal(this); };

			inline bool this_exec() const { return is_exec.load(); }
			inline bool this_func() const { return exec_func == nullptr; }
			inline bool this_thread() const { return m_belong_thread == std::this_thread::get_id(); }
		};
		//信号处理类
		class xhqmclass except_signalslot_events
			: public xhqm::except_events<xhqm::software::_signal>
		{
		public:
			except_signalslot_events() {};
			virtual void except_event(xhqm::event* event);
		};
		//信号产生类
		class xhqmclass signal_event : public xhqm::software::_signal
		{
			using signal_func = typename xhqm::software::_signal::signal_func;
			signal_event(signal_func func, xhqm::signal_type type = signal_type::signal_auto);

			virtual event* copy() const {
				return new signal_event(exec_func, exec_type);
			};
		};
	};
}
#endif
