#pragma once
#ifndef XHQM_SOFTWARE_CFG
#define XHQM_SOFTWARE_CFG
#include "../../head.h"
#include <map>
namespace xhqm
{
	class xhqmclass xcfg {
	public:
		typedef std::string Dcfg;
		typedef std::string Tcfg;
		typedef std::vector<Dcfg> Lcfg;
		typedef std::vector<Tcfg> Tcfgs;
		typedef std::vector<Lcfg> Lcfgs;
		typedef std::map<Tcfg, Lcfgs> Acfgs;
		xcfg(std::string path, std::string sig = "@");
		~xcfg();
	public:
		Tcfgs Titles();
		inline Lcfgs&Title(Tcfg tit) { return m_cfgs[tit]; };
		inline std::string GetPath() { return m_cfgpath; };
		inline std::string GetSign() { return m_cfgsign; };
		inline bool ReadCfg() { return ReadCfg(*this); };
		inline bool SaveCfg() { return SaveCfg(*this); };
	public:
		static bool ReadCfg(xcfg& xlogs);
		static bool SaveCfg(const xcfg& xcfgs);
		static xcfg* set(xcfg* cfg);
		static xcfg* get();
		static void del();
	protected:
		Acfgs m_cfgs;
		std::string m_cfgsign;
		std::string m_cfgpath;
	};

	inline namespace literals
	{
		xhqm::xcfg::Lcfgs xhqmclass operator""_xhqmcfg(const char* tag, std::size_t);
	}
}
#endif