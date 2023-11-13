#ifndef XHQM_MATH_POINT
#define XHQM_MATH_POINT
#include "../../head.h"
#include "../../metaclass/template.h"
namespace xhqm
{
	template<class type>
	class vec : public xhqm::hyper<type, 3>
	{
	public:
		using value_type = type;
		constexpr static xhqm::size dimension = 3;

		inline static type dot(const vec& a, const vec& b)
		{
			type sum = 0;
			sum += (a[0] * b[0]);
			sum += (a[1] * b[1]);
			sum += (a[2] * b[2]);
			return sum;
		}
		inline static vec mul(const vec& a, const vec& b)
		{
			vec c;
			c[0] = a.y() * b.z() - a.z() * b.y();
			c[1] = a.z() * b.x() - a.x() * b.z();
			c[2] = a.x() * b.y() - a.y() * b.x();
			return c;
		}

		vec(const vec& v) : xhqm::hyper<double, 3>() {
            (*this)[0] = v[0];
            (*this)[1] = v[1];
            (*this)[2] = v[2];
		}
		vec(const std::initializer_list<type>& list) : xhqm::hyper<double, 3>() {
            (*this)[0] = *(list.begin() + 0);
            (*this)[1] = *(list.begin() + 1);
            (*this)[2] = *(list.begin() + 2);
		}
		explicit vec(const type& x = type(), const type& y = type(), const type& z = type()) : xhqm::hyper<double, 3>() {
            (*this)[0] = x;
            (*this)[1] = y;
            (*this)[2] = z;
		}
		virtual ~vec() {};

		inline vec operator+ (const type& b) const 
		{
            vec res = (*this);
            res[0] += b;res[1] += b;res[2] += b;
			return res;
		}
		inline vec operator- (const type& b) const 
        {
            vec res = (*this);
            res[0] -= b;res[1] -= b;res[2] -= b;
            return res;
		}
		inline vec operator* (const type& b) const 
        {
            vec res = (*this);
            res[0] *= b;res[1] *= b;res[2] *= b;
            return res;
		}
		inline vec operator/ (const type& b) const 
        {
            vec res = (*this);
            res[0] /= b;res[1] /= b;res[2] /= b;
            return res;
		}
		inline vec operator + (const vec& b) const 
		{
            vec res = (*this);
            res[0] += b[0];
            res[1] += b[1];
            res[2] += b[2];
			return res;
		}
		inline vec operator - (const vec& b) const 
		{
            vec res = (*this);
            res[0] /= b[0];
            res[1] /= b[1];
            res[2] /= b[2];
			return res;
		}

		inline vec operator+= (const type& b)
		{
            (*this)[0] += b;
            (*this)[1] += b;
            (*this)[2] += b;
			return *this;
		}
		inline vec operator-= (const type& b)
		{
            (*this)[0] -= b;
            (*this)[1] -= b;
            (*this)[2] -= b;
			return *this;
		}
		inline vec operator*= (const type& b)
		{
            (*this)[0] *= b;
            (*this)[1] *= b;
            (*this)[2] *= b;
			return *this;
		}
		inline vec operator/= (const type& b)
		{
            (*this)[0] /= b;
            (*this)[1] /= b;
            (*this)[2] /= b;
			return *this;
		}
		inline vec operator += (const vec& b)
		{
            (*this)[0] += b[0];
            (*this)[1] += b[1];
            (*this)[2] += b[2];
			return *this;
		}
		inline vec operator -= (const vec& b)
		{
            (*this)[0] -= b[0];
            (*this)[1] -= b[1];
            (*this)[2] -= b[2];
			return *this;
		}

		inline type operator * (const vec& b)
		{
			return dot(*this, b);
		}
		inline vec operator / (const vec& b)
		{
			return mul(*this, b);
		}
		inline vec& operator= (const vec& a)
		{
            (*this)[0] = a[0];
            (*this)[1] = a[1];
            (*this)[2] = a[2];
			return (*this);
		}

        inline const type& x() const { return (*this)[0]; }
        inline const type& y() const { return (*this)[1]; }
        inline const type& z() const { return (*this)[2]; }
        inline type& x() { return (*this)[0]; }
        inline type& y() { return (*this)[1]; }
        inline type& z() { return (*this)[2]; }

