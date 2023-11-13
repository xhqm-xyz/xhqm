#ifndef XHQM_MATH_VECTOR
#define XHQM_MATH_VECTOR
#include "../../head.h"
namespace xhqm
{
	namespace math
	{
		template<class type = xhqm::measure>
		class vector :public std::vector<type> {
		public:
			using size_type = typename std::vector<type>::size_type;

			static type cos(const vector<type>& A, const vector<type>& B) { return (A * B) / (vector<type>::typesqrt(A * A) * vector<type>::typesqrt(B * B)); }
			static type sin(const vector<type>& A, const vector<type>& B) { type res = cos(A, B); return vector<type>::typesqrt(1 - (res * res)); }
			static type dot(const vector<type>& A, const vector<type>& B) //点乘
			{
				initialize<type> init;
				size_type dim = xmin(A.dimension(), B.dimension());
				for (size_type i = 0; i < dim; i++)
					init.value = init.value + A[i] * B[i];
				return init.value;
			}
			static vector<type> mul(size_type dim, ...); //伪叉乘


			static bool dele(vector<type>& veca, const size_type& n)
			{
				if (veca.dimension() <= n) return false;
				veca.erase(veca.begin() + n);
				return true;
			};
			static bool inst(vector<type>& veca, const size_type& n, const type& var)
			{
				if (veca.dimension() < n) return false;
				veca.insert(veca.begin() + n, var);
				return true;
			};
			static bool normaliza(vector<type>& veca) {
				initialize<type> typeinit;
				initialize<type> typeinitval(veca.modulus());
				if (typeinitval.value - typeinit.value > preci)
				{
					for (type& val : veca)
						val = val / typeinitval.value;
					return true;
				}
				return false;
			}

			static type modulus(const vector<type>& veca) { return vector<type>::typesqrt(vector<type>::dot(veca, veca)); }
			static type typesqrt(const type& val) { return (type)std::sqrt((measure)val); }
		public:
			inline vector() : std::vector<type>() {};
			inline vector(const vector& right) : std::vector<type>(right) {};
			inline vector(const std::vector<type>& right) : std::vector<type>(right) {};
			inline vector(const size_type& count) : std::vector<type>(count) {};
			inline vector(const size_type& count, const type& val) : std::vector<type>(count, val) {};
			inline vector(std::initializer_list<type> list) : std::vector<type>(list) {};
		public:
			inline void fill(const type& var) { for (auto& thisvar : *this) thisvar = var; };

			inline vector<type> dele(const size_type& n)
			{
				vector<type> copy = (*this);
				vector<type>::dele(copy, n);
				return copy;
			};
			inline vector<type> inst(const size_type& n, const type& var) {

				vector<type> copy = (*this);
				vector<type>::inst(copy, n, var);
				return copy;
			};
			inline vector<type> normaliza()
			{
				vector<type> copy = (*this);
				vector<type>::normaliza(copy);
				return copy;
			};

			inline vector<type> this_dele(const size_type& n)
			{
				vector<type>::dele((*this), n);
				return (*this);
			};
			inline vector<type> this_inst(const size_type& n, const type& var) {

				vector<type>::inst((*this), n, var);
				return (*this);
			};
			inline vector<type> this_normaliza()
			{
				vector<type>::normaliza((*this));
				return (*this);
			};

			inline type modulus() const { return vector<type>::modulus(*this); };
			inline size_type dimension() const { return std::vector<type>::size(); };
			inline size_type dimension(size_type& len) const { len = std::vector<type>::size(); return len; };

			inline bool operator != (const vector<type>& vect) const { return (((*this) - vect).modulus() > (measure)xhqm::preci); }
			inline bool operator == (const vector<type>& vect) const { return (((*this) - vect).modulus() <= (measure)xhqm::preci); }

			//inline type& operator[](const size_type& pos) { return std::vector<type>::operator[](pos); };
			inline vector<type>& operator=(const vector<type>& right) { std::vector<type>::operator=(right); return (*this); };
			inline vector<type>& operator=(const std::vector<type>& right) { std::vector<type>::operator=(right); return (*this); };
			inline vector<type>& operator=(std::initializer_list<type> list) { std::vector<type>::operator=(list); return (*this); };

