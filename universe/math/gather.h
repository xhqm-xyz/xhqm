#ifndef XHQM_MATH_GATHER
#define XHQM_MATH_GATHER
#include <algorithm>
#include <functional>
#include "../../head.h"
#include "../../conception/element.h"
#include "../../metaclass/template.h"
#include "../../metaclass/symbols_has.h"
namespace xhqm
{
	namespace math
	{
		template<typename type>
		class gather{
		public:
			using value_type = typename xhqm::select_if<xhqm::symbols_has<type>::has_less_than && xhqm::symbols_has<type>::has_equal, type, xhqm::element<type>>::type;
			using size_type = xhqm::size;
			using docker = std::vector<type>;
			using function = std::function<bool(const type&, const type&)>;
			using iterator = typename std::vector<type>::iterator;
			using const_iterator = typename std::vector<type>::const_iterator;
		protected:
			std::vector<type> m_values;
			inline static function equal = nullptr;//恒等，是否相等
			inline static function compare = nullptr;//偏序，是否小于
		public:
			inline static void set_equal(function fun) { equal = fun; }
			inline static void set_compare(function fun) { compare = fun; }
		public:
			inline gather() {};
			inline gather(const size_type& dim) : m_values(dim) {};
			inline gather(const docker& values) : m_values(values) {};
			inline gather(const gather& right) : m_values(right.m_values) {};
			inline gather(std::initializer_list<type> list) : m_values(list) {};

			template<class Fun, typename ... Args>
			inline void exec(Fun fun, Args ...args) {
				for (auto& var : m_values) var = fun(var, std::forward<Args>(args)...);
			}

			//排序
			inline void sort() {
				if (compare) std::sort(m_values.begin(), m_values.end(), compare);
				else std::sort(m_values.begin(), m_values.end(), std::less<>{});
			}
			//排序
			inline void sort(function compare) {
				if (compare) std::sort(m_values.begin(), m_values.end(), compare);
				else std::sort(m_values.begin(), m_values.end(), std::less<>{});
			}
			//去重
			inline void deduplication()
			{
				docker temp;
				for (xhqm::size i = 0, size = m_values.size(); i != size; i++)
				{
					temp.push_back(m_values[i]);
					for (xhqm::size j = i + 1; j < size; j++)
					{
						if (equal ? equal(m_values[i], m_values[j]) : (m_values[i] == m_values[j]))
						{
							temp.pop_back();
							break;
						}
					}
				}
				m_values = temp;
				sort();
			}
			//去重
			inline void deduplication(function equal)
			{
				docker temp;
				for (xhqm::size i = 0, size = m_values.size(); i != size; i++)
				{
					temp.push_back(m_values[i]);
					for (xhqm::size j = i + 1; j < size; j++)
					{
						if (equal ? equal(m_values[i], m_values[j]) : (m_values[i] == m_values[j]))
						{
							temp.pop_back();
							break;
						}
					}
				}
				m_values = temp;
				sort();
			}
			//去重
			inline void deduplication(function equal, function compare)
			{
				docker temp;
				for (xhqm::size i = 0, size = m_values.size(); i != size; i++)
				{
					temp.push_back(m_values[i]);
					for (xhqm::size j = i + 1; j < size; j++)
					{
						if (equal ? equal(m_values[i], m_values[j]) : (m_values[i] == m_values[j]))
						{
							temp.pop_back();
							break;
						}
					}
				}
				m_values = temp;
				sort(compare);
			}

			inline docker& vector() noexcept {
				return m_values;
			}
			inline xhqm::size size() noexcept {
				return m_values.size();
			}
			inline iterator begin() noexcept {
				return m_values.begin();
			}
			inline iterator end() noexcept {
				return m_values.end();
			}
			
			inline const docker& vector() const noexcept {
				return m_values;
			}
			inline const xhqm::size size() const noexcept {
				return m_values.size();
			}
			inline const_iterator begin() const noexcept {
				return m_values.begin();
			}
			inline const_iterator end() const noexcept {
				return m_values.end();
			}
		public:
			inline type& operator[](const size_type pos) noexcept { return m_values[pos]; }
			inline const type& operator[](const size_type pos) const noexcept { return m_values[pos]; }
			inline gather& operator=(const std::initializer_list<type>& list) { m_values = list; return (*this); };
			inline gather& operator=(const docker& right) { m_values = right; return (*this); };
			inline gather& operator=(const gather& right) { m_values = right.m_values; return (*this); };

