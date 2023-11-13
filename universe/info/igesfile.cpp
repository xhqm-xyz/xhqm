#include "igesfile.h"
namespace xhqm
{
	namespace info
	{
		igesfile::igesfile(std::string igespath)
            : xhqm::info::fileinfo(igespath)
        , dataT{ {{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}} }
		{
			
		}

		void igesfile::readBC()
		{
		}

		void igesfile::readS()
		{
			_S = igesdatastr(dataS);
		}

		void igesfile::readG()
		{
			std::string str_g = igesdatastr(dataG);
			std::string str_delimiter = igespoitstr(dataG[0][0]);
			std::vector<std::string> listinfo = xhqm::codesys::split_string(str_delimiter, _G_Parameter_Delimiter);
			_G_Parameter_Delimiter = listinfo.size() < 3 ? listinfo[0][2] : _G_Parameter_Delimiter;
			_G_Record_Delimiter = listinfo.size() < 3 ? listinfo[1][2] : listinfo[2][2];
			xhqm::codesys::split_string(str_g, _G_Parameter_Delimiter, _G);
		}

		void igesfile::readD()
		{
			const std::string emp = "        ";
			xhqm::size size = dataD.size() / 2;
			_D = std::vector<xhqm::info::igesmode>(size);
			for (xhqm::size pos = 0; pos != size; ++pos) {
				std::vector<std::string> pointstr_0;
				std::vector<std::string> pointstr_1;
				for (auto& poit : dataD[pos * 2 + 0]) pointstr_0.push_back(igespoitstr(poit));
				for (auto& poit : dataD[pos * 2 + 1]) pointstr_1.push_back(igespoitstr(poit));

				_D[pos].EntityTypeNumber	= std::stoi(pointstr_0[0] == emp ? "0" : pointstr_0[0]);

				_D[pos].ParamDataCount		= std::stoi(pointstr_0[1] == emp ? "0" : pointstr_0[1]);
				_D[pos].StrucTure			= std::stoi(pointstr_0[2] == emp ? "0" : pointstr_0[2]);
				_D[pos].LineFontPatt		= std::stoi(pointstr_0[3] == emp ? "0" : pointstr_0[3]);
				_D[pos].Level				= std::stoi(pointstr_0[4] == emp ? "0" : pointstr_0[4]);
				_D[pos].View				= std::stoi(pointstr_0[5] == emp ? "0" : pointstr_0[5]);
				_D[pos].TransMatrix			= std::stoi(pointstr_0[6] == emp ? "0" : pointstr_0[6]);
				_D[pos].LabelDispAssoc		= std::stoi(pointstr_0[7] == emp ? "0" : pointstr_0[7]);
				_D[pos].StatusNumber		= std::stoi(pointstr_0[8] == emp ? "0" : pointstr_0[8]);

				_D[pos].LineWeightNumber	= std::stoi(pointstr_1[1] == emp ? "0" : pointstr_1[1]);
				_D[pos].ColorNumber			= std::stoi(pointstr_1[2] == emp ? "0" : pointstr_1[2]);
				_D[pos].ParamLineCount		= std::stoi(pointstr_1[3] == emp ? "0" : pointstr_1[3]);
				_D[pos].FormNumber			= std::stoi(pointstr_1[4] == emp ? "0" : pointstr_1[4]);
				_D[pos].ValueSave1			= std::stoi(pointstr_1[5] == emp ? "0" : pointstr_1[5]);
				_D[pos].ValueSave2			= std::stoi(pointstr_1[6] == emp ? "0" : pointstr_1[6]);
				_D[pos].EntityLabel			= pointstr_1[7];
				_D[pos].EntitySubsNumber	= std::stoi(pointstr_1[8] == emp ? "0" : pointstr_1[8]);
			}
		}

