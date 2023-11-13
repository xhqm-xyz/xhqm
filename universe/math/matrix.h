#ifndef XHQM_MATH_MATRIX
#define XHQM_MATH_MATRIX
#include "../../head.h"
#include "vector.h"
namespace xhqm
{
	namespace math
	{
		template<class type = xhqm::measure>
		class matrix :public std::vector<std::vector<type>> {
			void dimension()
			{
				size_type rowdim = std::vector<std::vector<type>>::size();
				size_type coldim = 0;
				if (rowdim)
					for (auto& raw : (*this))
						coldim = (coldim > raw.size() ? coldim : raw.size());

				initialize<type> typeinit;
				for (auto& raw : (*this))
					if (raw.size() < coldim)
						raw.std::vector<type>::insert(raw.std::vector<type>::end(), coldim - raw.size(), typeinit.value);
			}
		public:
			using size_type = typename std::vector<std::vector<type>>::size_type;
			using value_type = typename std::vector<std::vector<type>>::value_type::value_type;
			inline static matrix<type> idemat(const size_type& dim)
			{
				matrix<type> mate(dim, dim);
				for (size_type i = 0; i < dim; i++)
					mate[i][i] = 1;
				return mate;
			};
		public:
			inline matrix() : std::vector<std::vector<type>>() {};
			inline matrix(const matrix& right) : std::vector<std::vector<type>>(right) { dimension(); };
			inline matrix(const size_type& rowdim, const size_type& coldim) : std::vector<std::vector<type>>(rowdim, std::vector<type>(coldim)) {};
			inline matrix(const size_type& rowdim, const size_type& coldim, const type& val) : std::vector<std::vector<type>>(rowdim, std::vector<type>(coldim, val)) {};

			inline matrix(std::initializer_list<std::vector<type>> list) : std::vector<std::vector<type>>(list) { dimension(); };
		public:
			inline bool operator != (const matrix<type>& mat) {
				initialize<type> typeinit;
				matrix diff = *this - mat;
				for (auto& varrow : diff)
					for (auto& var : varrow)
						if (xabs(var, typeinit.value) > preci)
							return true;
				return false;
			}
			inline bool operator == (const matrix<type>& mat) {
				initialize<type> typeinit;
				matrix diff = *this - mat;
				for (auto& varrow : diff)
					for (auto& var : varrow)
						if (xabs(var, typeinit.value) > preci)
							return false;
				return true;
			}

			//inline std::vector<type>& operator[](const size_type& pos) { return std::vector<std::vector<type>>::operator[](pos); dimension(); };
			inline matrix<type>& operator=(const matrix<type>& right) { std::vector<std::vector<type>>::operator=(right); dimension(); return (*this); };
			inline matrix<type>& operator=(std::initializer_list<std::vector<type>> list) { std::vector<std::vector<type>>::operator=(list); dimension(); return (*this); };

			inline friend matrix<type> operator +(const matrix<type>& A) { matrix<type> C(A); for (auto& vec : C) for (auto& var : vec) var = +var; return C; };
			inline friend matrix<type> operator -(const matrix<type>& A) { matrix<type> C(A); for (auto& vec : C) for (auto& var : vec) var = -var; return C; };

			inline friend matrix<type> operator + (const matrix<type>& A, const matrix<type>& B)
			{
				size_type _An = 0;
				size_type _Am = 0;
				size_type _Bn = 0;
				size_type _Bm = 0;
				matrix<type> copyA(A);
				matrix<type> copyB(B);
				copyA.dimension(_An, _Am);
				copyB.dimension(_Bn, _Bm);
				matrix<type> res(xmax(_An, _Bn), xmax(_Am, _Bm));
				for (size_type i = 0; i < _An; i++)
					for (size_type j = 0; j < _Am; j++)
						res[i][j] = res[i][j] + copyA[i][j];
				for (size_type i = 0; i < _Bn; i++)
					for (size_type j = 0; j < _Bm; j++)
						res[i][j] = res[i][j] + copyB[i][j];
				return res;
			};
			inline friend matrix<type> operator - (const matrix<type>& A, const matrix<type>& B)
			{
				size_type _An = 0;
				size_type _Am = 0;
				size_type _Bn = 0;
				size_type _Bm = 0;
				matrix<type> copyA(A);
				matrix<type> copyB(B);
				copyA.dimension(_An, _Am);
				copyB.dimension(_Bn, _Bm);
				matrix<type> res(xmax(_An, _Bn), xmax(_Am, _Bm));
				for (size_type i = 0; i < _An; i++)
					for (size_type j = 0; j < _Am; j++)
						res[i][j] = res[i][j] + copyA[i][j];
				for (size_type i = 0; i < _Bn; i++)
					for (size_type j = 0; j < _Bm; j++)
						res[i][j] = res[i][j] - copyB[i][j];
				return res;
			};
			inline friend matrix<type> operator * (const matrix<type>& A, const matrix<type>& B)
			{
				size_type _An = 0;
				size_type _Am = 0;
				size_type _Bn = 0;
				size_type _Bm = 0;
				A.dimension(_An, _Am);
				B.dimension(_Bn, _Bm);
				matrix<type> res(_An, _Bm);
				for (size_type i = 0; i < _An; i++)
					for (size_type j = 0; j < _Bm; j++)
						res[i][j] = A.row(i) * B.col(j);
				return res;
			};
			//inline friend matrix<type> operator / (const matrix<type>& A, const matrix<type>& B)
			//{
			//	matrix<type> C(B);
			//	return A * C.invmat();
			//};

