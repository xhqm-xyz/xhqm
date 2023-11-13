#include "codesys.h"

namespace xhqm
{
	void codesys::hexa(const xhqm::byte& data, std::array<xhqm::writ, 2>& text)
	{
		text[0] = (data & 0xf0) >> 4;
		text[1] = (data & 0x0f) >> 0;
		text[0] = (text[0] < 10 ? text[0] + 0x30 : text[0] + 0x41 - 10);
		text[1] = (text[1] < 10 ? text[1] + 0x30 : text[1] + 0x41 - 10);
	}

	void codesys::hexa(const std::array<xhqm::writ, 2>& text, xhqm::byte& data)
	{
		data = 0x00;
		data |= (text[1] < 0x41 ? (text[1] - 0x30) << 0 : (text[1] - 0x41 + 10) << 0);
		data |= (text[0] < 0x41 ? (text[0] - 0x30) << 4 : (text[0] - 0x41 + 10) << 4);
	}

	std::string codesys::tohexa(const std::string& text, bool ustag, xhqm::writ tag)
	{
		std::string asitext;
		std::array<xhqm::writ, 2> asi;
		xhqm::size len = text.length();
		if (ustag)
		{
			asitext.resize(len * 3);
			for (xhqm::size i = 0; i < len; ++i)
			{
				hexa(text[i], asi);
				asitext[i * 3 + 0] = asi[0];
				asitext[i * 3 + 1] = asi[1];
				asitext[i * 3 + 2] = tag;
			}
		}
		else
		{
			asitext.resize(len * 2);
			for (xhqm::size i = 0; i < len; ++i)
			{
				hexa(text[i], asi);
				asitext[i * 2 + 0] = asi[0];
				asitext[i * 2 + 1] = asi[1];
			}
		}
		return asitext;
	}

	std::string codesys::formhexa(const std::string& data, bool ustag)
	{
		std::string text;
		xhqm::byte hexadata;
		std::array<xhqm::writ, 2> asi;
		xhqm::size len = data.length();
		if (ustag)
		{
			len = len / 3 + (len % 3 == 2 ? 1 : 0);
			text.resize(len);
			for (xhqm::size i = 0; i < len; ++i)
			{
				asi[0] = data[i * 3 + 0];
				asi[1] = data[i * 3 + 1];
				hexa(asi, hexadata);
				text[i] = hexadata;
			}
		}
		else
		{
			len = len / 2;
			text.resize(len);
			for (xhqm::size i = 0; i < len; ++i)
			{
				asi[0] = data[i * 2 + 0];
				asi[1] = data[i * 2 + 1];
				hexa(asi, hexadata);
				text[i] = hexadata;
			}
		}
		return text;
	}


	//std::string codesys::unicode_to_string(const std::wstring& str)
	//{
	//	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
	//}

	//std::wstring codesys::string_to_unicode(const std::string& str)
	//{
	//	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
	//}

	void codesys::split_string(const std::string& str, xhqm::writ tag, std::vector<std::string>& elements)
	{
		elements.clear();
		std::string item;
		std::stringstream ss(str);
		while (std::getline(ss, item, tag)) 
			elements.push_back(item);
	}

	void codesys::split_string(const std::string& str, std::string tag, std::vector<std::string>& elements)
	{
		std::regex reg(tag);
		std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
		elements = std::vector<std::string>(iter, std::sregex_token_iterator());
	}
}