			inline friend vector<type> operator +(const vector<type>& A) { vector<type> C(A); for (auto& var : C) var = +var; return C; };
			inline friend vector<type> operator -(const vector<type>& A) { vector<type> C(A); for (auto& var : C) var = -var; return C; };

			inline friend vector<type> operator + (const type& a, const vector<type>& B) { vector<type> C(B); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = a + B[i];  return C; };
			inline friend vector<type> operator - (const type& a, const vector<type>& B) { vector<type> C(B); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = a - B[i];  return C; };
			inline friend vector<type> operator * (const type& a, const vector<type>& B) { vector<type> C(B); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = a * B[i];  return C; };
			inline friend vector<type> operator / (const type& a, const vector<type>& B) { vector<type> C(B); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = a / B[i];  return C; };
			inline friend vector<type> operator + (const vector<type>& A, const type& b) { vector<type> C(A); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = A[i] + b;  return C; };
			inline friend vector<type> operator - (const vector<type>& A, const type& b) { vector<type> C(A); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = A[i] - b;  return C; };
			inline friend vector<type> operator * (const vector<type>& A, const type& b) { vector<type> C(A); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = A[i] * b;  return C; };
			inline friend vector<type> operator / (const vector<type>& A, const type& b) { vector<type> C(A); size_type dim; C.dimension(dim); for (size_type i = 0; i < dim; i++) C[i] = A[i] / b;  return C; };

			inline friend vector<type> operator + (const vector<type>& A, const vector<type>& B)
			{
				size_type lenA = A.dimension();
				size_type lenB = B.dimension();
				vector<type> C(xhqm_max(lenA, lenB));
				for (size_type i = 0; i < lenA; i++)
					C[i] = C[i] + A[i];
				for (size_type i = 0; i < lenB; i++)
					C[i] = C[i] + B[i];
				return C;
			}
			inline friend vector<type> operator - (const vector<type>& A, const vector<type>& B)
			{
				size_type lenA = A.dimension();
				size_type lenB = B.dimension();
				vector<type> C(xhqm_max(lenA, lenB));
				for (size_type i = 0; i < lenA; i++)
					C[i] = C[i] + A[i];
				for (size_type i = 0; i < lenB; i++)
					C[i] = C[i] - B[i];
				return C;
			}
			inline friend type operator * (const vector<type>& A, const vector<type>& B) { return vector<type>::dot(A, B); }
			//inline friend vector<type> operator / (const vector<type>& A, const vector<type>& B) { return vector<type>::mul(3, A, B); }

			inline vector<type> operator += (const type& b) { for (auto& var : (*this)) var = var + b;  return (*this); };
			inline vector<type> operator -= (const type& b) { for (auto& var : (*this)) var = var - b;  return (*this); };
			inline vector<type> operator *= (const type& b) { for (auto& var : (*this)) var = var * b;  return (*this); };
			inline vector<type> operator /= (const type& b) { for (auto& var : (*this)) var = var / b;  return (*this); };

			inline vector<type> operator += (const vector<type>& B)
			{
				initialize<type> typeinit;
				size_type len = dimension();
				size_type lenB = B.dimension();
				if (len < lenB) std::vector<type>::insert(std::vector<type>::end(), lenB - len, typeinit.value);
				for (size_type i = 0; i < lenB; i++) (*this)[i] = (*this)[i] + B[i];
				return (*this);
			}
			inline vector<type> operator -= (const vector<type>& B)
			{
				initialize<type> typeinit;
				size_type len = dimension();
				size_type lenB = B.dimension();
				if (len < lenB) std::vector<type>::insert(std::vector<type>::end(), lenB - len, typeinit.value);
				for (size_type i = 0; i < lenB; i++) (*this)[i] = (*this)[i] - B[i];
				return (*this);
			}



			template<class function, typename ... Args>
			void execfun(function fun, Args ...args) {
				for (auto& var : (*this)) var = fun(var, std::forward<Args>(args)...);
			}


		};
	}
}
#endif
