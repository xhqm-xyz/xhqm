#ifndef SO_FILE_STL
#define SO_FILE_STL
#include "fileinfo.h"

namespace xhqm
{
	namespace info
	{
		class xhqmclass stlfile :
			public xhqm::info::fileinfo
		{
		public:
			struct Triangle {
				float normal[3];
				float vertex1[3];
				float vertex2[3];
				float vertex3[3];
			};
		protected:
			std::vector<Triangle> m_data;
		public:
			stlfile(std::string igespath = "");
			virtual xhqm::sign read();
			virtual xhqm::sign save();

			static bool writestl_bin(const std::string& path, const std::vector<Triangle>& triangles);

			static bool writestl_txt(const std::string& path, const std::vector<Triangle>& triangles);

			static bool readstl_bin(const std::string& path, std::vector<Triangle>& triangles);

			static bool readstl_txt(const std::string& path, std::vector<Triangle>& triangles);

			static bool readstl(const std::string& path, std::vector<Triangle>& triangles);

			std::vector<Triangle>& data()
			{
				return m_data;
			};
		};
	}
}
#endif