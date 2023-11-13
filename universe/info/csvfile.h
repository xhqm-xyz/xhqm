#ifndef SO_FILE_CSV
#define SO_FILE_CSV
#include "fileinfo.h"
namespace xhqm
{
	namespace info
	{
		class xhqmclass csvfile :
			public xhqm::info::fileinfo
		{
		protected:
            xtd::matrix<std::string> m_data;
		public:
			csvfile(std::string igespath = "");
			virtual xhqm::sign read();
			virtual xhqm::sign save();

            xtd::matrix<std::string>& data();
            const xtd::matrix<std::string>& data() const;
			std::string& val(std::size_t r, std::size_t c);
			const std::string& val(std::size_t r, std::size_t c) const;

			std::vector<std::string> row(std::size_t pos);
			std::vector<std::string> col(std::size_t pos);

            static void ReadCSV(xtd::matrix<std::string>& csv, std::string path);
            static void WriteCSV(xtd::matrix<std::string>& csv, std::string path);
		};
	}
}
#endif
