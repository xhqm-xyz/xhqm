#pragma once
#ifndef XHQM_SOFTWARE_LOG
#define XHQM_SOFTWARE_LOG
#include "../../head.h"
#include <mutex>
namespace xhqm
{
	class xhqmclass xlog {
	public:
		typedef std::string Tlog;
		typedef std::string Dlog;
		typedef std::pair<Tlog, Dlog> Olog;
		typedef std::vector<Olog> Alogs;
		xlog(std::string path, std::string sig = "@");
	public:
		void AddLog(Dlog info);
		inline Olog GetLog(size_t pos) { return m_logs[pos]; };
		inline Alogs GetLogs() { return m_logs; };
		inline void clear() { m_logs.clear(); }
		inline size_t size() { return m_logs.size(); }

		inline std::string GetSign() { return m_logsign; };
		inline std::string GetPath() { return m_logpath; };
		inline bool SaveLog() { return SaveLog(*this); };
	public:
		static bool SaveLog(const xlog& xlogs);
		static xlog* set(xlog* log);
		static xlog* get();
		static void del();
	protected:
		Alogs m_logs;
		std::mutex m_logmutex;
		std::string m_logsign = "";
		std::string m_logpath = "";
	};

	inline namespace literals
	{
		void xhqmclass operator""_xhqmlog(const char* log, std::size_t);
	}
}
#endif
