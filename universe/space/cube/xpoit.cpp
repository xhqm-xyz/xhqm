#include "xpoit.h"
namespace xhqm
{
	namespace space
	{
		xpoit operator+(const xpoit& pot, const xvec& vec)
		{
			xpoit res = pot.m_vertex + vec;
			res.m_normal = pot.m_normal;
			res.m_color = pot.m_color;
			return res;
		}

		xpoit operator-(const xpoit& pot, const xvec& vec)
		{
			xpoit res = pot.m_vertex - vec;
			res.m_normal = pot.m_normal;
			res.m_color = pot.m_color;
			return res;
		}

		xpoit operator*(const xpoit& pot, const xvec& vec)
		{
			xpoit res = pot;
			xvec::size_type lenp = pot.m_vertex.dimension();
			xvec::size_type lenv = vec.dimension();
			for (xvec::size_type i = 0; i < lenp; i++)
				res.m_vertex[i] = res.m_vertex[i] * (i < lenv ? vec[i] : 0.0);
			return res;
		}

		xpoit operator*(const xpoit& pot, const xmat& mat)
		{
			xpoit res = pot.m_vertex * mat;
			res.m_normal = pot.m_normal;
			res.m_color = pot.m_color;
			return res;
		}

		xpoit operator*(const xmat& mat, const xpoit& pot)
		{
			xpoit res = mat * pot.m_vertex;
			res.m_normal = pot.m_normal;
			res.m_color = pot.m_color;
			return res;
		}

	}
}
