#include "signalslot_events.h"
namespace xhqm::software
{
    _adress::_adress(void* receiver, void* function)
        : m_function(function) , m_receiver(receiver)
        , m_belong_thread(std::this_thread::get_id())
    {
    }
    _adress::_adress(void* function)
        : m_function(function) , m_receiver(nullptr)
        , m_belong_thread(std::this_thread::get_id())
    {
    }
    _adress::_adress()
        : m_function(nullptr) , m_receiver(nullptr)
        , m_belong_thread(std::this_thread::get_id())
	{
	}

	_signal::_signal()
		: m_belong_thread(std::this_thread::get_id())
		, exec_type(xhqm::signal_type::signal_auto)
		, exec_func(nullptr)
	{
		type = event_type::signal;
	}
	_signal::_signal(const _signal* copy)
		: m_belong_thread(copy->m_belong_thread)
		, exec_type(copy->exec_type)
		, exec_func(copy->exec_func)
	{
		is_exec = copy->is_exec.load();
		type = event_type::signal;
	}

	void except_signalslot_events::except_event(xhqm::event* event)
	{
		xhqm::software::_signal* signal = static_cast<xhqm::software::_signal*>(event);
		if (signal)
		{
			if (signal->exec_type == xhqm::signal_type::signal_waited)
			{
				signal->exec_func();
				signal->is_exec = true;
				return;
			}
			if (signal->exec_type == xhqm::signal_type::signal_queued)
			{
				signal->exec_func();
				delete signal;
				return;
			}
		}
	}

	signal_event::signal_event(signal_func func, signal_type type)
	{
		exec_func = func;
		exec_type = type;
	}
}
