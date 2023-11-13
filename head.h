#ifndef XHQM_HEAD
#define XHQM_HEAD

#ifdef _MSC_VER
#define XHQMEXPORT  __declspec(dllexport)
#define XHQMIMPORT  __declspec(dllimport)
#else
#define XHQMEXPORT
#define XHQMIMPORT
#endif

#ifdef XHQM_PROGRAM
#define XHQMCLASS  XHQMEXPORT
#else
#define XHQMCLASS  XHQMIMPORT
#ifdef _MSC_VER
#ifdef XHQMDLL_PROGRAM
#pragma comment(lib,"../../public/xhqm.lib")
#else
#pragma comment(lib,"../public/xhqm.lib")
#endif
#endif
#endif
#define xhqmclass XHQMCLASS
#ifdef _MSC_VER
#pragma warning(disable : 4251)
//#pragma warning(disable : 4091)
#pragma warning(disable : 4996)
#endif

#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdarg>
#include <cstring>

#include <list>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeindex>


namespace xtd
{
    template <typename type, std::size_t size>
    using array = std::array<type, size>;

	template <typename type, std::size_t size>
	using grids = std::array<std::array<type, size>, size>;

	template <typename type, std::size_t size>
	using magic = std::array<std::array<std::array<type, size>, size>, size>;

    template <typename type>
    using list = std::list<type>;

    template <typename type>
    using vector = std::vector<type>;

    template <typename type>
    using matrix = std::vector<std::vector<type>>;
}

namespace xhqm
{
	struct os {
		enum type {
			os_no = 0,
			os_ios,
			os_mac,
			os_unix,
			os_linux,
			os_posix,
			//os_win32,
			//os_win64,
			os_window,
			os_android,
			os_harmony,
		};
#ifdef _WIN32
		//define something for Windows (32-bit and 64-bit, this part is common)
		constexpr static type this_os = os_window;
#define XHQM_WINDOWS
//#ifdef _WIN64
//   //define something for Windows (64-bit only)
//		constexpr static type this_os = os_win64;
//#else
//   //define something for Windows (32-bit only)
//		constexpr static type this_os = os_win32;
//#endif
#elif __APPLE__
#if TARGET_IPHONE_SIMULATOR
		constexpr static type this_os = os_ios;// iOS Simulator
#define XHQM_IOS
#elif TARGET_OS_IPHONE
		constexpr static type this_os = os_ios;// iOS device
#define XHQM_IOS
#elif TARGET_OS_MAC
		constexpr static type this_os = os_mac;
#define XHQM_MAC
#elif __ANDROID__
		constexpr static type this_os = os_android;
#define XHQM_ANDROID
#elif __linux__
		constexpr static type this_os = os_linux;
#define XHQM_LINUX
#elif __unix__ // all unices not caught above
		constexpr static type this_os = os_unix;
#define XHQM_UNIX
#elif defined(_POSIX_VERSION)
		constexpr static type this_os = os_posix;
#define XHQM_POSIX
#else
		constexpr static type this_os = os_no;
#define XHQM_OSNO
#endif
#endif
	};
}

namespace xhqm 
{
	//宏函数
#define xhqm_redef(sec, fir) using sec = fir;//typedef fir sec;
#define xhqm_max(_val1, _val2) (_val1 > _val2 ? _val1 : _val2)
#define xhqm_min(_val1, _val2) (_val1 < _val2 ? _val1 : _val2)
#define xhqm_abs(_val1, _val2) (xhqm_max(_val1, _val2) - xhqm_min(_val1, _val2))
#define xhqm_rount(_val) ((int)(_val + 0.5f))
#define xhqm_equal(_val1, _val2, _preci) (_preci >= xhqm_abs(_val1, _val2))
#define xhqm_equalpreci(_val1, _val2) xhqm_equal(_val1, _val2, xhqm::preci)
#define xhqm_delete(_ptr) if(_ptr){ delete _ptr; _ptr = nullptr;}
#define xhqm_new(_ptr, _class) if(!_ptr){ _ptr = new _class;}

	//字符串
#define _XHQMCONNECTSTR(x,y) x##y	//拼接 
#define _XHQMTOSTR(x) #x			//转字符串
#define XHQMCONNECTSTR(x,y) _XHQMCONNECTSTR(x,y)
#define XHQMTOSTR(x) _XHQMTOSTR(x)

	//常数
	static constexpr auto en = 2.71828182845904523536028747135266249775724709369996;//自然底数
	static constexpr auto pi = 3.14159265358979323846264338327950288419716939937510;//圆周率
	static constexpr auto preci = 0.00000000001;//精度
	static constexpr auto npos = static_cast<std::size_t>(-1);

	static double zero = 0;//零值
	static double inf = 1 / zero;
	static double nan = 0 / zero;

	//数学体系
	using natural = std::size_t;//自然数
	using integer = std::intptr_t;//整数
	using measure = std::double_t;//实数
	using symbols = unsigned char;//符号
	using duality = bool;		  //是否
	using anycase = void*;		  //事物

	using string = std::string;
	using inte = std::intptr_t;	//有符号
	using size = std::size_t;	//无符号
	using byte = unsigned char;
	using writ = char;
	using sign = char;

	//内存体系
	using byte_1 = unsigned char;
	using byte_2 = unsigned short;
	using byte_4 = unsigned int;
	using byte_8 = unsigned long long;

	//颜色体系
	using color = unsigned int;
#define xhqm_rgb(_r,_g,_b)		((xhqm::color)(((xhqm::byte)(_r)|((xhqm::color)((xhqm::byte)(_g))<<8))|(((xhqm::color)(xhqm::byte)(_b))<<16)|(((xhqm::color)(xhqm::byte)(0xff))<<24)))
#define xhqm_rgba(_r,_g,_b,_a)	((xhqm::color)(((xhqm::byte)(_r)|((xhqm::color)((xhqm::byte)(_g))<<8))|(((xhqm::color)(xhqm::byte)(_b))<<16)|(((xhqm::color)(xhqm::byte)(_a))<<24)))
#define xhqm_byte(_data,_ind)	((xhqm::byte*)(&_data))[_ind]
#define xhqmcolor_r(_data)		((xhqm::byte*)(&_data))[0]
#define xhqmcolor_g(_data)		((xhqm::byte*)(&_data))[1]
#define xhqmcolor_b(_data)		((xhqm::byte*)(&_data))[2]
#define xhqmcolor_a(_data)		((xhqm::byte*)(&_data))[3]


	inline namespace templates {
		//要求type有默认的构造函数进行初始化
		template <typename type>
		struct initialize {
			const type value;
			inline initialize() :value() {};
			inline initialize(const type& val) :value(val) {};
		};
		template <typename type> struct init { 
			static constexpr type value = type();
		};
	};
	inline namespace literals {
		inline void operator""_cout(const char* str, xhqm::size) {
			std::cout << xhqm::string(str) << std::endl;
		}
		inline void operator""_cout(unsigned long long val) {
			std::cout << val << std::endl;
		}
		inline void operator""_cout(long double val) {
			std::cout << val << std::endl;
		}
	};
}


#endif
