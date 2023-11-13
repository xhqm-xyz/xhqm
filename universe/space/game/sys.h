#ifndef XHQM_GAME_SYSTEM
#define XHQM_GAME_SYSTEM
#include "../head.h"
#include "../math/dimension.h"
namespace xhqm
{
	namespace game
	{
		template<class type>
		class vec : public xhqm::math::dimension<type, 3>
		{
		public:
			vec() : xhqm::math::dimension<type, 3>() {}
			vec(const vec& v) : xhqm::math::dimension<type, 3>() {
				this->value[0] = v.value[0];
				this->value[1] = v.value[1];
				this->value[2] = v.value[2];
			}
			vec(std::initializer_list<type> list) : xhqm::math::dimension<type, 3>(list) {}
			vec(const type& x, const type& y, const type& z) : xhqm::math::dimension<type, 3>() {
				this->value[0] = x;
				this->value[1] = y;
				this->value[2] = z;
			}

			inline type modulus() const {
				initialize<type> inittype;
				type sum = inittype.value;
				sum += (this->value[0] * this->value[0]);
				sum += (this->value[1] * this->value[1]);
				sum += (this->value[2] * this->value[2]);
				return std::sqrt(sum);
			}
			inline vec normalvec() const { return (*this) / modulus(); }
			inline void normalize() { (*this) = (*this) / modulus(); }

			inline friend vec<type> operator + (const vec<type>& a, const type& b)
			{
				vec<type> c;
				c.value[0] = a.value[0] + b;
				c.value[1] = a.value[1] + b;
				c.value[2] = a.value[2] + b;
				return c;
			}
			inline friend vec<type> operator - (const vec<type>& a, const type& b)
			{
				vec<type> c;
				c.value[0] = a.value[0] - b;
				c.value[1] = a.value[1] - b;
				c.value[2] = a.value[2] - b;
				return c;
			}
			inline friend vec<type> operator * (const vec<type>& a, const type& b)
			{
				vec<type> c;
				c.value[0] = a.value[0] * b;
				c.value[1] = a.value[1] * b;
				c.value[2] = a.value[2] * b;
				return c;
			}
			inline friend vec<type> operator / (const vec<type>& a, const type& b)
			{
				vec<type> c;
				c.value[0] = a.value[0] / b;
				c.value[1] = a.value[1] / b;
				c.value[2] = a.value[2] / b;
				return c;
			}

			inline friend vec<type> operator + (const vec<type>& a, const vec<type>& b)
			{
				vec<type> c;
				c.value[0] = a.value[0] + b.value[0];
				c.value[1] = a.value[1] + b.value[1];
				c.value[2] = a.value[2] + b.value[2];
				return c;
			}
			inline friend vec<type> operator - (const vec<type>& a, const vec<type>& b)
			{
				vec c;
				c.value[0] = a.value[0] - b.value[0];
				c.value[1] = a.value[1] - b.value[1];
				c.value[2] = a.value[2] - b.value[2];
				return c;
			}
			inline friend vec<type> operator ^ (const vec<type>& a, const vec<type>& b)
			{
				vec c;
				c[0] = a.y() * b.z() - a.z() * b.y();
				c[1] = a.z() * b.x() - a.x() * b.z();
				c[2] = a.x() * b.y() - a.y() * b.x();
				return c;
			}
			inline friend type operator * (const vec<type>& a, const vec<type>& b)
			{
				initialize<type> inittype;
				type sum = inittype.value;
				sum += (a.value[0] * b.value[0]);
				sum += (a.value[1] * b.value[1]);
				sum += (a.value[2] * b.value[2]);
				return sum;
			}
			inline vec<type>& operator= (const vec<type>& a)
			{
				this->value[0] = a.value[0];
				this->value[1] = a.value[1];
				this->value[2] = a.value[2];
				return (*this);
			}
		};