			//增加一个元素
			inline void add(const type& value) {
				m_values.push_back(value);
			}
			//删除首个相同元素
			inline void sub(const type& value) {
				for (xhqm::size i = 0, size = m_values.size(); i != size; i++) {
					if (equal ? equal(value, m_values[i]) : (value == m_values[i]))
					{
						m_values.erase(m_values.begin() + i);
						break;
					}
				}
			}
			//删除全部相同元素
			inline void div(const type& value) {
				docker values_copy = m_values; m_values.clear();
				for (xhqm::size i = 0, size = m_values.size(); i != size; i++) {
					if (equal ? !equal(value, m_values[i]) : !(value == m_values[i]))
					{
						m_values.push_back(m_values[i]);
					}
				}
			}

			//结果非去重
			inline static gather<type> add(const gather<type>& A, const gather<type>& B)//和集//或集//并集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.sort(); copyB.sort();
				for (xhqm::size pos = 0, size = (A.size() + B.size()); pos < size; ) {
					if (apos == A.size() && bpos == B.size()) break;
					else if (apos < A.size() && bpos == B.size()) {
						res.m_values.insert(res.m_values.end(), copyA.m_values.begin() + apos, copyA.m_values.end()); break;
					}
					else if (apos == A.size() && bpos < B.size()) {
						res.m_values.insert(res.m_values.end(), copyB.m_values.begin() + bpos, copyB.m_values.end()); break;
					}

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						res.m_values.emplace_back(copyA[apos]);
						res.m_values.emplace_back(copyB[bpos]);
						++apos; ++pos;
						++bpos; ++pos;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							res.m_values.emplace_back(copyA[apos]);
							++apos; ++pos;
						}
						else {
							res.m_values.emplace_back(copyB[bpos]);
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
			inline static gather<type> sub(const gather<type>& A, const gather<type>& B)//差集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.sort(); copyB.sort();
				for (xhqm::size pos = 0, size = (A.size() + B.size()); pos < size; ) {
					if (apos == A.size()) break;
					else if (apos < A.size() && bpos == B.size()) {
						res.m_values.insert(res.m_values.end(), copyA.m_values.begin() + apos, copyA.m_values.end()); break;
					}

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						++apos; ++pos;
						++bpos; ++pos;
						continue;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							res.m_values.emplace_back(copyA[apos]);
							++apos; ++pos;
						}
						else {
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
			inline static gather<type> mul(const gather<type>& A, const gather<type>& B)//交集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.sort(); copyB.sort();
				for (xhqm::size pos = 0, size = (A.size() + B.size()); pos < size; ) {
					if (apos == A.size() || bpos == B.size()) break;

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						res.m_values.emplace_back(copyA[apos]);
						++apos; ++pos;
						++bpos; ++pos;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							++apos; ++pos;
						}
						else {
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
			inline static gather<type> div(const gather<type>& A, const gather<type>& B)//异或集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.sort(); copyB.sort();
				for (xhqm::size pos = 0, size = (A.size() + B.size()); pos < size; ) {
					if (apos == A.size() && bpos == B.size()) break;
					else if (apos < A.size() && bpos == B.size()) {
						res.m_values.insert(res.m_values.end(), copyA.m_values.begin() + apos, copyA.m_values.end()); break;
					}
					else if (apos == A.size() && bpos < B.size()) {
						res.m_values.insert(res.m_values.end(), copyB.m_values.begin() + bpos, copyB.m_values.end()); break;
					}

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						++apos; ++pos;
						++bpos; ++pos;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							res.m_values.emplace_back(copyA[apos]);
							++apos; ++pos;
						}
						else {
							res.m_values.emplace_back(copyB[bpos]);
							++bpos; ++pos;
						}
					}
				}
				return res;
			};

