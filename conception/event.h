#ifndef XHQM_EVENT
#define XHQM_EVENT
#include "queues.h"
namespace xhqm
{
	enum class event_type
	{
		no = 0,
		key,
		signal,
		timer,
		other
	};

	struct xhqmclass event
	{
		event_type type = event_type::no;
		virtual ~event() {};
		virtual event* copy() const = 0;
	};

	//时间事件抽象类
	struct xhqmclass timerevent : public event
	{
		timerevent() {
			type = event_type::timer;
		}
	};



	template<typename type>
	class except_events {
	protected:
		using event_type = type;
		xhqm::queues<xhqm::event*> events;
	public:
		event_type* get_event()
		{
			xhqm::event* e = nullptr; events.get(e);
			return dynamic_cast<event_type*>(e);
		}
		void pop_event(event_type*& e)
		{
			xhqm::event* _e = nullptr; events.get(_e);
			e = dynamic_cast<event_type*>(_e);
		}
		void ins_event(event_type* e)
		{
			xhqm::event* _e = e; events.set(_e);
		}

		virtual void except_event(xhqm::event* e) = 0;
	};
}
#endif

