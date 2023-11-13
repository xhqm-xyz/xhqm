#include "fileinfo.h"
namespace xhqm
{
	namespace info
	{
		fileinfo::fileinfo(std::string filepath)
			: xhqm::info::infomation("")
		{
			fileinfo::filepath(filepath);
		}
		fileinfo::~fileinfo()
		{
			fileinfo::close();
		}

		void fileinfo::filepath(std::string filepath)
		{
			if (filepath == "") return;
			std::vector<std::string> list_0;
			std::vector<std::string> list_1 = xhqm::codesys::split_string(filepath, '\\');
			for (auto& path_1 : list_1)
			{
				std::vector<std::string> list_2 = xhqm::codesys::split_string(path_1, '/');
				list_0.insert(list_0.end(), list_2.begin(), list_2.end());
			}
			path = "";
			std::size_t size = list_0.size() - 1;
			for (std::size_t pos = 0; pos != size; ++pos)
			{
				path = path + list_0[pos] + "/";
			}
			name = list_0[size];
		}
		std::string fileinfo::filepath() const
		{
			return path + name;
		}
		std::string fileinfo::filename() const
		{
			std::vector<std::string> list;
			list = xhqm::codesys::split_string(name, '.');
			return (list.size() > 0) ? list[0] : name;
		}
		std::string fileinfo::filesuff() const
		{
			std::vector<std::string> list;
			list = xhqm::codesys::split_string(name, '.');
			return (list.size() > 1) ? list[1] : name;
		}

		bool fileinfo::is_good()
		{
			return file.is_open();
		}
		void fileinfo::open(std::ios_base::openmode mode)
		{
			if (!file.is_open()) file.open(filepath(), mode);
		}
		void fileinfo::close()
		{
			if (file.is_open()) file.close();
		}
		std::fstream& fileinfo::fstream()
		{
			return file;
		}
	}
}

