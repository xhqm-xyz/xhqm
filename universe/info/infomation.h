#ifndef XHQM_INFO_BASE
#define XHQM_INFO_BASE
#include "../../head.h"
#include "../../system/codesys.h"
namespace xhqm
{
	namespace info
	{
		struct xhqmclass infomation
		{
		protected:
			std::string name = "";
		public:
			infomation(std::string infoname = "");
			std::string infoname() const;
			void infoname(std::string infoname);

			virtual xhqm::sign read() = 0;
			virtual xhqm::sign save() = 0;
		};
	}
}
#endif

