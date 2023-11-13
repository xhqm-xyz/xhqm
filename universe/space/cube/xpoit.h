#ifndef XHQM_SPACE_XPOINT
#define XHQM_SPACE_XPOINT
#include "../system.h"
namespace xhqm
{
	namespace space
	{
		class xhqmclass xpoit
		{
		public:
			xpot m_vertex;
			xvec m_normal;
			color m_color = xrgba(255, 255, 255, 255);
		public:
			inline xpoit() :m_vertex() {};
			inline xpoit(const xpot& pot) :m_vertex(pot), m_normal(pot.size()) {};
			inline xpoit(const xvec::size_type& dim) :m_vertex(dim), m_normal(dim) {}
			inline xpoit(const xvec::size_type& dim, measure val) : m_vertex(dim, val), m_normal(dim) {}
			inline xpoit(std::initializer_list<measure> list) : m_vertex(list), m_normal(list.size()) {};
			inline xpoit(const xpoit& poit) :m_vertex(poit.m_vertex), m_normal(poit.m_normal), m_color(poit.m_color) {}

			measure GetLenght(xpoit pot) { return (m_vertex - pot.m_vertex).modulus(); };
			inline xpoit operator = (const xhqm::math::vector<measure>& vec) {
				return m_vertex = vec;
			};
			inline xpoit operator = (const xpoit& pot) {
				m_vertex = pot.m_vertex;
				m_normal = pot.m_normal; 
				m_color = pot.m_color; 
				return *this; };
			inline xpoit operator += (const xvec& vec) { return m_vertex += vec; };
			inline xpoit operator -= (const xvec& vec) { return m_vertex -= vec; };
			inline xpoit operator *= (const xvec& vec) { return (*this) = (*this) * vec; };
			inline xpoit operator *= (const xmat& mat) { return (*this) = (*this) * mat; };
			friend xpoit operator + (const xpoit& pot, const xvec& vec);//点移动
			friend xpoit operator - (const xpoit& pot, const xvec& vec);//点移动
			friend xpoit operator * (const xpoit& pot, const xvec& vec);//点缩放

			friend xpoit operator * (const xpoit& pot, const xmat& mat);//点变换
			friend xpoit operator * (const xmat& mat, const xpoit& pot);//变换点
		};
		typedef std::vector<xpoit> xpoints;
	}
}

#endif // !UNIVERSE_SPACE_XPOINT