		template<class type>
		class mat : public xhqm::math::dimension<xhqm::math::dimension<type, 3>, 3>
		{
		public:
			mat() : xhqm::math::dimension<xhqm::math::dimension<type, 3>, 3>() {}
			mat(std::initializer_list<xhqm::math::dimension<type, 3>> list) : xhqm::math::dimension<xhqm::math::dimension<type, 3>, 3>(list) {}
			mat(const mat& m) : xhqm::math::dimension<xhqm::math::dimension<type, 3>, 3>()
			{
				this->value[0][0] = m.val(0, 0); this->value[0][1] = m.val(0, 1); this->value[0][2] = m.val(0, 2);
				this->value[1][0] = m.val(1, 0); this->value[1][1] = m.val(1, 1); this->value[1][2] = m.val(1, 2);
				this->value[2][0] = m.val(2, 0); this->value[2][1] = m.val(2, 1); this->value[2][2] = m.val(2, 2);
			}
			virtual ~mat() {};

			inline friend mat<type> operator + (const mat<type>& a, const type& b)
			{
				mat<type> c(a);
				c[0][0] += b; c[0][1] += b; c[0][2] += b;
				c[1][0] += b; c[1][1] += b; c[1][2] += b;
				c[2][0] += b; c[2][1] += b; c[2][2] += b;
				return c;
			}
			inline friend mat<type> operator - (const mat<type>& a, const type& b)
			{
				mat<type> c(a);
				c[0][0] -= b; c[0][1] -= b; c[0][2] -= b;
				c[1][0] -= b; c[1][1] -= b; c[1][2] -= b;
				c[2][0] -= b; c[2][1] -= b; c[2][2] -= b;
				return c;
			}
			inline friend mat<type> operator * (const mat<type>& a, const type& b)
			{
				mat<type> c(a);
				c[0][0] *= b; c[0][1] *= b; c[0][2] *= b;
				c[1][0] *= b; c[1][1] *= b; c[1][2] *= b;
				c[2][0] *= b; c[2][1] *= b; c[2][2] *= b;
				return c;
			}
			inline friend mat<type> operator / (const mat<type>& a, const type& b)
			{
				mat<type> c(a);
				c[0][0] /= b; c[0][1] /= b; c[0][2] /= b;
				c[1][0] /= b; c[1][1] /= b; c[1][2] /= b;
				c[2][0] /= b; c[2][1] /= b; c[2][2] /= b;
				return c;
			}

			inline friend mat<type> operator + (const mat<type>& a, const mat<type>& b)
			{
				mat<type> c;
				c[0][0] = a.val(0, 0) + b.val(0, 0);
				c[0][1] = a.val(0, 1) + b.val(0, 1);
				c[0][2] = a.val(0, 2) + b.val(0, 2);
				c[1][0] = a.val(1, 0) + b.val(1, 0);
				c[1][1] = a.val(1, 1) + b.val(1, 1);
				c[1][2] = a.val(1, 2) + b.val(1, 2);
				c[2][0] = a.val(2, 0) + b.val(2, 0);
				c[2][1] = a.val(2, 1) + b.val(2, 1);
				c[2][2] = a.val(2, 2) + b.val(2, 2);
				return c;
			}
			inline friend mat<type> operator * (const mat<type>& a, const mat<type>& b)
			{
				mat<type> c;
				c[0][0] = a.val(0, 0) * b.val(0, 0) + a.val(0, 1) * b.val(1, 0) + a.val(0, 2) * b.val(2, 0);
				c[0][1] = a.val(0, 0) * b.val(0, 1) + a.val(0, 1) * b.val(1, 1) + a.val(0, 2) * b.val(2, 1);
				c[0][2] = a.val(0, 0) * b.val(0, 2) + a.val(0, 1) * b.val(1, 2) + a.val(0, 2) * b.val(2, 2);
				c[1][0] = a.val(1, 0) * b.val(0, 0) + a.val(1, 1) * b.val(1, 0) + a.val(1, 2) * b.val(2, 0);
				c[1][1] = a.val(1, 0) * b.val(0, 1) + a.val(1, 1) * b.val(1, 1) + a.val(1, 2) * b.val(2, 1);
				c[1][2] = a.val(1, 0) * b.val(0, 2) + a.val(1, 1) * b.val(1, 2) + a.val(1, 2) * b.val(2, 2);
				c[2][0] = a.val(2, 0) * b.val(0, 0) + a.val(2, 1) * b.val(1, 0) + a.val(2, 2) * b.val(2, 0);
				c[2][1] = a.val(2, 0) * b.val(0, 1) + a.val(2, 1) * b.val(1, 1) + a.val(2, 2) * b.val(2, 1);
				c[2][2] = a.val(2, 0) * b.val(0, 2) + a.val(2, 1) * b.val(1, 2) + a.val(2, 2) * b.val(2, 2);
				return c;
			}
			inline friend vec<type> operator * (const vec<type>& va, const mat<type>& mb)
			{
				vec<type> c;
				c[0] = va.val(0) * mb.val(0, 0) + va.val(1) * mb.val(1, 0) + va.val(2) * mb.val(2, 0);
				c[1] = va.val(0) * mb.val(0, 1) + va.val(1) * mb.val(1, 1) + va.val(2) * mb.val(2, 1);
				c[2] = va.val(0) * mb.val(0, 2) + va.val(1) * mb.val(1, 2) + va.val(2) * mb.val(2, 2);
				return c;
			}
			inline friend vec<type> operator * (const mat<type>& ma, const vec<type>& vb)
			{
				vec<type> c;
				c[0] = ma.val(0, 0) * vb.val(0) + ma.val(0, 1) * vb.val(1) + ma.val(0, 2) * vb.val(2);
				c[1] = ma.val(1, 0) * vb.val(0) + ma.val(1, 1) * vb.val(1) + ma.val(1, 2) * vb.val(2);
				c[2] = ma.val(2, 0) * vb.val(0) + ma.val(2, 1) * vb.val(1) + ma.val(2, 2) * vb.val(2);
				return c;
			}
			inline mat<type>& operator= (const mat<type>& a)
			{
				this->value[0][0] = a.val(0, 0);
				this->value[0][1] = a.val(0, 1);
				this->value[0][2] = a.val(0, 2);

				this->value[1][0] = a.val(1, 0);
				this->value[1][1] = a.val(1, 1);
				this->value[1][2] = a.val(1, 2);

				this->value[2][0] = a.val(2, 0);
				this->value[2][1] = a.val(2, 1);
				this->value[2][2] = a.val(2, 2);
				return (*this);
			}

