#include "timesys.h"
#include <iomanip>
namespace xhqm
{
	nowtime operator-(const nowtime& be, const nowtime& af)
	{
		nowtime res;
		res.year = be.year - af.year;
		res.month = be.month - af.month;
		res.mday = be.mday - af.mday;
		res.wday = be.wday - af.wday;
		res.hour = be.hour - af.hour;
		res.minu = be.minu - af.minu;
		res.seco = be.seco - af.seco;
		res.mill = be.mill - af.mill;
		bool ne = false;
		ne = res.mill < 0;
		res.mill = ne ? res.mill + 1000 : res.mill;
		res.seco = ne ? res.seco - 1 : res.seco;
		ne = res.seco < 0;
		res.seco = ne ? res.seco + 60 : res.seco;
		res.minu = ne ? res.minu - 1 : res.minu;
		ne = res.minu < 0;
		res.minu = ne ? res.minu + 60 : res.minu;
		res.hour = ne ? res.hour - 1 : res.hour;
		ne = res.hour < 0;
		res.hour = ne ? res.hour + 24 : res.hour;
		res.mday = ne ? res.mday - 1 : res.mday;
		ne = res.mday < 0;
		res.mday = ne ? -1 : 0;//-1错误数据, 0不参与计算
		res.month = 0;//0不参与计算
		res.wday = 0;//0不参与计算
		res.year = 0;//0不参与计算
		return res;
	}

	xhqm::nowtime timesys::systemtime(xhqm::natural ms)
	{
		xhqm::nowtime xt;
		std::time_t nows = ms / 1000;
		std::time_t nowm = ms % 1000;
		std::tm* st = std::localtime(&nows);
		xt.year = st->tm_year + 1900ULL;
		xt.month = st->tm_mon + 1ULL;
		xt.mday = st->tm_mday;
		xt.wday = st->tm_wday;
		xt.hour = st->tm_hour;
		xt.minu = st->tm_min;
		xt.seco = st->tm_sec;
		xt.mill = nowm;
		return xt;
	}

	xhqm::nowtime timesys::systemtime()
	{
		return timesys::systemtime(timesys::mtime());
	}

	std::string timesys::localtime(xhqm::natural ms)
	{
		xhqm::nowtime time = timesys::systemtime(ms);
		return
			std::to_string(time.year) + "/" + std::to_string(time.month) + "/" + std::to_string(time.mday) + " " +
			std::to_string(time.hour) + ":" + std::to_string(time.minu) + ":" + std::to_string(time.seco);
	}

	std::string timesys::localtime()
	{
		xhqm::nowtime time = timesys::systemtime(timesys::mtime());
		return
			std::to_string(time.year) + "/" + std::to_string(time.month) + "/" + std::to_string(time.mday) + " " +
			std::to_string(time.hour) + ":" + std::to_string(time.minu) + ":" + std::to_string(time.seco);
	}

	std::string xtimer::starTime()
	{
		return xhqm::timesys::localtime(m_starns / 1000000);
	}
	std::string xtimer::nowTime()
	{
		return xhqm::timesys::localtime(xruntime() / 1000000);
	}
	std::string xtimer::runTime()
	{
		xhqm::nowtime run = xhqm::timesys::systemtime((xruntime() - m_starns) / 1000000);
		return std::to_string(run.hour) + ":" + std::to_string(run.minu) + ":" + std::to_string(run.seco) + "." + std::to_string(run.mill);
	}

	inline namespace literals
	{
        std::string operator""_systemtime(unsigned long long ms)
		{
			return xhqm::timesys::localtime(ms);
		}
	}

};