			inline friend matrix<type> operator + (const type& a, const matrix<type>& B)
			{
				matrix<type> copy(B);
				for(auto&row : copy) for (auto& b : row) b = a + b;
				return copy;
			};
			inline friend matrix<type> operator - (const type& a, const matrix<type>& B)
			{
				matrix<type> copy(B);
				for (auto& row : copy) for (auto& b : row) b = a - b;
				return copy;
			};
			inline friend matrix<type> operator * (const type& a, const matrix<type>& B)
			{
				matrix<type> copy(B);
				for (auto& row : copy) for (auto& b : row) b = a * b;
				return copy;
			};
			inline friend matrix<type> operator / (const type& a, const matrix<type>& B)
			{
				matrix<type> copy(B);
				for (auto& row : copy) for (auto& b : row) b = a / b;
				return copy;
			};
			inline friend matrix<type> operator + (const matrix<type>& A, const type& b)
			{
				matrix<type> copy(A);
				for (auto& row : copy) for (auto& a : row) a = a + b;
				return copy;
			};
			inline friend matrix<type> operator - (const matrix<type>& A, const type& b)
			{
				matrix<type> copy(A);
				for (auto& row : copy) for (auto& a : row) a = a - b;
				return copy;
			};
			inline friend matrix<type> operator * (const matrix<type>& A, const type& b)
			{
				matrix<type> copy(A);
				for (auto& row : copy) for (auto& a : row) a = a * b;
				return copy;
			};
			inline friend matrix<type> operator / (const matrix<type>& A, const type& b)
			{
				matrix<type> copy(A);
				for (auto& row : copy) for (auto& a : row) a = a / b;
				return copy;
			};

			inline friend xhqm::math::vector<type> operator * (const xhqm::math::vector<type>& A, const matrix<type>& B)
			{
				size_type rowdim = 0;
				size_type coldim = 0;
				xhqm::math::vector<type> vec(A);
				xhqm::math::matrix<type> mat(B);
				mat.dimension(rowdim, coldim);
				xhqm::math::vector<type> res(coldim);
				for (size_type j = 0; j < coldim; j++)
					res[j] = vec * mat.col(j);
				return res;
			};
			inline friend xhqm::math::vector<type> operator * (const matrix<type>& A, const xhqm::math::vector<type>& B)
			{
				size_type rowdim = 0;
				size_type coldim = 0;
				xhqm::math::matrix<type> mat(A);
				xhqm::math::vector<type> vec(B);
				mat.dimension(rowdim, coldim);
				xhqm::math::vector<type> res(rowdim);
				for (size_type i = 0; i < rowdim; i++)
					res[i] = vec * mat.row(i);
				return res;
			};


			inline matrix<type> operator += (const type& b) { for (auto& row : (*this)) for (auto& var : row) var = var + b; return (*this); };
			inline matrix<type> operator -= (const type& b) { for (auto& row : (*this)) for (auto& var : row) var = var - b; return (*this); };
			inline matrix<type> operator *= (const type& b) { for (auto& row : (*this)) for (auto& var : row) var = var * b; return (*this); };
			inline matrix<type> operator /= (const type& b) { for (auto& row : (*this)) for (auto& var : row) var = var / b; return (*this); };