			inline vec<type> row(const std::size_t& n) const { return vec<type>(val(n, 0), val(n, 1), val(n, 2), val(n, 3)); };
			inline vec<type> col(const std::size_t& m) const { return vec<type>(val(0, m), val(1, m), val(2, m), val(3, m)); };
			inline type val(const std::size_t& n, const std::size_t& m) const { return this->value[n].val(m); }
			inline type det() const
			{
				initialize<type> typeinit;
				type sum = typeinit.value;
				sum += this->val(0, 0) * this->val(1, 1) * this->val(2, 2);
				sum += this->val(0, 1) * this->val(1, 2) * this->val(2, 0);
				sum += this->val(0, 2) * this->val(1, 0) * this->val(2, 1);
				sum -= this->val(0, 0) * this->val(1, 2) * this->val(2, 1);
				sum -= this->val(0, 1) * this->val(1, 0) * this->val(2, 2);
				sum -= this->val(0, 2) * this->val(1, 1) * this->val(2, 0);
				return sum;
			};								//得到行列式的值
			inline mat<type> adjmat() const
			{
				mat<type> adj;
				adj.value[0][0] = this->val(1, 1) * this->val(2, 2) - this->val(1, 2) * this->val(2, 1);
				adj.value[1][0] = this->val(1, 2) * this->val(2, 0) - this->val(1, 0) * this->val(2, 2);
				adj.value[2][0] = this->val(1, 0) * this->val(2, 1) - this->val(1, 1) * this->val(2, 0);
				adj.value[0][1] = this->val(0, 2) * this->val(2, 1) - this->val(0, 1) * this->val(2, 2);
				adj.value[1][1] = this->val(0, 0) * this->val(2, 2) - this->val(0, 2) * this->val(2, 0);
				adj.value[2][1] = this->val(0, 1) * this->val(2, 0) - this->val(0, 0) * this->val(2, 1);
				adj.value[0][2] = this->val(0, 1) * this->val(1, 2) - this->val(0, 2) * this->val(1, 1);
				adj.value[1][2] = this->val(0, 2) * this->val(1, 0) - this->val(0, 0) * this->val(1, 2);
				adj.value[2][2] = this->val(0, 0) * this->val(1, 1) - this->val(0, 1) * this->val(1, 0);
				return adj;
			};							//伴随矩阵
			inline mat<type> tramat() const
			{
				return {
					{this->value[0][0],this->value[1][0],this->value[2][0]},
					{this->value[0][1],this->value[1][1],this->value[2][1]},
					{this->value[0][2],this->value[1][2],this->value[2][2]},
				};
			};							//转置矩阵	
			inline mat<type> invmat() const
			{
				return (adjmat() / det());
			};							//逆矩阵	

