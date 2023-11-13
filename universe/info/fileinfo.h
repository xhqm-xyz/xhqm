#ifndef XHQM_INFO_FILE
#define XHQM_INFO_FILE
#include "infomation.h"
#include "../../system/filesys.h"
namespace xhqm
{
	namespace info
	{
		struct xhqmclass fileinfo :
			public xhqm::info::infomation
		{
		protected:
			std::fstream file;
			std::string path = "";
		public:
			fileinfo(std::string filepath = "");
			~fileinfo();
			void filepath(std::string filepath);
			std::string filepath() const;
			std::string filename() const;
			std::string filesuff() const;

			bool is_good();
			void open(std::ios_base::openmode mode);
			void close();
			std::fstream& fstream();

			static std::size_t filesize(std::string path) {
				std::ifstream file(path, std::ios::binary | std::ios::ate);
				if (file.is_open()) {
					std::size_t fileSize = file.tellg();
					file.close();
					return fileSize;
				}
				return 0;
			}
		};
	}
}
#endif