			inline matrix<type> operator += (const matrix<type>& B)
			{
				size_type Browdim = 0;
				size_type Bcoldim = 0;
				size_type thisrowdim = 0;
				size_type thiscoldim = 0;
				B.dimension(Browdim, Bcoldim);
				dimension(thisrowdim, thiscoldim);
				size_type rowdim = xmax(thisrowdim, Browdim);
				size_type coldim = xmax(thiscoldim, Bcoldim);
				initialize<type> typeinit;
				for (size_type i = 0; i < rowdim; i++)
				{
					if (i < thisrowdim)
					{
						for (size_type j = 0; j < coldim; j++)
							if (j < thiscoldim)
								(*this)[i][j] = (*this)[i][j] + B[i][j];
							else
								(*this)[i].std::vector<type>::push_back(typeinit.value + B[i][j]);
					}
					else
					{
						std::vector<std::vector<type>>::push_back(std::vector<type>());
						for (size_type j = 0; j < coldim; j++)
							(*this)[i].std::vector<type>::push_back(typeinit.value + B[i][j]);
					}
				}
				return (*this);
			}
			inline matrix<type> operator -= (const matrix<type>& B)
			{
				size_type Browdim = 0;
				size_type Bcoldim = 0;
				size_type thisrowdim = 0;
				size_type thiscoldim = 0;
				B.dimension(Browdim, Bcoldim);
				dimension(thisrowdim, thiscoldim);
				size_type rowdim = xmax(thisrowdim, Browdim);
				size_type coldim = xmax(thiscoldim, Bcoldim);
				initialize<type> typeinit;
				for (size_type i = 0; i < rowdim; i++)
				{
					if (i < thisrowdim)
					{
						for (size_type j = 0; j < coldim; j++)
							if (j < thiscoldim)
								(*this)[i][j] = (*this)[i][j] - B[i][j];
							else
								(*this)[i].std::vector<type>::push_back(typeinit.value - B[i][j]);
					}
					else
					{
						std::vector<std::vector<type>>::push_back(std::vector<type>());
						for (size_type j = 0; j < coldim; j++)
							(*this)[i].std::vector<type>::push_back(typeinit.value - B[i][j]);
					}
				}
				return (*this);
			}
		public:

			inline void dimension(size_type& rowdim, size_type& coldim) const
			{
				rowdim = std::vector<std::vector<type>>::size();
				coldim = (rowdim ? (*this)[0].size() : 0);
			}

			void fill(const type& var) { for (auto& thisvec : *this) for (auto& thisvar : thisvec) thisvar = var; };

			inline matrix<type> this_delerow(const size_type& n)
			{
				std::vector<std::vector<type>>::erase(std::vector<std::vector<type>>::begin() + n);
				return (*this);
			};//n下标
			inline matrix<type> this_delecol(const size_type& m)
			{
				for (auto& row : (*this))
					row.std::vector<type>::erase(row.std::vector<type>::begin() + m);
				return (*this);
			};//m下标
			inline matrix<type> this_dele(const size_type& n, const size_type& m)
			{
				std::vector<std::vector<type>>::erase(std::vector<std::vector<type>>::begin() + n);
				for (auto& row : (*this))
					row.std::vector<type>::erase(row.std::vector<type>::begin() + m);
				return (*this);
			};

			inline matrix<type> delerow(const size_type& n) const
			{
				matrix<type> copy = (*this);
				copy.std::vector<std::vector<type>>::erase(copy.std::vector<std::vector<type>>::begin() + n);
				return copy;
			};//n下标
			inline matrix<type> delecol(const size_type& m) const
			{
				matrix<type> copy = (*this);
				for (auto& row : copy)
					row.std::vector<type>::erase(row.std::vector<type>::begin() + m);
				return copy;
			};//m下标
			inline matrix<type> dele(const size_type& n, const size_type& m) const
			{
				matrix<type> copy = (*this);
				copy.std::vector<std::vector<type>>::erase(copy.std::vector<std::vector<type>>::begin() + n);
				for (auto& row : copy)
					row.std::vector<type>::erase(row.std::vector<type>::begin() + m);
				return copy;
			};