			static mat<type> rotate(type agex, type agey, type agez)
			{
				mat<type> rotex{ {1, 0, 0}, {0, std::cos(agex), -std::sin(agex)}, {0, std::sin(agex), std::cos(agex) } };
				mat<type> rotey{ {std::cos(agey), 0, -std::sin(agey)}, {0, 1, 0}, {std::sin(agey), 0, std::cos(agey) } };
				mat<type> rotez{ {std::cos(agez), -std::sin(agez), 0}, {std::sin(agez), std::cos(agez), 0}, {0, 0, 1 } };
				return rotex * rotey * rotez;
			}
			static mat<type> flexible(type varx, type vary, type varz)
			{
				mat<type> flex;
				flex[0][0] = varx;
				flex[1][1] = vary;
				flex[2][2] = varz;
				return flex;
			}
			static mat<type> rotate(vec<type> axis, type age)
			{
				type cos = std::cos(age);
				type sin = std::sin(age);
				mat<type> add1{
					{cos,0,0},
					{0,cos,0},
					{0,0,cos},
				};
				mat<type> add2{
					{axis[0] * axis[0],axis[0] * axis[1],axis[0] * axis[2] },
					{axis[1] * axis[0],axis[1] * axis[1],axis[1] * axis[2] },
					{axis[2] * axis[0],axis[2] * axis[1],axis[2] * axis[2] },
				};
				mat<type> add3{
					{0,-axis[2],axis[1]},
					{axis[2],0,-axis[0]},
					{-axis[1],axis[0],0},
				};
				mat<type> rote = add1 + (add2 * (1 - cos)) + (add3 * sin);
				return rote;
			}
			static mat<type> perspective(type n, type f)
			{
				mat<type> perspec;
				type len = n / (n + f);
				perspec[0][0] = len;
				perspec[1][1] = len;
				perspec[2][2] = 1;
				return perspec;
			}
		};


		template<class type>
		class sys :public mat<type>, public vec<type>
		{
		public:
			mat<type>& m_mat;
			vec<type>& m_vec;
			sys() : m_mat(*this), m_vec(*this) {
				m_mat = { {1,0,0},{0,1,0},{0,0,1} };
			}
			sys(const sys& s) : mat<type>(s), vec<type>(s), m_mat(*this), m_vec(*this) { }
			void setmic(mat<type> from, vec<type> move) { m_mat = from; m_vec = move; }
			void getmic(mat<type>& from, vec<type>& move) { from = m_mat; move = m_vec; }
			sys& operator = (const sys& s) { m_mat = s; m_vec = s; return (*this); };
			virtual ~sys() {};
			//先姿态，后位置
			//先矩阵，后向量
			static void mac2mic(mat<type> macfrom, vec<type> macmove, mat<type> parfrom, vec<type> parmove, mat<type>& micfrom, vec<type>& micmove)
			{
				mat<type> parinv = parfrom.invmat();
				micfrom = macfrom * parinv;
				micmove = (macmove - parmove) * parinv;
			}
			static void mic2mac(mat<type> micfrom, vec<type> micmove, mat<type> parfrom, vec<type> parmove, mat<type>& macfrom, vec<type>& macmove)
			{
				macfrom = micfrom * parfrom;
				macmove = micmove * parfrom + parmove;
			}
			static mat<type> mati() { return { {1,0,0},{0,1,0},{0,0,1} }; }
			static vec<type> veco() { return { 0,0,0 }; }
		};

		template<class type>
		using pot = xhqm::game::vec<type>;
		template<class type>
		using vertex = xhqm::game::vec<type>;
		template<class type>
		using normal = xhqm::game::vec<type>;
		template<class type = xhqm::byte>
		using colour = xhqm::math::dimension<type, 4>;
	}
}
#endif
