#include "infomation.h"

namespace xhqm
{
	namespace info
	{
		infomation::infomation(std::string infoname)
			: name(infoname) { }

		std::string infomation::infoname() const {
			return name;
		}
		void infomation::infoname(std::string infoname) {
			name = infoname;
		}
	}
}
