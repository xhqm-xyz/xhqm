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
		using compute = std::function<type(const type&, const type&)>;//����
		using compare = std::function<bool(const type&, const type&)>;//�Ƚ�

		inline static compute sum = nullptr;//���㣬��
		inline static compute sub = nullptr;//���㣬��
		inline static compute dot = nullptr;//���㣬��
		inline static compute div = nullptr;//���㣬��
		inline static void set_sum(compute fun) { sum = fun; }
		inline static void set_sub(compute fun) { sub = fun; }
		inline static void set_dot(compute fun) { dot = fun; }
		inline static void set_div(compute fun) { div = fun; }
		inline friend element operator+(const element& re, const element& le) { return sum(re, le); };
		inline friend element operator-(const element& re, const element& le) { return sub(re, le); };
		inline friend element operator*(const element& re, const element& le) { return dot(re, le); };
		inline friend element operator/(const element& re, const element& le) { return div(re, le); };

		inline static compare equal = nullptr;//��ȣ��Ƿ����
		inline static compare less_than = nullptr;//ƫ���Ƿ�С��
		inline static compare greater_than = nullptr;//ƫ���Ƿ����
		inline static compare less_equal = nullptr;//ƫ���Ƿ�С�ڵ���
		inline static compare greater_equal = nullptr;//ƫ���Ƿ���ڵ���
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