		void igesfile::readP()
		{
			xhqm::size size = dataD.size() / 2;
			for (xhqm::size pos = 0; pos != size; ++pos) {
				std::string dataline = "";
				xhqm::size dsize = _D[pos].ParamDataCount + _D[pos].ParamLineCount;
				for (xhqm::size dpos = _D[pos].ParamDataCount; dpos != dsize; ++dpos)
					dataline += igeslinestr(dataP[dpos - 1], 8);
				_D[pos].ValueList = xhqm::codesys::split_string(dataline, _G_Record_Delimiter);
				_D[pos].ValueList = xhqm::codesys::split_string(_D[pos].ValueList[0], _G_Parameter_Delimiter);

			}
		}

		void igesfile::readT()
		{
			xhqm::info::igespoit poit0 = dataT[0]; poit0[0] = 0x20;
			xhqm::info::igespoit poit1 = dataT[1]; poit1[0] = 0x20;
			xhqm::info::igespoit poit2 = dataT[2]; poit2[0] = 0x20;
			xhqm::info::igespoit poit3 = dataT[3]; poit3[0] = 0x20;
			_T[dataT[0][0]] = std::stoi(igespoitstr(poit0)); //data('S')->size();// 
			_T[dataT[1][0]] = std::stoi(igespoitstr(poit1)); //data('G')->size();// 
			_T[dataT[2][0]] = std::stoi(igespoitstr(poit2)); //data('D')->size();// 
			_T[dataT[3][0]] = std::stoi(igespoitstr(poit3)); //data('P')->size();// 
		}

		void igesfile::saveBC()
		{
		}

		void igesfile::saveS()
		{
			clear('S');
			dataS = igesdata('S', _S);
		}

		void igesfile::saveG()
		{			
			std::string delimiter = "1H,,1H;";
			delimiter[2] = _G_Parameter_Delimiter;
			delimiter[6] = _G_Record_Delimiter;
			std::string G = delimiter;
			xhqm::size pos = 0;
			_G[pos] = ""; 
			pos = (_G[1] != "" ? 1 : 2);
			_G[pos] = "";
			for (auto& g : _G) if(g != "") G += ("," + g);
			clear('G');
			dataG = igesdata('G', G);
		}

		void igesfile::saveD()
		{
			clear('D');
			xhqm::size size = _D.size();
			for (xhqm::size pos = 0; pos != size; ++pos) {
				xhqm::info::igesline line_0;
				xhqm::info::igesline line_1;
				line_0[0] = igespoit<xhqm::size>(_D[pos].EntityTypeNumber	);
				line_0[1] = igespoit<xhqm::size>(_D[pos].ParamDataCount		);
				line_0[2] = igespoit<xhqm::size>(_D[pos].StrucTure			);
				line_0[3] = igespoit<xhqm::size>(_D[pos].LineFontPatt		);
				line_0[4] = igespoit<xhqm::size>(_D[pos].Level				);
				line_0[5] = igespoit<xhqm::size>(_D[pos].View				);
				line_0[6] = igespoit<xhqm::size>(_D[pos].TransMatrix		);
				line_0[7] = igespoit<xhqm::size>(_D[pos].LabelDispAssoc		);
				line_0[8] = igespoit<xhqm::size>(_D[pos].StatusNumber		);
				line_1[0] = igespoit<xhqm::size>(_D[pos].EntityTypeNumber	);
				line_1[1] = igespoit<xhqm::size>(_D[pos].LineWeightNumber	);
				line_1[2] = igespoit<xhqm::size>(_D[pos].ColorNumber		);
				line_1[3] = igespoit<xhqm::size>(_D[pos].ParamLineCount		);
				line_1[4] = igespoit<xhqm::size>(_D[pos].FormNumber			);
				line_1[5] = igespoit<xhqm::size>(_D[pos].ValueSave1			);
				line_1[6] = igespoit<xhqm::size>(_D[pos].ValueSave2			);
				line_1[7] = igespoit(_D[pos].EntityLabel		);
				line_1[8] = igespoit<xhqm::size>(_D[pos].EntitySubsNumber	);

				line_0[9] = igespoit('D', pos * 2 + 1);
				line_1[9] = igespoit('D', pos * 2 + 2);

				dataD.push_back(line_0);
				dataD.push_back(line_1);
			}
		}

