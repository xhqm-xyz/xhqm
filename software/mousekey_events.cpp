#include "mousekey_events.h"
namespace xhqm::software
{
	key_event::key_event(key_type k, bool d)
		: keyevent(d)
	{
		keyevent::key = k;
	}
	mouse_key::mouse_key(byte t, byte k, short nx, short ny)
		: mouseevent(nx, ny)
	{
		tag = t;
		mkey = k;
		key = key_type::mouse_key;
	}
	mouse_move::mouse_move(short ox, short oy, short nx, short ny)
		: mouseevent(nx, ny)
	{
		oldx = ox;
		oldy = oy;
		key = key_type::mouse_move;
	}
	mouse_wheel::mouse_wheel(short wx, short wy, short nx, short ny)
		: mouseevent(nx, ny)
	{
		wlx = wx;
		wly = wy;
		key = key_type::mouse_wheel;
	}

	void except_mousekey_events::except_event(xhqm::event* e)
	{
		if (!e) return;
		xhqm::software::_keyevent* ke = (xhqm::software::_keyevent*)e;
		switch (ke->_keyevent::key)
		{
		case xhqm::software::key_type::mouse_key: {
			except_mousekey((xhqm::software::mouse_key*)e);
		}break;
		case xhqm::software::key_type::mouse_move: {
			except_mousemove((xhqm::software::mouse_move*)e);
		}break;
		case xhqm::software::key_type::mouse_wheel: {
			except_mousewheel((xhqm::software::mouse_wheel*)e);
		}break;
		default: {
			except_keyevent((xhqm::software::key_event*)e);
		}break;
		}
	}
}