			inline xhqm::math::vector<type> row(const size_type& n) const
			{
				size_type rowsize = 0;
				size_type colsize = 0;
				dimension(rowsize, colsize);
				xhqm::initialize<type> inittype;
				xhqm::math::vector<type> res(colsize);
				for (size_type j = 0; j < colsize; j++)
					res[j] = j < (*this)[n].size() ? (*this)[n][j] : inittype.value;
				return res;
			};
			inline xhqm::math::vector<type> col(const size_type& m) const
			{
				size_type rowsize = 0;
				size_type colsize = 0;
				dimension(rowsize, colsize);
				xhqm::initialize<type> inittype;
				xhqm::math::vector<type> res(rowsize);
				for (size_type i = 0; i < rowsize; i++)
					res[i] = m < (*this)[i].size() ? (*this)[i][m] : inittype.value;
				return res;
			};
			inline type value(const size_type& n, const size_type& m) const
			{
				return (*this)[n][m];
			}

			inline type det() const
			{
				size_type rowdim = 0;
				size_type coldim = 0;
				dimension(rowdim, coldim);
				initialize<type> typeinit;
				if (rowdim != coldim || rowdim == 0 || coldim == 0)
					return typeinit.value;
				if (rowdim == 1 && coldim == 1)
					return (*this)[0][0];
				type sig = typeinit.value;
				type mea = typeinit.value;
				for (size_type i = 0; i < rowdim; i++) {
					sig = i % 2 == 0 ? 1 : -1;
					mea += ((*this)[i][0] * dele(i, 0).det() * sig);
				}return mea;
			};								//得到行列式的值
			inline matrix<type> invmat() const
			{
				matrix<type> inv;
				type dete = det();
				initialize<type> typeinit;
				if (xhqm_abs(dete, typeinit.value) > preci)
					inv = adjmat() / dete;
				return inv;
			};							//逆矩阵	
			inline matrix<type> tramat() const
			{
				size_type rowdim = 0;
				size_type coldim = 0;
				dimension(rowdim, coldim);
				matrix<type> tra(coldim, rowdim);
				for (size_type i = 0; i < rowdim; i++)
					for (size_type j = 0; j < coldim; j++)
						tra[j][i] = (*this)[i][j];
				return tra;
			};							//转置矩阵
			inline matrix<type> adjmat() const
			{
				size_type rowdim = 0;
				size_type coldim = 0;
				dimension(rowdim, coldim);
				matrix<type> adj(coldim, rowdim);
				if (rowdim != coldim || rowdim == 0 || coldim == 0)
					return adj;
				type sig = 0;
				for (size_type i = 0; i < rowdim; i++) {
					for (size_type j = 0; j < coldim; j++) {
						sig = (i + j) % 2 == 0 ? 1 : -1;
						adj[j][i] = dele(i, j).det() * sig;
					}
				}
				return adj;
			};							//伴随矩阵
			inline matrix<type> idemat() const
			{
				size_type rowdim = 0;
				size_type coldim = 0;
				dimension(rowdim, coldim);
				return matrix<type>::idemat(xmax(rowdim, coldim));
			};							//单位矩阵

			template<class function, typename ... Args>
			void execfun(function fun, Args ...args) {
				for (auto& vec : (*this))
					for (auto& var : vec)
						var = fun(var, std::forward<Args>(args)...);
			}
		};

		template<class type>
		inline vector<type> vector<type>::mul(size_type dim, ...)
		{
			va_list arg_ptr;
			va_start(arg_ptr, dim);
			vector<vector<type>> res(1);
			for (size_type i = 1; i < dim; i++)
				res.push_back(va_arg(arg_ptr, vector<type>));
			va_end(arg_ptr);

			initialize<type> typeinit;
			for (size_t d = 0; d < dim; d++)
			{
				xhqm::math::matrix<type> mat = xhqm::math::matrix<type>::idemat(dim - 1);
				xhqm::math::vector<type> vec(dim - 1, typeinit.value);
				for (size_type i = 1, v = 0; i < dim; i++, v++)
				{
					for (size_type j = 0, m = 1; m < dim; j++, m++)
					{
						if (j == d)
						{
							vec[v] = res[i][j];
						}
						else if (j < d)
						{
							mat[v][j] = res[i][j];
						}
						else if (j > d)
						{
							mat[v][j] = res[i][m];
						}
					}
				}

				type dete = mat.det();
				if (std::abs(dete) > xhqm::preci)
				{
					xhqm::math::matrix<type> inv = mat.adjmat() / dete;
					res[0] = inv * vec;
					res[0].std::vector<type>::insert(res[0].std::vector<type>::begin() + d, -1);
					res[0] = res[0] * -1;
					break;
				}
			}

			return res[0];
		}
	}

	template<class type> using vector = xhqm::math::vector<type>;
	template<class type> using matrix = xhqm::math::matrix<type>;
}
#endif