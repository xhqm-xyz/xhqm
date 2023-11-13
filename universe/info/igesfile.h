#ifndef SO_FILE_IGES
#define SO_FILE_IGES
#include <map>
#include "fileinfo.h"
namespace xhqm
{
	namespace info
	{
		using igespoit = std::array<xhqm::sign, 8>;
		using igesline = std::array<xhqm::info::igespoit, 10>;
		using igesdata = std::vector<xhqm::info::igesline>;
		using igessign = std::map<xhqm::sign, xhqm::size>;
		struct igesmode {
			int EntityTypeNumber	;//实体类型

			int ParamDataCount		;//PD开始行
			int StrucTure			;//结构
			int LineFontPatt		;//线条字体模式
			int Level				;//水平
			int View				;//视图
			int TransMatrix			;//转换矩阵
			int LabelDispAssoc		;//标签显示关联性
			int StatusNumber		;//状态编号

			int LineWeightNumber	;//线宽数
			int ColorNumber			;//色号
			int ParamLineCount		;//参数行数
			int FormNumber			;//表格编号
			int ValueSave1			;//保留 未使用
			int ValueSave2			;//保留 未使用
			std::string EntityLabel			;//实体标签
			int EntitySubsNumber	;//实体下标编号

			std::vector<std::string> ValueList;
		};

		class xhqmclass igesfile :
			public xhqm::info::fileinfo
		{
		protected:
			xhqm::info::igesdata dataBC;
			xhqm::info::igesdata dataS;
			xhqm::info::igesdata dataG;
			xhqm::info::igesdata dataD;
			xhqm::info::igesdata dataP;
			xhqm::info::igesline dataT;
			char _G_Parameter_Delimiter = ',';//参数分隔符
			char _G_Record_Delimiter = ';';//记录分隔符
			std::string _S;
			std::vector<std::string> _G;
			std::vector<xhqm::info::igesmode> _D;
			xhqm::info::igessign _T;
		protected:
			void readBC();//“B”或“C”表示标志段；
			void readS();//“S”表示开始段；
			void readG();//“G”表示全局段；
			void readD();//“D”表示元素索引段；
			void readP();//“P”表示参数数据段；
			void readT();//“T”表示结束段。
			void saveBC();//“B”或“C”表示标志段；
			void saveS();//“S”表示开始段；
			void saveG();//“G”表示全局段；
			void saveD();//“D”表示元素索引段；
			void saveP();//“P”表示参数数据段；
			void saveT();//“T”表示结束段。
			void clear(xhqm::sign sign = '0');
		public:
			igesfile(std::string igespath = "");
			xhqm::info::igesdata* data(xhqm::sign sign);
			inline xhqm::info::igesmode& operator[](const xhqm::size& pos) { return _D[pos]; };
			inline xhqm::size Size() { return _D.size(); }
			virtual xhqm::sign read();
			virtual xhqm::sign save();
		protected:

			inline static xhqm::sign igeslinetype(xhqm::info::igesline& line) {
				return line[9][0];
			}
			inline static std::string igespoitstr(xhqm::info::igespoit& poit) {
				std::string poitstr{ 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20 };;
				for (xhqm::size pos = 0; pos != 8; ++pos)
					poitstr[pos] = poit[pos];
				return poitstr;
			}
			inline static std::string igeslinestr(xhqm::info::igesline& line, xhqm::size last = 10) {
				std::string linestr = "";
				for (xhqm::size pos = 0; pos != last; ++pos)
					linestr.append(igespoitstr(line[pos]));
				return linestr;
			}
			inline static std::string igesdatastr(xhqm::info::igesdata& data, xhqm::sign sign = 0x30) {
				std::string datastr = "";
				for (auto& line : data)
					if (sign == igeslinetype(line) || sign == 0x30)
						datastr.append(igeslinestr(line, 9));
				return datastr;
			}

			template<class type>
			inline static xhqm::info::igespoit igespoit(type sure) {
				xhqm::info::igespoit poit{ 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 };
				std::string surestr = std::to_string(sure);
				xhqm::size strsure = surestr.size();
				for (xhqm::size pos = 0; pos != strsure; ++pos)
					poit[8 - pos - 1] = surestr[strsure - pos - 1];
				return poit;
			}
			inline static xhqm::info::igespoit igespoit(xhqm::sign sign, xhqm::size size) {
				xhqm::info::igespoit poit{ 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20 };
				std::string sizestr = std::to_string(size);
				xhqm::size strsize = sizestr.size();
				poit[0] = sign;
				for (xhqm::size pos = 0; pos != strsize; ++pos)
					poit[8 - pos - 1] = sizestr[strsize - pos - 1];
				return poit;
			}
			inline static xhqm::info::igespoit igespoit(std::string& poitstr) {
				xhqm::info::igespoit poit;
				for (xhqm::size pos = 0; pos != 8; ++pos)
					poit[pos] = poitstr[pos];
				return poit;
			}
			inline static xhqm::info::igesline igesline(std::string& linestr) {
				xhqm::info::igesline line;
				for (xhqm::size i = 0; i != 10; ++i)
					for (xhqm::size j = 0; j != 8; ++j)
						line[i][j] = linestr[i * 8 + j];
				return line;
			}
			inline static xhqm::info::igesdata igesdata(xhqm::sign sign, std::string& datastr, xhqm::size linesize = 72) {
				xhqm::size length = datastr.length();
				xhqm::size size = length % linesize;
				if (size != 0) {
					size = linesize - size;
					for (xhqm::size i = 0; i != size; ++i)
						datastr.append(" ");
				}

				xhqm::info::igesdata data;
				length = datastr.length();
				size = length / linesize;

				for (xhqm::size i = 0; i != size; ++i) {
					xhqm::info::igesline line;
					for (xhqm::size j = 0; j != linesize; ++j)
						line[j / 8][j % 8] = datastr[i * linesize + j];
					line[9] = igespoit(sign, i + 1);
					data.push_back(line);
				}
				return data;
			}
		};
	}
}
#endif