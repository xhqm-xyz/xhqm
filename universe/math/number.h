#ifndef XHQM_MATH_NUMBER
#define XHQM_MATH_NUMBER
#include "../../head.h"
#include <complex>
namespace xhqm
{
	namespace math
	{
		template<class value_type>
		class number {
		public:
			value_type value;
		public:
			number() {};
			number(value_type val) : value(val) {};
			explicit operator value_type() const noexcept { return value; };
		};

        template<class value_type>
        using complex = std::complex<value_type>;

        template <typename value_type>
        class dualnum
        {
            value_type value[2];
        public:
            dualnum(value_type val, value_type val2) { value[0] = val; value[1] = val2; }
            dualnum(const dualnum<value_type>& rhs)
            {
                (*this) = rhs;
            }
            dualnum() { value[0] = value_type(); value[1] = value_type(); }
            ~dualnum() {}

            //explicit operator value_type() const noexcept { return value[1]; }
            const value_type& operator () (std::size_t i) const { return value[i]; }
            value_type& operator[] (std::size_t i) { return value[i]; }
            dualnum<value_type> operator + () const { return value[0] *= +1; value[1] *= +1; }
            dualnum<value_type> operator - () const { return value[0] *= -1; value[1] *= -1; }
            dualnum<value_type> conj() const { return dualnum<value_type>(value[0], -value[1]); }

            dualnum<value_type>& operator += (const value_type& rhs) { value[0] += rhs; return *this; }
            dualnum<value_type>& operator -= (const value_type& rhs) { value[0] -= rhs; return *this; }
            dualnum<value_type>& operator *= (const value_type& rhs) { value[0] *= rhs; value[1] *= rhs; return *this; }
            dualnum<value_type>& operator /= (const value_type& rhs) { value[0] /= rhs; value[1] /= rhs; return *this; }
            dualnum<value_type>& operator += (const dualnum<value_type>& rhs) { value[0] += rhs.value[0]; value[1] += rhs.value[1]; return *this; }
            dualnum<value_type>& operator -= (const dualnum<value_type>& rhs) { value[0] -= rhs.value[0]; value[1] -= rhs.value[1]; return *this; }
            dualnum<value_type>& operator *= (const dualnum<value_type>& rhs) { value[1] = value[0] * rhs.value[1] + value[1] * rhs.value[0]; value[0] = value[0] * rhs.value[0]; return *this; }
            dualnum<value_type>& operator /= (const dualnum<value_type>& rhs) { (*this) *= rhs.conj(); (*this) /= (rhs.value[0] * rhs.value[0]); return *this; }


            inline friend dualnum<value_type> operator + (const dualnum<value_type>& lhs, const value_type& rhs) { return dualnum<value_type>(lhs) += rhs; }
            inline friend dualnum<value_type> operator - (const dualnum<value_type>& lhs, const value_type& rhs) { return dualnum<value_type>(lhs) -= rhs; }
            inline friend dualnum<value_type> operator * (const dualnum<value_type>& lhs, const value_type& rhs) { return dualnum<value_type>(lhs) *= rhs; }
            inline friend dualnum<value_type> operator / (const dualnum<value_type>& lhs, const value_type& rhs) { return dualnum<value_type>(lhs) /= rhs; }
            inline friend dualnum<value_type> operator + (const value_type& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(+lhs, 0) += rhs; }
            inline friend dualnum<value_type> operator - (const value_type& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(-lhs, 0) -= rhs; }
            inline friend dualnum<value_type> operator * (const value_type& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(rhs) *= lhs; }
            inline friend dualnum<value_type> operator / (const value_type& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(lhs, 0) /= rhs; }
            inline friend dualnum<value_type> operator + (const dualnum<value_type>& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(lhs) += rhs; }
            inline friend dualnum<value_type> operator - (const dualnum<value_type>& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(lhs) -= rhs; }
            inline friend dualnum<value_type> operator * (const dualnum<value_type>& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(lhs) *= rhs; }
            inline friend dualnum<value_type> operator / (const dualnum<value_type>& lhs, const dualnum<value_type>& rhs) { return dualnum<value_type>(lhs) /= rhs; }


            template <typename T> operator
                T () const {
                return static_cast<T>(value[0]);
            }
        };

        ////幂函数
        //static value_type power(value_type val, xhqm::measure a) { return val ^ a; };
        ////指数函数
        //static value_type exp(value_type val) { return val; };
        ////对数函数
        //static value_type log(value_type val) { return val; };
        
        ////三角函数
        //static value_type sin(value_type val) { return val; };
        //static value_type cos(value_type val) { return val; };
        ////反三角函数
        //static value_type arcsin(value_type val) { return val; };
        //static value_type arccos(value_type val) { return val; };
        template<typename value_type>
        dualnum<value_type> pow(const dualnum<value_type>& val, value_type exp)
        {
            return dualnum<value_type>(std::pow<value_type>(val(0), exp),
                exp * std::pow<value_type>(val(0), exp - value_type(1)) * val(1));
        }
        template<typename value_type>
        dualnum<value_type> sqrt(const dualnum<value_type>& val)
        {
            value_type val_0_sqrt = std::sqrt(val(0));
            if (val_0_sqrt < xhqm::preci)
                return dualnum<value_type>(value_type(0), value_type(0.5) * val(1) * INFINITY);
            return dualnum<value_type>(val_0_sqrt, value_type(0.5) * val(1) / val_0_sqrt);
        }

        template<typename value_type>
        dualnum<value_type> exp(const dualnum<value_type>& val)
        {
            value_type exp_a = std::exp<value_type>(val(0));
            return dualnum<value_type>(exp_a, exp_a * val(1));
        }
        template<typename value_type>
        dualnum<value_type> log(const dualnum<value_type>& val)
        {
            return dualnum<value_type>(std::log(val(0)), val(1) / val(0));
        }

        template<typename value_type> 
        dualnum<value_type> sin(const dualnum<value_type>& val)
        {
            return dualnum<value_type>(std::sin(val(0)), std::cos(val(0)) * val(1));
        }
        template<typename value_type> 
        dualnum<value_type> cos(const dualnum<value_type>& val)
        {
            return dualnum<value_type>(std::cos(val(0)), std::sin(val(0))* val(1) * value_type(-1));
        }

        template<typename value_type> 
        dualnum<value_type> asin(const dualnum<value_type>& val)
        {
            return dualnum<value_type>(std::asin(val(0)), val(1) / std::sqrt(1 - val(0) * val(0)));
        }
        template<typename value_type> 
        dualnum<value_type> acos(const dualnum<value_type>& val)
        {
            return dualnum<value_type>(std::asin(val(0)), -val(1) / std::sqrt(1 - val(0) * val(0)));
        }
	}
}
#endif
