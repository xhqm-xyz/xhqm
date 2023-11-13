#pragma once
#ifndef XHQM_TOOL_CODE
#define XHQM_TOOL_CODE
#include "../head.h"
#include <regex>
#include <array>
#include <vector>
#include <codecvt>
namespace xhqm
{
	//string的编码方式为utf8
	class xhqmclass codesys
	{
	public:
		static void hexa(const xhqm::byte& data, std::array<xhqm::writ, 2>& text);
		static void hexa(const std::array<xhqm::writ, 2>& text, xhqm::byte& data);
		static std::string tohexa(const std::string& text, bool ustag = false, xhqm::writ tag = ' ');
		static std::string formhexa(const std::string& data, bool ustag = false);

		//static std::string unicode_to_string(const std::wstring& str);
		//static std::wstring string_to_unicode(const std::string& str);
		static void split_string(const std::string& str, xhqm::writ tag, std::vector<std::string>& elements);
		static void split_string(const std::string& str, std::string tag, std::vector<std::string>& elements);
		inline static std::vector<std::string> split_string(const std::string& str, xhqm::writ tag) {
			std::vector<std::string> elements; split_string(str, tag, elements); return  elements;
		};
		inline static std::vector<std::string> split_string(const std::string& str, std::string tag) {
			std::vector<std::string> elements; split_string(str, tag, elements); return  elements;
		};
	};

	//文字
	template<xhqm::size size>
	class writing {
	public:
		xhqm::byte writ[size];
	
		template<class type>
		writing(const type sign) {
			constexpr xhqm::size length = sizeof(type);
			for (xhqm::size ind = 0; ind != size; ++ind)
				writ[ind] = ind >= length ? 0 : xhqmbyte(sign, ind);
		}

//        template<>
//        writing<std::string>(const std::string sign) {
//			xhqm::size length = sign.length();
//			for (xhqm::size ind = 0; ind != size; ++ind)
//				writ[ind] = ind >= length ? 0 : sign.at(ind);
//		}
	};

	//模板函数
	template <class type>
	inline static void val2str(const type& val, std::string& str) {
		std::stringstream strval; strval << val; strval >> str;
	}
	template <class type>
	inline static void str2val(const std::string& str, type& val) {
		std::stringstream strval; strval << str; strval >> val;
	}
}
#endif