		inline type modulus() const {
			initialize<type> inittype;
			type sum = inittype.value;
            sum += ((*this)[0] * (*this)[0]);
            sum += ((*this)[1] * (*this)[1]);
            sum += ((*this)[2] * (*this)[2]);
			return std::sqrt(sum);
		}
		inline vec normalvec() const { return (*this) / modulus(); }
		inline void normalize() { 
			type len = modulus();
            (*this)[0] /= len;
            (*this)[1] /= len;
            (*this)[2] /= len;
		}
	};

	template<class type>
	class mat : public xhqm::hyper<type, 3, 3>
	{
	public:
		using value_type = type;
		constexpr static std::array<xhqm::size, 2> dimension = {3, 3};

		mat(std::initializer_list<xhqm::hyper<type, 3>> list) : xhqm::hyper<type, 3, 3>() {
            (*this)[0][0] = (*(list.begin() + 0))[0]; (*this)[0][1] = (*(list.begin() + 0))[1]; (*this)[0][2] = (*(list.begin() + 0))[2];
            (*this)[1][0] = (*(list.begin() + 1))[0]; (*this)[1][1] = (*(list.begin() + 1))[1]; (*this)[1][2] = (*(list.begin() + 1))[2];
            (*this)[2][0] = (*(list.begin() + 2))[0]; (*this)[2][1] = (*(list.begin() + 2))[1]; (*this)[2][2] = (*(list.begin() + 2))[2];
		}
		mat(const mat<type>& m) : xhqm::hyper<type, 3, 3>()
		{
            (*this)[0][0] = m[0][0]; (*this)[0][1] = m[0][1]; (*this)[0][2] = m[0][2];
            (*this)[1][0] = m[1][0]; (*this)[1][1] = m[1][1]; (*this)[1][2] = m[1][2];
            (*this)[2][0] = m[2][0]; (*this)[2][1] = m[2][1]; (*this)[2][2] = m[2][2];
		}
		mat() : xhqm::hyper<type, 3, 3>() {}
		virtual ~mat() {};

		inline mat operator + (const type& b) const
		{
			mat c;
            c[0][0] = (*this)[0][0] + b; c[0][1] = (*this)[0][1] + b; c[0][2] = (*this)[0][2] + b;
            c[1][0] = (*this)[1][0] + b; c[1][1] = (*this)[1][1] + b; c[1][2] = (*this)[1][2] + b;
            c[2][0] = (*this)[2][0] + b; c[2][1] = (*this)[2][1] + b; c[2][2] = (*this)[2][2] + b;
			return c;
		}
		inline mat operator - (const type& b) const
		{
			mat c;
            c[0][0] = (*this)[0][0] - b; c[0][1] = (*this)[0][1] - b; c[0][2] = (*this)[0][2] - b;
            c[1][0] = (*this)[1][0] - b; c[1][1] = (*this)[1][1] - b; c[1][2] = (*this)[1][2] - b;
            c[2][0] = (*this)[2][0] - b; c[2][1] = (*this)[2][1] - b; c[2][2] = (*this)[2][2] - b;
			return c;
		}
		inline mat operator * (const type& b) const
		{
			mat c;
            c[0][0] = (*this)[0][0] * b; c[0][1] = (*this)[0][1] * b; c[0][2] = (*this)[0][2] * b;
            c[1][0] = (*this)[1][0] * b; c[1][1] = (*this)[1][1] * b; c[1][2] = (*this)[1][2] * b;
            c[2][0] = (*this)[2][0] * b; c[2][1] = (*this)[2][1] * b; c[2][2] = (*this)[2][2] * b;
			return c;
		}
		inline mat operator / (const type& b) const
		{
			mat c;
            c[0][0] = (*this)[0][0] / b; c[0][1] = (*this)[0][1] / b; c[0][2] = (*this)[0][2] / b;
            c[1][0] = (*this)[1][0] / b; c[1][1] = (*this)[1][1] / b; c[1][2] = (*this)[1][2] / b;
            c[2][0] = (*this)[2][0] / b; c[2][1] = (*this)[2][1] / b; c[2][2] = (*this)[2][2] / b;
			return c;
		}

