#ifndef XHQM_SHAPE_NURBS
#define XHQM_SHAPE_NURBS
#include "shape.h"

namespace xhqm::shape
{
	//nurbs类型
	struct xhqmclass nurbs
	{
		inline static void value(xhqm::measure& val,
			const xhqm::measure& star, const xhqm::measure& stop)
		{
			val = val < 0.0 ? 0.0 : val;
			val = val > 1.0 ? 1.0 : val;
			val = (stop - star) * val + star;
		}

		inline static std::vector<xhqm::measure> linspace(const xhqm::size& size,
			const xhqm::measure& star, const xhqm::measure& stop) 
		{
			xhqm::measure step = (stop - star) / (size - 1);
			std::vector<xhqm::measure> values(size);
			for (xhqm::size i = 0; i != size; ++i)
				values[i] = star + step * i;
			values.back() = stop;
			return values;
		}

		inline static xhqm::matr<4, 4> cclt(const std::vector<double>& T, const xhqm::size& pos) {
			xhqm::matr<4, 4> N;

			N[0][0] = ((T[pos + 1] - T[pos]) * (T[pos + 1] - T[pos])) / ((T[pos + 1] - T[pos - 1]) * (T[pos + 1] - T[pos - 2]));
			N[0][2] = ((T[pos] - T[pos - 1]) * (T[pos] - T[pos - 1])) / ((T[pos + 2] - T[pos - 1]) * (T[pos + 1] - T[pos - 1]));
			N[0][1] = 1 - N[0][0] - N[0][2];
			N[0][3] = 0.0;

			N[1][0] = -3 * N[0][0];
			N[1][2] = 3 * (T[pos + 1] - T[pos]) * (T[pos] - T[pos - 1]) / ((T[pos + 2] - T[pos - 1]) * (T[pos + 1] - T[pos - 1]));
			N[1][1] = 3 * N[0][0] - N[1][2];
			N[1][3] = 0.0;

			N[2][0] = 3 * N[0][0];
			N[2][2] = 3 * ((T[pos + 1] - T[pos]) * (T[pos + 1] - T[pos])) / ((T[pos + 2] - T[pos - 1]) * (T[pos + 1] - T[pos - 1]));
			N[2][1] = -3 * N[0][0] - N[2][2];
			N[2][3] = 0.0;

			N[3][0] = -1 * N[0][0];
			N[3][3] = ((T[pos + 1] - T[pos]) * (T[pos + 1] - T[pos])) / ((T[pos + 3] - T[pos]) * (T[pos + 2] - T[pos]));
			N[3][2] = -1 * (N[2][2] / 3 + N[3][3] + ((T[pos + 1] - T[pos]) * (T[pos + 1] - T[pos])) / ((T[pos + 2] - T[pos]) * (T[pos + 2] - T[pos - 1])));
			N[3][1] = N[0][0] - N[3][2] - N[3][3];

			return N;
		}
	};
	//nurbs曲线类型
	struct xhqmclass nurbs_line
		: public shape_base<xhqm::shape::nurbs_line>
		, xhqm::shape::nurbs
	{
	protected:
		xhqm::size m_K = 0;
		std::vector<xhqm::poit<3>> m_P;
		std::vector<xhqm::measure> m_W;
		std::vector<xhqm::measure> m_V;
	public:
		xhqm::size& K() { return m_K; };
		const xhqm::size& K() const { return m_K; };

		std::vector<xhqm::measure>& V() { return m_V; };
		const std::vector<xhqm::measure>& V() const { return m_V; };
		std::vector<xhqm::measure>& W() { return m_W; };
		const std::vector<xhqm::measure>& W() const { return m_W; };
		std::vector<xhqm::poit<3>>& P() { return m_P; };
		const std::vector<xhqm::poit<3>>& P() const { return m_P; };

		xhqm::measure& V(xhqm::size m) { return m_V[m]; };
		const xhqm::measure& V(xhqm::size m) const { return m_V[m]; };
		xhqm::measure& W(xhqm::size m) { return m_W[m]; };
		const xhqm::measure& W(xhqm::size m) const { return m_W[m]; };
		xhqm::poit<3>& P(xhqm::size m) { return m_P[m]; };
		const xhqm::poit<3>& P(xhqm::size m) const { return m_P[m]; };


		nurbs_line(xhqm::size K = 0)
			: shape_base("nurbs_line")
			, m_K(K)
		{

		}

		//阶  数，K
		//关  系  M = N + K + 1
		//节向量，V 共 M + 1 个
		//控制点，P 共 N + 1 个
		//权重值，W 共 N + 1 个
		bool isgood() const {
			if (m_V.size() && m_W.size() && m_P.size())
				if (m_W.size() == m_P.size())
					if (m_V.size() == m_P.size() + m_K + 1)
						return true;
			return false;
		}

		//v: 0-1
		xhqm::poit<3> creat(xhqm::measure v) const;
		std::vector<xhqm::poit<3>> creat(const std::vector<xhqm::measure>& v) const;
		std::vector<xhqm::poit<3>> creat(const xhqm::size& size) const
		{
			return creat(nurbs::linspace(size, 0.0, 1.0));
		}
	};
	//nurbs曲面类型
	struct xhqmclass nurbs_face
		: public shape_base<xhqm::shape::nurbs_face>
		, xhqm::shape::nurbs
	{
	protected:
        xtd::array<xhqm::size, 2> m_K;
        xtd::matrix<xhqm::poit<3>> m_P;
        xtd::matrix<xhqm::measure> m_W;
        xtd::matrix<xhqm::measure> m_V;
	public:
        xtd::array<xhqm::size, 2>& K() { return m_K; };
        const xtd::array<xhqm::size, 2>& K() const { return m_K; };

        xtd::matrix<xhqm::measure>& V() { return m_V; };
        const xtd::matrix<xhqm::measure>& V() const { return m_V; };
        xtd::matrix<xhqm::measure>& W() { return m_W; };
        const xtd::matrix<xhqm::measure>& W() const { return m_W; };
        xtd::matrix<xhqm::poit<3>>& P() { return m_P; };
        const xtd::matrix<xhqm::poit<3>>& P() const { return m_P; };

		xhqm::measure& V(xhqm::size m, xhqm::size n) { return m_V[m][n]; };
		const xhqm::measure& V(xhqm::size m, xhqm::size n) const { return m_V[m][n]; };
		xhqm::measure& W(xhqm::size m, xhqm::size n) { return m_W[m][n]; };
		const xhqm::measure& W(xhqm::size m, xhqm::size n) const { return m_W[m][n]; };
		xhqm::poit<3>& P(xhqm::size m, xhqm::size n) { return m_P[m][n]; };
		const xhqm::poit<3>& P(xhqm::size m, xhqm::size n) const { return m_P[m][n]; };

		nurbs_face(xhqm::size K1 = 0, xhqm::size K2 = 0)
			: shape_base("nurbs_face")
			, m_K{ K1, K2 }
		{

		}

		//阶  数，K
		//关  系  M = N + K + 1
		//节向量，V 共 M + 1 个
		//控制点，P 共 N + 1 个
		//权重值，W 共 N + 1 个
		bool isgood() const {
			if (m_V.size() && m_W.size() && m_P.size())
				if (m_V[0].size() && m_W[0].size() && m_P[0].size())
					if (m_V.size() == m_P.size() + m_K[0] + 1 && m_V[0].size() == m_P[0].size() + m_K[1] + 1)
						return true;
			return false;
		}

		xhqm::shape::nurbs_line linev(xhqm::size pos) const;
		xhqm::shape::nurbs_line lineh(xhqm::size pos) const;
		xhqm::shape::nurbs_line linev(xhqm::measure val) const;
		xhqm::shape::nurbs_line lineh(xhqm::measure val) const;
		//true横切 false纵切
		xhqm::shape::nurbs_line line(xhqm::size pos, bool vorh = true) const
		{
			return vorh ? linev(pos) : lineh(pos);
		}
		//true横切 false纵切
		xhqm::shape::nurbs_line line(xhqm::measure val, bool vorh = true) const
		{
			return vorh ? linev(val) : lineh(val);
		}

		xhqm::poit<3> creat(xhqm::measure v1, xhqm::measure v2) const;
        xtd::matrix<xhqm::poit<3>> creat(const std::vector<xhqm::measure>& v1, const std::vector<xhqm::measure>& v2) const;
        xtd::matrix<xhqm::poit<3>> creat(const xhqm::size& size1, const xhqm::size& size2) const
		{
			return creat(nurbs::linspace(size1, 0.0, 1.0), nurbs::linspace(size2, 0.0, 1.0));
		}


	};
}

#endif
