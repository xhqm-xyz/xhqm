#ifndef XHQM_MATH_ELEMENT
#define XHQM_MATH_ELEMENT
#include "../head.h"
#include "../metaclass/template.h"
#include <functional>

namespace xhqm
{
	template<typename type>
	struct element {
		type m_element;
		element() { }
		element(type&& e) { m_element = std::move(e); }
		element(const type& e) { m_element = e; }
		element(element&& e) { m_element = std::move(e.m_element); }
		element(const element& e) { m_element = e.m_element; }
		using compute = std::function<type(const type&, const type&)>;//计算
		using compare = std::function<bool(const type&, const type&)>;//比较

		inline static compute sum = nullptr;//计算，加
		inline static compute sub = nullptr;//计算，减
		inline static compute dot = nullptr;//计算，乘
		inline static compute div = nullptr;//计算，除
		inline static void set_sum(compute fun) { sum = fun; }
		inline static void set_sub(compute fun) { sub = fun; }
		inline static void set_dot(compute fun) { dot = fun; }
		inline static void set_div(compute fun) { div = fun; }
		inline friend element operator+(const element& re, const element& le) { return sum(re, le); };
		inline friend element operator-(const element& re, const element& le) { return sub(re, le); };
		inline friend element operator*(const element& re, const element& le) { return dot(re, le); };
		inline friend element operator/(const element& re, const element& le) { return div(re, le); };

		inline static compare equal = nullptr;//恒等，是否相等
		inline static compare less_than = nullptr;//偏序，是否小于
		inline static compare greater_than = nullptr;//偏序，是否大于
		inline static compare less_equal = nullptr;//偏序，是否小于等于
		inline static compare greater_equal = nullptr;//偏序，是否大于等于
		inline static void set_equal(compare fun) { equal = fun; }
		inline static void set_less_than(compare fun) { less_than = fun; }
		inline static void set_greater_than(compare fun) { greater_than = fun; }
		inline static void set_less_equal(compare fun) { less_equal = fun; }
		inline static void set_greater_equal(compare fun) { greater_equal = fun; }
		inline friend bool operator==(const element& re, const element& le) { return equal(re, le); };
		inline friend bool operator< (const element& re, const element& le) { return less_than(re, le); };
		inline friend bool operator> (const element& re, const element& le) { return greater_than(re, le); };
		inline friend bool operator<=(const element& re, const element& le) { return less_equal(re, le); };
		inline friend bool operator>=(const element& re, const element& le) { return greater_equal(re, le); };
	};
}
#endif
