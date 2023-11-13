#ifndef SO_FILE_STEP
#define SO_FILE_STEP
#include "fileinfo.h"
namespace xhqm
{
	namespace info
	{
		class xhqmclass stepfile :
			public xhqm::info::fileinfo
		{
		protected:
		public:
			stepfile(std::string igespath = "");
			virtual xhqm::sign read();
			virtual xhqm::sign save();
		};
	}
}
#endif