		inline mat operator + (const mat& b)
		{
			mat c;
            c[0][0] = (*this)[0][0] + b[0][0]; c[1][0] = (*this)[1][0] + b[1][0]; c[2][0] = (*this)[2][0] + b[2][0];
            c[0][1] = (*this)[0][1] + b[0][1]; c[1][1] = (*this)[1][1] + b[1][1]; c[2][1] = (*this)[2][1] + b[2][1];
            c[0][2] = (*this)[0][2] + b[0][2]; c[1][2] = (*this)[1][2] + b[1][2]; c[2][2] = (*this)[2][2] + b[2][2];
			return c;
		}
		inline mat operator - (const mat& b)
		{
			mat c;
            c[0][0] = (*this)[0][0] - b[0][0]; c[1][0] = (*this)[1][0] - b[1][0]; c[2][0] = (*this)[2][0] - b[2][0];
            c[0][1] = (*this)[0][1] - b[0][1]; c[1][1] = (*this)[1][1] - b[1][1]; c[2][1] = (*this)[2][1] - b[2][1];
            c[0][2] = (*this)[0][2] - b[0][2]; c[1][2] = (*this)[1][2] - b[1][2]; c[2][2] = (*this)[2][2] - b[2][2];
			return c;
		}

		inline friend vec<type> operator * (const vec<type>& va, const mat& mb)
		{
			vec<type> c;
			c[0] = va[0] * mb[0][0] + va[1] * mb[1][0] + va[2] * mb[2][0];
			c[1] = va[0] * mb[0][1] + va[1] * mb[1][1] + va[2] * mb[2][1];
			c[2] = va[0] * mb[0][2] + va[1] * mb[1][2] + va[2] * mb[2][2];
			return c;
		}
		inline friend vec<type> operator * (const mat& ma, const vec<type>& vb)
		{
			vec<type> c;
			c[0] = ma[0][0] * vb[0] + ma[0][1] * vb[1] + ma[0][2] * vb[2];
			c[1] = ma[1][0] * vb[0] + ma[1][1] * vb[1] + ma[1][2] * vb[2];
			c[2] = ma[2][0] * vb[0] + ma[2][1] * vb[1] + ma[2][2] * vb[2];
			return c;
		}
		inline friend mat operator * (const mat& ma, const mat& mb)
		{
			mat c;
			c[0][0] = ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0] + ma[0][2] * mb[2][0];
			c[0][1] = ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1] + ma[0][2] * mb[2][1];
			c[0][2] = ma[0][0] * mb[0][2] + ma[0][1] * mb[1][2] + ma[0][2] * mb[2][2];
			c[1][0] = ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0] + ma[1][2] * mb[2][0];
			c[1][1] = ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1] + ma[1][2] * mb[2][1];
			c[1][2] = ma[1][0] * mb[0][2] + ma[1][1] * mb[1][2] + ma[1][2] * mb[2][2];
			c[2][0] = ma[2][0] * mb[0][0] + ma[2][1] * mb[1][0] + ma[2][2] * mb[2][0];
			c[2][1] = ma[2][0] * mb[0][1] + ma[2][1] * mb[1][1] + ma[2][2] * mb[2][1];
			c[2][2] = ma[2][0] * mb[0][2] + ma[2][1] * mb[1][2] + ma[2][2] * mb[2][2];
			return c;
		}

		inline mat& operator= (const mat& m)
		{
            (*this)[0][0] = m[0][0]; (*this)[0][1] = m[0][1]; (*this)[0][2] = m[0][2];
            (*this)[1][0] = m[1][0]; (*this)[1][1] = m[1][1]; (*this)[1][2] = m[1][2];
            (*this)[2][0] = m[2][0]; (*this)[2][1] = m[2][1]; (*this)[2][2] = m[2][2];
			return (*this);
		}

        inline type& val(const std::size_t& n, const std::size_t& m) { return (*this)[n][m]; };
        inline const type& val(const std::size_t& n, const std::size_t& m) const { return (*this)[n][m]; };
		inline vec<type> row(const std::size_t& n) const { return {val(n, 0), val(n, 1), val(n, 2)}; };
		inline vec<type> col(const std::size_t& m) const { return {val(0, m), val(1, m), val(2, m)}; };


		inline type det() const
		{
			type sum = 0;
            sum += (*this)[0][0] * (*this)[1][1] * (*this)[2][2];
            sum += (*this)[0][1] * (*this)[1][2] * (*this)[2][0];
            sum += (*this)[0][2] * (*this)[1][0] * (*this)[2][1];
            sum -= (*this)[0][0] * (*this)[1][2] * (*this)[2][1];
            sum -= (*this)[0][1] * (*this)[1][0] * (*this)[2][2];
            sum -= (*this)[0][2] * (*this)[1][1] * (*this)[2][0];
			return sum;
		};								//得到行列式的值
		inline mat adjmat() const
		{
			mat adj;
            adj[0][0] = (*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1];
            adj[1][0] = (*this)[1][2] * (*this)[2][0] - (*this)[1][0] * (*this)[2][2];
            adj[2][0] = (*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0];
            adj[0][1] = (*this)[0][2] * (*this)[2][1] - (*this)[0][1] * (*this)[2][2];
            adj[1][1] = (*this)[0][0] * (*this)[2][2] - (*this)[0][2] * (*this)[2][0];
            adj[2][1] = (*this)[0][1] * (*this)[2][0] - (*this)[0][0] * (*this)[2][1];
            adj[0][2] = (*this)[0][1] * (*this)[1][2] - (*this)[0][2] * (*this)[1][1];
            adj[1][2] = (*this)[0][2] * (*this)[1][0] - (*this)[0][0] * (*this)[1][2];
            adj[2][2] = (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			return adj;
		};							//伴随矩阵
		inline mat tramat() const
		{
			return {
                {(*this)[0][0],(*this)[1][0],(*this)[2][0]},
                {(*this)[0][1],(*this)[1][1],(*this)[2][1]},
                {(*this)[0][2],(*this)[1][2],(*this)[2][2]},
			};
		};							//转置矩阵	
		inline mat invmat() const
		{
			return (adjmat() / det());
		};							//逆矩阵	

		static mat rotate(type agex, type agey, type agez)
		{
			mat rotex{ {1, 0, 0}, { 0, std::cos(agex), -std::sin(agex) }, { 0, std::sin(agex), std::cos(agex) } };
			mat rotey{ {std::cos(agey), 0, -std::sin(agey)}, { 0, 1, 0 }, { std::sin(agey), 0, std::cos(agey) } };
			mat rotez{ {std::cos(agez), -std::sin(agez), 0}, { std::sin(agez), std::cos(agez), 0 }, { 0, 0, 1 } };
			return rotex * rotey * rotez;
		}
		static mat flexible(type varx, type vary, type varz)
		{
			mat flex;
			flex[0][0] = varx;
			flex[1][1] = vary;
			flex[2][2] = varz;
			return flex;
		}
		static mat rotate(vec<type> axis, type age)
		{
			type cos = std::cos(age);
			type sin = std::sin(age);
			mat add1{
				{ cos, 0, 0 },
				{ 0, cos, 0 },
				{ 0, 0, cos },
			};
			mat add2{
				{ axis[0] * axis[0], axis[0] * axis[1], axis[0] * axis[2] },
				{ axis[1] * axis[0], axis[1] * axis[1], axis[1] * axis[2] },
				{ axis[2] * axis[0], axis[2] * axis[1], axis[2] * axis[2] },
			};
			mat add3{
				{ 0, -axis[2], axis[1] },
				{ axis[2], 0, -axis[0] },
				{ -axis[1], axis[0], 0 },
			};
			mat rote = add1 + (add2 * (1 - cos)) + (add3 * sin);
			return rote;
		}
		static mat perspective(type n, type f)
		{
			mat perspec;
			type len = n / (n + f);
			perspec[0][0] = len;
			perspec[1][1] = len;
			perspec[0][0] = 1;
			perspec[1][1] = 1;
			perspec[2][2] = 1;
			return perspec;
		}
	};

	template<class type>
	using pot = xhqm::vec<type>;


	template<class type = xhqm::inte>
	class rect : public xhqm::hyper<type, 4>
	{
	public:
		using value_type = type;
		constexpr static xhqm::size dimension = 4;

		inline type& top() { return this->_Elems[0]; }
		inline type& boom() { return this->_Elems[1]; }
		inline type& left() { return this->_Elems[2]; }
		inline type& right() { return this->_Elems[3]; }
		inline const type& top() const { return this->_Elems[0]; }
		inline const type& boom() const { return this->_Elems[1]; }
		inline const type& left() const { return this->_Elems[2]; }
		inline const type& right() const { return this->_Elems[3]; }

		inline friend rect operator * (const type& a, const rect& b)
		{
			rect lrect;
			lrect._Elems[0] = a * b._Elems[0];
			lrect._Elems[1] = a * b._Elems[1];
			lrect._Elems[2] = a * b._Elems[2];
			lrect._Elems[3] = a * b._Elems[3];
			return lrect;
		}
		inline friend rect operator / (const type& a, const rect& b)
		{
			rect lrect;
			lrect._Elems[0] = a / b._Elems[0];
			lrect._Elems[1] = a / b._Elems[1];
			lrect._Elems[2] = a / b._Elems[2];
			lrect._Elems[3] = a / b._Elems[3];
			return lrect;
		}
		inline friend rect operator * (const rect& a, const type& b)
		{
			rect lrect;
			lrect._Elems[0] = a._Elems[0] * b;
			lrect._Elems[1] = a._Elems[1] * b;
			lrect._Elems[2] = a._Elems[2] * b;
			lrect._Elems[3] = a._Elems[3] * b;
			return lrect;
		}
		inline friend rect operator / (const rect& a, const type& b)
		{
			rect lrect;
			lrect._Elems[0] = a._Elems[0] / b;
			lrect._Elems[1] = a._Elems[1] / b;
			lrect._Elems[2] = a._Elems[2] / b;
			lrect._Elems[3] = a._Elems[3] / b;
			return lrect;
		}

		rect(const type& valt = type(), const type& valb = type(), const type& vall = type(), const type& valr = type())
		{
			top() = valt;
			boom() = valb;
			left() = vall;
			right() = valr;
		};
		rect(const xhqm::hyper<type, 2>& star = xhqm::hyper<type, 2>(),
			const xhqm::hyper<type, 2>& stop = xhqm::hyper<type, 2>()) {
			top() = star[0];
			boom() = stop[0];
			left() = star[1];
			right() = stop[1];
		};

		inline const type height() const { return top() - boom(); }
		inline const type width() const { return right() - left(); }
		inline bool isgood() const { return (height() >= 0 && width() >= 0); }
	};

	template<xhqm::size dim, class type = xhqm::measure>
	class poit : public xhqm::hyper<type, dim>
	{
	public:
		inline friend poit operator + (const type& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a + b[i];
			return c;
		}
		inline friend poit operator - (const type& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a - b[i];
			return c;
		}
		inline friend poit operator * (const type& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a * b[i];
			return c;
		}
		inline friend poit operator / (const type& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a / b[i];
			return c;
		}
		inline friend poit operator + (const poit& a, const type& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] + b;
			return c;
		}
		inline friend poit operator - (const poit& a, const type& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] - b;
			return c;
		}
		inline friend poit operator * (const poit& a, const type& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] * b;
			return c;
		}
		inline friend poit operator / (const poit& a, const type& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] / b;
			return c;
		}
		inline friend poit operator + (const poit& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] + b[i];
			return c;
		}
		inline friend poit operator - (const poit& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] - b[i];
			return c;
		}
		inline friend poit operator * (const poit& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] * b[i];
			return c;
		}
		inline friend poit operator / (const poit& a, const poit& b)
		{
			poit c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] / b[i];
			return c;
		}
		inline friend poit operator ^ (const poit& a, const poit& b)
		{
			return ((a + b) / 2);
		}

		inline operator xhqm::poit<dim - 1, type>() const {
			xhqm::poit<dim - 1, type> c;
            for (xhqm::size i = 0; i < dim - 1; ++i)
                c[i] = (*this)[i];
			return c;
		}
		inline operator xhqm::poit<dim + 1, type>() const {
			initialize<type> inittype;
			xhqm::poit<dim + 1, type> c;
			for (xhqm::size i = 0; i < dim; ++i)
                c[i] = (*this)[i];
            c[dim] = inittype.value;
			return c;
		}

		poit() : xhqm::hyper<type, dim>() {}
		poit(const std::initializer_list<type>& list) : xhqm::hyper<type, dim>() {
			for (xhqm::size i = 0; i < dim; ++i)
                (*this)[i] = *(list.begin() + i);
		}

		template<class function, typename ... Args>
		void execfun(function fun, Args ...args) {
			for (auto& vec : (*this))
				vec = fun(vec, std::forward<Args>(args)...);
		}

		constexpr xhqm::size dime() const noexcept {
			return dim;
		}

        inline const type& operator[](xhqm::size _Pos) const { return xhqm::hyper<type, dim>::operator[](_Pos); }
        inline type& operator[](xhqm::size _Pos) { return xhqm::hyper<type, dim>::operator[](_Pos); }
        inline const type& x() const { return (*this)[0]; }
        inline const type& y() const { return (*this)[1]; }
        inline const type& z() const { return (*this)[2]; }
        inline type& x() { return this->operator[](0); }
        inline type& y() { return this->operator[](1); }
        inline type& z() { return this->operator[](2); }

		using value_type = type;
		constexpr static xhqm::size dimension = dim;
	};

	template<xhqm::size dim, class type = xhqm::measure>
	class vect : public xhqm::hyper<type, dim>
	{
	public:
		inline friend vect operator + (const type& a, const vect& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a + b[i];
			return c;
		}
		inline friend vect operator - (const type& a, const vect& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a - b[i];
			return c;
		}
		inline friend vect operator * (const type& a, const vect& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a * b[i];
			return c;
		}
		inline friend vect operator / (const type& a, const vect& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a / b[i];
			return c;
		}
		inline friend vect operator + (const vect& a, const type& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] + b;
			return c;
		}
		inline friend vect operator - (const vect& a, const type& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] - b;
			return c;
		}
		inline friend vect operator * (const vect& a, const type& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] * b;
			return c;
		}
		inline friend vect operator / (const vect& a, const type& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] / b;
			return c;
		}
		inline friend vect operator + (const vect& a, const vect& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] + b[i];
			return c;
		}
		inline friend vect operator - (const vect& a, const vect& b)
		{
			vect c;
			for (xhqm::size i = 0; i < dim; i++)
                c[i] = a[i] - b[i];
			return c;
		}

		inline friend type operator * (const vect& a, const vect& b)
		{
			return vect::dot(a, b);
		}
		inline friend vect operator / (const vect& a, const vect& b)
		{
			return vect::mul(a, b);
		}

		inline operator xhqm::vect<dim - 1, type>() const {
			xhqm::vect<dim - 1, type> c;
			for (xhqm::size i = 0; i < dim - 1; ++i)
                c[i] = (*this)[i];
			return c;
		}
		inline operator xhqm::vect<dim + 1, type>() const {
			initialize<type> inittype;
			xhqm::vect<dim + 1, type> c;
			for (xhqm::size i = 0; i < dim; ++i)
                c[i] = (*this)[i];
            c[dim] = inittype.value;
			return c;
		}
		inline operator xhqm::poit<dim, type>() const {
			xhqm::poit<dim, type> c;
			for (xhqm::size i = 0; i < dim - 1; ++i)
                c[i] = (*this)[i];
			return c;
		}

		vect() : xhqm::hyper<type, dim>() {}
		vect(const std::initializer_list<type>& list) : xhqm::hyper<type, dim>() {
			for (xhqm::size i = 0; i < dim; ++i)
                (*this)[i] = *(list.begin() + i);
		}
		explicit vect(const xhqm::poit<dim, type>& pot) : xhqm::hyper<type, dim>(pot) {}
		explicit vect(const xhqm::poit<dim, type>& star, const xhqm::poit<dim, type>& stop) : xhqm::hyper<type, dim>(stop - star) {}

		template<class function, typename ... Args>
		void execfun(function fun, Args ...args) {
			for (auto& vec : (*this))
				vec = fun(vec, std::forward<Args>(args)...);
		}

		constexpr xhqm::size dime() const noexcept {
			return dim;
		}

		inline type modulus() const { return (type)std::sqrt((*this) * (*this)); }
		inline vect normalvec() const { return (*this) / modulus(); }
		inline void normalize() { (*this) = (*this) / modulus(); }

		static type dot(const vect& a, const vect& b)
		{
			initialize<type> inittype;
			type sum = inittype.value;
			for (xhqm::size i = 0; i < dim; i++)
                sum = sum + (a[i] * b[i]);
			return sum;
		}
		static vect mul(const vect& a, const vect& b)
		{
			vect c;
			if constexpr (dim == 1)
			{
				//数乘
				c[0] = a[0] * b[0];
			}
			if constexpr (dim == 2)
			{
				//中点
				c[0] = (a[0] + b[0]) / 2;
				c[1] = (a[1] + b[1]) / 2;
			}
			if constexpr (dim == 3)
			{
				//叉乘
				c[0] = a[1] * b[2] - a[2] * b[1];
				c[1] = a[2] * b[0] - a[0] * b[2];
				c[2] = a[0] * b[1] - a[1] * b[0];
			}
			return c;
		}

		using value_type = type;
		constexpr static xhqm::size dimension = dim;
	};

	template<xhqm::size m, xhqm::size n, class type = xhqm::measure>
	class matr : public xhqm::hyper<type, m, n>
	{
		//static_assert(m == 0 || n == 0, "m == 0 || n == 0");
	public:
		inline friend matr operator + (const type& a, const matr& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
				c[i][j] = a + b[i][j];
			return c;
		}
		inline friend matr operator - (const type& a, const matr& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a - b[i][j];
			return c;
		}
		inline friend matr operator * (const type& a, const matr& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a * b[i][j];
			return c;
		}
		inline friend matr operator / (const type& a, const matr& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a / b[i][j];
			return c;
		}
		inline friend matr operator + (const matr& a, const type& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a[i][j] + b;
			return c;
		}
		inline friend matr operator - (const matr& a, const type& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a[i][j] - b;
			return c;
		}
		inline friend matr operator * (const matr& a, const type& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a[i][j] * b;
			return c;
		}
		inline friend matr operator / (const matr& a, const type& b)
		{
			matr c;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					c[i][j] = a[i][j] / b;
			return c;
		}



		template<class function, typename ... Args>
		void execfun(function fun, Args ...args) {
			for (auto& vec : (*this))
				for (auto& var : vec)
					var = fun(var, std::forward<Args>(args)...);
		}
		//子矩阵
		template<xhqm::size km, xhqm::size kn>
		inline xhqm::matr<km, kn, type> kidmat(const xhqm::hyper<xhqm::size, km>& selm, const xhqm::hyper<xhqm::size, kn>& seln) const
		{
			xhqm::matr<km, kn, type> kid;
			for (xhqm::size i = 0; i < km; i++)
				for (xhqm::size j = 0; j < kn; j++)
					kid[j][i] = (*this)[selm[i]][seln[j]];
			return kid;
		};

		inline xhqm::matr<m - 1, n - 1, type> kidmat(const xhqm::size& delm, const xhqm::size& deln) const
		{
			xhqm::matr<m - 1, n - 1, type> kid;
			for (xhqm::size i = 0; i < m - 1; i++)
				for (xhqm::size j = 0; j < n - 1; j++)
					kid[j][i] = (*this)[i < delm ? i : i + 1][j < deln ? j : j + 1];
			return kid;
		};
		//转置矩阵
		inline xhqm::matr<n, m, type> tramat() const
		{
			xhqm::matr<n, m, type> tra;
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
					tra[j][i] = (*this)[i][j];
			return tra;
		};

		//得到行列式的值
		inline type det() const
		{
			static_assert(m == n, "m != n");

			if constexpr (m == 1 && n == 1)
				return (*this)[0][0];
			if constexpr (m > 1 || n > 1)
			{
				type mea = 0;
				for (xhqm::size i = 0; i < m; i++)
					mea += ((*this)[i][0] * kidmat(i, 0).det() * (i % 2 == 0 ? 1 : -1));
				return mea;
			}


			//type val = 0;
			//matr cop = (*this);
			//for (xhqm::size i = 0; i < m; ++i)
			//{
			//	for (xhqm::size j = i + 1; j < m; ++j)
			//	{
			//		type K = cop[j][0] / cop[i][0];
			//		for (xhqm::size k = n - 1; k <= i; --k)
			//		{
			//			cop[j][k] = cop[j][k] - K * cop[i][k];
			//		}
			//	}
			//}
			//for (xhqm::size i = 0; i < m; ++i)
			//{
			//	for (xhqm::size j = i + 1; j < m; ++j)
			//	{
			//	}
			//}
			//return 0;
		};
		//伴随矩阵
		inline matr adjmat() const
		{
			static_assert(m == n, "m != n");

			matr adj;
			xhqm::inte sig = 0;
			for (xhqm::size  i = 0; i < m; i++) {
				for (xhqm::size  j = 0; j < n; j++) {
					sig = (i + j) % 2 == 0 ? 1 : -1;
					adj[j][i] = kidmat(i, j).det() * sig;
				}
			}
			return adj;
		};
		//逆矩阵	
		inline matr invmat() const
		{
			static_assert(m == n, "m != n");

			matr inv;
			type dete = det();
			initialize<type> typeinit;
			if (xhqm_abs(dete, typeinit.value) > preci)
				inv = adjmat() / dete;
			return inv;
		};


		matr(bool ide = false) : xhqm::hyper<type, m, n>() {
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
                    (*this)[i][j] = ide && i == j ? 1 : 0;
		}
		matr(const type& value) : xhqm::hyper<type, m, n>() {
			for (xhqm::size i = 0; i < m; i++)
				for (xhqm::size j = 0; j < n; j++)
                    (*this)[i][j] = value;
		}
		matr(const std::initializer_list<xhqm::hyper<type, n>>& list) : xhqm::hyper<type, m, n>() {
			for (xhqm::size i = 0; i < m; ++i)
                (*this)[i] = *(list.begin() + i);
		}

		constexpr xhqm::hyper<xhqm::size, 2> dime() const noexcept {
			return { m, n };
		}

		inline xhqm::vect<n, type> row(const xhqm::size& pos) const
		{
			xhqm::vect<n, type> res;
			for (xhqm::size j = 0; j < n; j++)
                res[j] = (*this)[pos][j];
			return res;
		};
		inline xhqm::vect<m, type> col(const xhqm::size& pos) const
		{
			xhqm::vect<m, type> res;
			for (xhqm::size i = 0; i < m; i++)
                res[i] = (*this)[i][pos];
			return res;
		};

		using value_type = type;
		constexpr static std::array<xhqm::size, 2> dimension = { m, n };
	};

	template<xhqm::size kl, xhqm::size km, xhqm::size kn, class type>
	inline xhqm::matr<kl, kn, type> operator * (const xhqm::matr<kl, km, type>& a, const xhqm::matr<km, kn, type>& b)
	{
		xhqm::matr<kl, kn, type> c;
		for (xhqm::size i = 0; i < kl; i++)
		{
			for (xhqm::size j = 0; j < kn; j++)
			{
				c[i][j] = 0;
				for (xhqm::size k = 0; k < km; k++)
					c[i][j] += (a[i][k] * b[k][j]);
			}
		}
		return c;
	}


	using pot4 = xhqm::poit<4, xhqm::measure>;
	using vec4 = xhqm::vect<4, xhqm::measure>;
	using pot3 = xhqm::poit<3, xhqm::measure>;
	using vec3 = xhqm::vect<3, xhqm::measure>;
	using pot2 = xhqm::poit<2, xhqm::measure>;
	using vec2 = xhqm::vect<2, xhqm::measure>;
	using pot1 = xhqm::poit<1, xhqm::measure>;
	using vec1 = xhqm::vect<1, xhqm::measure>;
}
#endif
