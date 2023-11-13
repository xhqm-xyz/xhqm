#include "csvfile.h"

namespace xhqm
{
	namespace info 
	{

        void csvfile::ReadCSV(xtd::matrix<std::string>& csv, std::string path)
        {
            csv.clear();
            std::ifstream inFile(path);
            if (inFile.is_open())
            {
                std::string line;
                while (getline(inFile, line))
                {
                    csv.push_back({});
                    std::string field;
                    std::istringstream inLine(line); //将整行字符串line读入到字符串流istringstream中
                    while (std::getline(inLine, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
                        csv.back().push_back(field); //将刚刚读取的字符串添加到向量fields中
                }
                inFile.close();
            }
        }

        void csvfile::WriteCSV(xtd::matrix<std::string>& csv, std::string path)
        {
            std::ofstream outFile(path);
            if (outFile.is_open())
            {
                std::string line;
                for (auto& outLine : csv)
                {
                    line = "";
                    for (auto& field : outLine)
                        line.append(field + ",");
                    outFile << line;
                }
                outFile.close();
            }
        }

		csvfile::csvfile(std::string igespath)
			: xhqm::info::fileinfo(igespath)
		{
		}
        xhqm::sign csvfile::read()
		{
            close();
            open(std::ios::in);
            if (is_good()) {

                std::string line;
                while (getline(file, line))
                {
                    m_data.push_back({});
                    std::string field;
                    std::istringstream inLine(line); //将整行字符串line读入到字符串流istringstream中
                    while (std::getline(inLine, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
                        m_data.back().push_back(field); //将刚刚读取的字符串添加到向量fields中
                } close();
            }
            return 0;
		}
        xhqm::sign csvfile::save()
		{
            close();
            open(std::ios::out);
            if (is_good()) {
                std::string line;
                for (auto& outLine : m_data)
                {
                    line = "";
                    for (auto& field : outLine)
                        line.append(field + ",");
                    file << line << "\n";
                } close();
            }
            return 0;
		}
        xtd::matrix<std::string>& csvfile::data()
        {
            return m_data;
        }
        const xtd::matrix<std::string>& csvfile::data() const
        {
            return m_data;
        }
        std::string& csvfile::val(std::size_t r, std::size_t c)
        {
            return m_data[r][c];
        }
        const std::string& csvfile::val(std::size_t r, std::size_t c) const
        {
            return m_data[r][c];
        }
        std::vector<std::string> csvfile::row(std::size_t pos)
        {
            std::vector<std::string> onerow;
            onerow = m_data[pos];
            return onerow;
        }
        std::vector<std::string> csvfile::col(std::size_t pos)
        {
            std::vector<std::string> onecol;
            for (auto& onerow : m_data)
                onecol.push_back(onerow[pos]);
            return onecol;
        }
	}
}