			//结果去重
			inline friend gather<type> operator + (const gather<type>& A, const gather<type>& B)//和集//或集//并集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.deduplication();
				copyB.deduplication();
				for (xhqm::size pos = 0, size = (copyA.size() + copyB.size()); pos < size; ) {
					if (apos == copyA.size() && bpos == copyB.size()) break;
					else if (apos < copyA.size() && bpos == copyB.size()) {
						res.m_values.insert(res.m_values.end(), copyA.m_values.begin() + apos, copyA.m_values.end()); break;
					}
					else if (apos == copyA.size() && bpos < copyB.size()) {
						res.m_values.insert(res.m_values.end(), copyB.m_values.begin() + bpos, copyB.m_values.end()); break;
					}

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						res.m_values.emplace_back(copyA[apos]);
						res.m_values.emplace_back(copyB[bpos]);
						++apos; ++pos;
						++bpos; ++pos;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							res.m_values.emplace_back(copyA[apos]);
							++apos; ++pos;
						}
						else {
							res.m_values.emplace_back(copyB[bpos]);
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
			inline friend gather<type> operator - (const gather<type>& A, const gather<type>& B)//差集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.deduplication();
				copyB.deduplication();
				for (xhqm::size pos = 0, size = (copyA.size() + copyB.size()); pos < size; ) {
					if (apos == copyA.size()) break;
					else if (apos < copyA.size() && bpos == copyB.size()) {
						res.m_values.insert(res.m_values.end(), copyA.m_values.begin() + apos, copyA.m_values.end()); break;
					}

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						++apos; ++pos;
						++bpos; ++pos;
						continue;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							res.m_values.emplace_back(copyA[apos]);
							++apos; ++pos;
						}
						else {
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
			inline friend gather<type> operator * (const gather<type>& A, const gather<type>& B)//交集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.deduplication();
				copyB.deduplication();
				for (xhqm::size pos = 0, size = (copyA.size() + copyB.size()); pos < size; ) {
					if (apos == copyA.size() || bpos == copyB.size()) break;

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						res.m_values.emplace_back(copyA[apos]);
						++apos; ++pos;
						++bpos; ++pos;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							++apos; ++pos;
						}
						else {
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
			inline friend gather<type> operator / (const gather<type>& A, const gather<type>& B)//异或集
			{
				gather<type> res, copyA = A, copyB = B;
				xhqm::size apos = 0, bpos = 0;
				copyA.deduplication();
				copyB.deduplication();
				for (xhqm::size pos = 0, size = (copyA.size() + copyB.size()); pos < size; ) {
					if (apos == copyA.size() && bpos == copyB.size()) break;
					else if (apos < copyA.size() && bpos == copyB.size()) {
						res.m_values.insert(res.m_values.end(), copyA.m_values.begin() + apos, copyA.m_values.end()); break;
					}
					else if (apos == copyA.size() && bpos < copyB.size()) {
						res.m_values.insert(res.m_values.end(), copyB.m_values.begin() + bpos, copyB.m_values.end()); break;
					}

					if (equal ? equal(copyA[apos], copyB[bpos]) : (copyA[apos] == copyB[bpos])) {
						++apos; ++pos;
						++bpos; ++pos;
					}
					else
					{
						if (compare ? compare(copyA[apos], copyB[bpos]) : (copyA[apos] < copyB[bpos])) {
							res.m_values.emplace_back(copyA[apos]);
							++apos; ++pos;
						}
						else {
							res.m_values.emplace_back(copyB[bpos]);
							++bpos; ++pos;
						}
					}
				}
				return res;
			};
		};


		template<typename type>
		std::vector<type> setunion(const std::vector<type>& A, const std::vector<type>& B) {
			return (xhqm::math::gather<type>(A) + xhqm::math::gather<type>(B)).vector();
		}
		template<typename type>
		std::vector<type> setdiff(const std::vector<type>& A, const std::vector<type>& B) {
			return (xhqm::math::gather<type>(A) - xhqm::math::gather<type>(B)).vector();
		}
		template<typename type>
		std::vector<type> intersect(const std::vector<type>& A, const std::vector<type>& B) {
			return (xhqm::math::gather<type>(A) * xhqm::math::gather<type>(B)).vector();
		}
		template<typename type>
		std::vector<type> setxor(const std::vector<type>& A, const std::vector<type>& B) {
			return (xhqm::math::gather<type>(A) / xhqm::math::gather<type>(B)).vector();
		}
	}
}
#endif