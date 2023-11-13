#include "xcfg.h"
#include "../../pattern/instance.h"
#include "../../system/timesys.h"
#include "../../system/codesys.h"
#include "../../system/filesys.h"
namespace xhqm
{
	xcfg::xcfg(std::string path, std::string sig)
	{
		m_cfgsign = sig;
		m_cfgpath = path;
		ReadCfg();
	}

	xcfg::~xcfg()
	{
		SaveCfg();
	}

	xcfg::Tcfgs xcfg::Titles()
	{
		Tcfgs titles;
		for (auto& tit : m_cfgs) 
			titles.push_back(tit.first);
		return titles;
	}

	bool xcfg::ReadCfg(xcfg& xcfgs)
	{
		std::ifstream cfg(xcfgs.m_cfgpath, std::ios::in);
		if (cfg.is_open()) {

			std::size_t tlen = xcfgs.m_cfgsign.length() + 7ULL;
			std::string info = "";
			xcfgs.m_cfgs.clear();

			for (info = ""; !cfg.eof(); cfg >> info)
			{
				if (info.substr(0, tlen) == "starcfg" + xcfgs.m_cfgsign)
				{
					Tcfg title = info.substr(tlen, info.length() - tlen);
					xcfgs.m_cfgs[title] = Lcfgs();
					while(true) 
					{
						cfg >> info;
						if (info.substr(0, tlen) != "stopcfg" + xcfgs.m_cfgsign)
							xcfgs.m_cfgs[title].push_back(xhqm::codesys::split_string(info, ','));
						else break;
					} 
				}
			}

			cfg.close();
			return true;
		} return false;
	}

	bool xcfg::SaveCfg(const xcfg& xcfgs)
	{
		std::ofstream cfg(xcfgs.m_cfgpath, std::ios::out | std::ios::trunc);
		if (cfg.is_open()) {
			for (auto& tit : xcfgs.m_cfgs) {
				std::string star = "starcfg" + xcfgs.m_cfgsign + tit.first;
				std::string stop = "stopcfg" + xcfgs.m_cfgsign + tit.first;
				if (tit.second.size())
				{
					cfg << star << std::endl;
					for (auto& line : tit.second) {
						std::string info = "";
						for (auto& data : line)
							info +=  data + ",";
						info = info.substr(0, info.length() - 1);
						cfg << info << std::endl;
					} cfg << stop << std::endl;
				}
			} cfg.close();
			return true;
		} return false;
	}


	xcfg* xcfg::set(xcfg* cfg)
	{
		if (!xhqm::instance<xcfg*>::get())
			xhqm::instance<xcfg*>::get() = cfg;
		return xhqm::instance<xcfg*>::get();
	}
	xcfg* xcfg::get()
	{
		if (!xhqm::instance<xcfg*>::get())
		{
			auto path = xhqm::filesys::current_path();
			xhqm::instance<xcfg*>::get() = new xcfg(path + "/xhqm.cfg");
		}
		return xhqm::instance<xcfg*>::get();
	}
	void xcfg::del()
	{
		xhqm_delete(xhqm::instance<xcfg*>::get());
	}


	inline namespace literals
	{
		xhqm::xcfg::Lcfgs operator""_xhqmcfg(const char* tag, std::size_t)
		{
			return xhqm::xcfg::get()->Title(tag);
		}
	}
}


