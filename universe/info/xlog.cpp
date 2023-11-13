#include "xlog.h"
#include "../../pattern/instance.h"
#include "../../system/timesys.h"
#include "../../system/codesys.h"
#include "../../system/filesys.h"
namespace xhqm
{
	xlog::xlog(std::string path, std::string sig)
	{
		m_logsign = sig;
		m_logpath = path;
	}

	void xlog::AddLog(Dlog info)
	{
		std::lock_guard<std::mutex> lock(m_logmutex);
		std::ofstream log(m_logpath, std::ios::out | std::ios::app);
		Tlog time = xhqm::timesys::localtime();
		m_logs.push_back(std::pair<Tlog, Dlog>(time, info));
		log << time << m_logsign << "\t" << info << std::endl;
		log.close();
	}

	bool xlog::SaveLog(const xlog& xlogs)
	{
		std::ofstream log(xlogs.m_logpath, std::ios::out | std::ios::trunc);
		if (log.is_open()) {
			for (auto& data : xlogs.m_logs)
				log << data.first << xlogs.m_logsign << data.second << std::endl;
			log.close();
			return true;
		}return false;
	}


	
	xlog* xlog::set(xlog* log)
	{
		if (!xhqm::instance<xlog*>::get()) 
			xhqm::instance<xlog*>::get() = log;
		return xhqm::instance<xlog*>::get();
	}
	xlog* xlog::get()
	{
		if (!xhqm::instance<xlog*>::get()) 
		{
			auto path = xhqm::filesys::current_path();
			xhqm::instance<xlog*>::get() = new xlog(path + "/xhqm.log");
		}
		return xhqm::instance<xlog*>::get();
	}
	void xlog::del()
	{
		xhqm_delete(xhqm::instance<xlog*>::get());
	}

	inline namespace literals
	{
		void operator""_xhqmlog(const char* log, std::size_t)
		{
			return xhqm::xlog::get()->AddLog(log);
		}
	}
}

