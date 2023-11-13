#include "signal.h"

namespace xhqm::signals
{
	void events::doexcept()
	{
	}
	void events::runexcept()
	{
		xhqm::software::_signal* signal = this->get_event();
		if (signal)
		{
			except_event(signal);
		}
	}
	void events::undoexcept()
	{
		xhqm::software::_signal* signal = this->get_event();
		while (signal)	//清理事件
		{
			except_event(signal);
			signal = get_event();
		}
	}

	void events::sand_signal(const xhqm::signals::event& event)
	{
		xhqm::software::_signal* signal = new xhqm::software::_signal(&event);

		if (signal->exec_type == signal_type::signal_auto)
		{
			if (signal->this_thread())
			{
				signal->exec_func();
				delete signal;
			}
			else
			{
				signal->exec_type = signal_type::signal_queued;
				xhqm::instance<xhqm::signals::events>::get().ins_event(signal);
			}
		}
		else if (signal->exec_type == signal_type::signal_direct)
		{
			signal->exec_func();
			delete signal;
		}
		else if (signal->exec_type == signal_type::signal_queued)
		{
			xhqm::instance<xhqm::signals::events>::get().ins_event(signal);
		}
		else if (signal->exec_type == signal_type::signal_waited)
		{
			xhqm::instance<xhqm::signals::events>::get().ins_event(signal);
			while (signal->this_exec() == false) { /*wait*/ };
			delete signal;
		}
	}

};
