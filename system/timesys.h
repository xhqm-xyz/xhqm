#ifndef XHQM_TOOL_TIMESYS
#define XHQM_TOOL_TIMESYS
#include "../head.h"
#include <chrono>
#include <thread>
namespace xhqm
{
    struct xhqmclass nowtime
	{
		xhqm::integer year = 0;
		xhqm::integer month= 0;
		xhqm::integer mday = 0;
		xhqm::integer wday = 0;
		xhqm::integer hour = 0;
		xhqm::integer minu = 0;
		xhqm::integer seco = 0;
		xhqm::integer mill = 0;

		friend nowtime operator- (const nowtime& be, const nowtime& af);
	};

    class xhqmclass timesys
	{
	public:
		using nanos = std::chrono::nanoseconds; //纳
		using micro = std::chrono::microseconds;//微
		using milli = std::chrono::milliseconds;//毫
		using second = std::chrono::seconds;	//秒
		using minute = std::chrono::minutes;	//分
		using hour = std::chrono::hours;		//时
#if _HAS_CXX20
		using day = std::chrono::days;			//日
		using week = std::chrono::weeks;		//周
		using year = std::chrono::years;		//年
		using month = std::chrono::months;		//月
#endif // _HAS_CXX20

		template<class timetype = nanos>
		static xhqm::natural nowtime()//计算距离1970-1-1,00:00的时间长度
		{
			return std::chrono::time_point_cast<timetype>(std::chrono::system_clock::now()).time_since_epoch().count();
		}
		inline static xhqm::natural ntime() //UTC时间纳
		{
			//windows system_clock是100纳秒级别的(不同系统不一样)
			return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
		}
		inline static xhqm::natural utime() //UTC时间微
		{
			return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
		}
		inline static xhqm::natural mtime() //UTC时间毫
		{
			return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
		}
		inline static xhqm::natural stime() //UTC时间秒
		{
			return std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now()).time_since_epoch().count();
		}


		template<class timetype = nanos>
		static void sleep(xhqm::natural sleeptime)//暂停sleeptime时间
		{
			std::this_thread::sleep_for(timetype(sleeptime));
		}
		inline static void nsleep(xhqm::natural n)//暂停n纳
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(n));
		}
		inline static void usleep(xhqm::natural u)//暂停u微
		{
			std::this_thread::sleep_for(std::chrono::microseconds(u));
		}
		inline static void msleep(xhqm::natural m)//暂停m毫
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(m));
		}
		inline static void ssleep(xhqm::natural s)//暂停s秒
		{
			std::this_thread::sleep_for(std::chrono::seconds(s));
		}


		static xhqm::nowtime systemtime(xhqm::natural ms);//提取毫秒时间
		static xhqm::nowtime systemtime();//提取毫秒时间
		static std::string localtime(xhqm::natural ms);//系统时间
		static std::string localtime();//系统时间
	};

	class xhqmclass xtimer
	{
		xhqm::natural m_starns;
	public:
		xtimer() { xuptimer(); };

		inline xhqm::natural xstarus() { return m_starns; }
		inline xhqm::natural xuptimer() { return m_starns = xhqm::timesys::ntime(); }
		inline xhqm::natural xruntime() { return xhqm::timesys::ntime() - m_starns; }
		inline xhqm::natural xutimes() { return xruntime() / 1000; }
		inline xhqm::natural xmtimes() { return xruntime() / 1000000; }
		inline xhqm::natural xstimes() { return xruntime() / 1000000000; }


		inline std::string starTime();
		inline std::string nowTime();
		inline std::string runTime();
	};

	inline namespace literals
	{
        std::string xhqmclass operator""_systemtime(unsigned long long ms);
	}
}
#endif