		void igesfile::saveP()
		{
			clear('P');
			xhqm::size size = _D.size();
			for (xhqm::size pos = 0; pos != size; ++pos) {
				std::string dataline = "";
				for (auto& str : _D[pos].ValueList)
					dataline = dataline + str + _G_Parameter_Delimiter;
				dataline[dataline.length() - 1] = _G_Record_Delimiter;

				xhqm::info::igesdata datap = igesdata('P', dataline, 64);
				xhqm::size count = 1;
				for (auto& line : datap) {
					line[8] = igespoit<xhqm::size>(pos * 2 + 1);
					line[9] = igespoit('P', dataP.size() + count++);
				}

				dataP.insert(dataP.end(), datap.begin(), datap.end());
			}
		}

		void igesfile::saveT()
		{
			_T['S'] = data('S')->size();// std::stoi(igespoitstr(dataT[0])); //
			_T['G'] = data('G')->size();// std::stoi(igespoitstr(dataT[1])); //
			_T['D'] = data('D')->size();// std::stoi(igespoitstr(dataT[2])); //
			_T['P'] = data('P')->size();// std::stoi(igespoitstr(dataT[3])); //
			dataT[0] = igespoit('S', _T['S']);
			dataT[1] = igespoit('G', _T['G']);
			dataT[2] = igespoit('D', _T['D']);
			dataT[3] = igespoit('P', _T['P']);
		}


		xhqm::info::igesdata* igesfile::data(xhqm::sign sign)
		{
			switch (sign) {
			case 'B': return &dataBC;
			case 'C': return &dataBC;
			case 'S': return &dataS;
			case 'G': return &dataG;
			case 'D': return &dataD;
			case 'P': return &dataP;
			default: return nullptr;
			}
		}
		void igesfile::clear(xhqm::sign sign)
		{
			switch (sign) {
			case 'B':
			case 'C':
			case 'S':
			case 'G':
			case 'D':
			case 'P':
				data(sign)->clear();
				_T[sign] = 0;
				break;
			default: 
				dataBC.clear();
				dataS.clear();
				dataG.clear();
				dataD.clear();
				dataP.clear();
				_T['S'] = 0;
				_T['G'] = 0;
				_T['D'] = 0;
				_T['P'] = 0;
				break;
			}
		}
		xhqm::sign igesfile::read() {
			close();
			open(std::ios::in);
			if (is_good()) {
				clear();
				std::string linedata;
				while (!file.eof()) {
					std::getline(file, linedata);
					if (linedata.size() < 80) continue;
					xhqm::info::igesline line = igesline(linedata);
					auto dataptr = data(igeslinetype(line));
					if(dataptr) dataptr->push_back(line);//'B' 'C' 'S', 'G', 'D', 'P'
					else 
						dataT = line; //'T'
				} close();
			} 

			readBC();
			readS();
			readG();
			readD();
			readP();
			readT();
			return 0;
		}
		xhqm::sign igesfile::save() {
			saveBC();
			saveS();
			saveG();
			saveD();
			saveP();
			saveT();

			close();
			open(std::ios::out);
			if (is_good()) {
				std::string linedata;
				std::array<xhqm::sign, 4> signs{'S', 'G', 'D', 'P'};
				for (auto& sign : signs) {
					auto dataall = data(sign);
					for (auto& line : (*dataall)) {
						linedata = igeslinestr(line, 10);
						file << linedata << "\n";
					}
				} 
				linedata = igeslinestr(dataT, 10);
				file << linedata << "\n";
				close();
			} 
			return 0;
		}
	}
}
