#include "nurbs.h"
namespace xhqm::shape
{
    xhqm::poit<3> nurbs_line::creat(xhqm::measure v) const
	{
		nurbs::value(v, m_V.front(), m_V.back());
		for (xhqm::size i = m_K, size = m_V.size() - m_K - 1; i < size; i++)
		{
			if (m_V[i] <= v && v <= m_V[i + 1])
			{
				xhqm::matr<4, 4> N = nurbs::cclt(m_V, i);
				xhqm::matr<4, 1> Z{
					{ m_W[i - 3] }, { m_W[i - 2] }, { m_W[i - 1] }, { m_W[i - 0] }
				};
				xhqm::matr<4, 3> P{
					{m_W[i - 3 + 0] * m_P[i - 3 + 0].x(), m_W[i - 3 + 0] * m_P[i - 3 + 0].y(), m_W[i - 3 + 0] * m_P[i - 3 + 0].z()},
					{ m_W[i - 3 + 1] * m_P[i - 3 + 1].x(),m_W[i - 3 + 1] * m_P[i - 3 + 1].y(),m_W[i - 3 + 1] * m_P[i - 3 + 1].z() },
					{ m_W[i - 3 + 2] * m_P[i - 3 + 2].x(),m_W[i - 3 + 2] * m_P[i - 3 + 2].y(),m_W[i - 3 + 2] * m_P[i - 3 + 2].z() },
					{ m_W[i - 3 + 3] * m_P[i - 3 + 3].x(),m_W[i - 3 + 3] * m_P[i - 3 + 3].y(),m_W[i - 3 + 3] * m_P[i - 3 + 3].z() }
				};
				double ut = m_V[i] == m_V[i + 1] ? 0.0 : (v - m_V[i]) / (m_V[i + 1] - m_V[i]);
				xhqm::matr<1, 4> mt{ { 1.0, ut, ut* ut, ut* ut* ut } };

				xhqm::matr<1, 1> W = mt * N * Z;
				xhqm::matr<1, 3> C = mt * N * P;
				xhqm::matr<1, 3> poit = C / W[0][0];
				return { poit[0][0], poit[0][1], poit[0][2] };
			}
		}
		return { 0.0,0.0,0.0 };
	}

	std::vector<xhqm::poit<3>> nurbs_line::creat(const std::vector<xhqm::measure>& v) const
	{
		xhqm::size poitSize = v.size();
		std::vector<xhqm::poit<3>> poits(poitSize);
		for (xhqm::size j = 0; j < poitSize; j++)
			poits[j] = creat(v[j]);
		return poits;
	}


    xhqm::shape::nurbs_line nurbs_face::linev(xhqm::size pos) const
    {
        xhqm::size size = 0;
        nurbs_line line(m_K[0]);
        size = m_P.size() ? m_P[0].size() : 0;
        line.P() = std::vector<xhqm::poit<3>>(size);
        for (xhqm::size i = 0; i < size; ++i)
            line.P(i) = m_P[pos][i];

        size = m_W.size() ? m_W[0].size() : 0;
        line.W() = std::vector<xhqm::measure>(size);
        for (xhqm::size i = 0; i < size; ++i)
            line.W(i) = m_W[pos][i];

        size = m_W.size() ? m_V[0].size() : 0;
        line.V() = std::vector<xhqm::measure>(size);
        for (xhqm::size i = 0; i < size; ++i)
            line.V(i) = m_V[pos][i];
        return line;
    }
    xhqm::shape::nurbs_line nurbs_face::lineh(xhqm::size pos) const
    {
        xhqm::size size = 0;
        nurbs_line line(m_K[1]);
        size = m_P.size();
        line.P() = std::vector<xhqm::poit<3>>(size);
        for (xhqm::size i = 0; i < size; ++i)
            line.P(i) = m_P[i][pos];

        size = m_W.size();
        line.W() = std::vector<xhqm::measure>(size);
        for (xhqm::size i = 0; i < size; ++i)
            line.W(i) = m_W[i][pos];

        size = m_V.size();
        line.V() = std::vector<xhqm::measure>(size);
        for (xhqm::size i = 0; i < size; ++i)
            line.V(i) = m_V[i][pos];
        return line;
    }

    xhqm::shape::nurbs_line nurbs_face::linev(xhqm::measure val) const
    {
        xhqm::size dim = static_cast<xhqm::size>(val);
        return xhqm::shape::nurbs_line(dim);
    }

    xhqm::shape::nurbs_line nurbs_face::lineh(xhqm::measure val) const
    {
        xhqm::size dim = static_cast<xhqm::size>(val);
        return xhqm::shape::nurbs_line(dim);
    }


	xhqm::poit<3> nurbs_face::creat(xhqm::measure v1, xhqm::measure v2) const
    {
        xhqm::size pos1 = 0; xhqm::size pos2 = 0;
        nurbs::value(v1, m_V[0].front(), m_V[0].back());
        nurbs::value(v2, m_V[1].front(), m_V[1].back());
        for (xhqm::size i = m_K[0], size = m_V[0].size() - m_K[0] - 1; i < size; i++)
            if (m_V[0][i] <= v1 && v1 <= m_V[0][i + 1]) pos1 = i;
        for (xhqm::size j = m_K[1], size = m_V[1].size() - m_K[1] - 1; j < size; j++)
            if (m_V[1][j] <= v2 && v2 <= m_V[1][j + 1]) pos2 = j;

        double ut = m_V[0][pos1] == m_V[0][pos1 + 1] ? 0.0 : (v1 - m_V[0][pos1]) / (m_V[0][pos1 + 1] - m_V[0][pos1]);
        double us = m_V[1][pos2] == m_V[1][pos2 + 1] ? 0.0 : (v2 - m_V[1][pos2]) / (m_V[1][pos2 + 1] - m_V[1][pos2]);
        xhqm::matr<1, 4> mt{ { 1.0, ut, ut* ut, ut* ut* ut } };
        xhqm::matr<1, 4> ms{ { 1.0, us, us* us, us* us* us } };
        xhqm::matr<4, 4> Nt = nurbs::cclt(m_V[0], pos1);
        xhqm::matr<4, 4> Ns = nurbs::cclt(m_V[1], pos2);


        xhqm::matr<4, 1> Z{
            { m_W[pos1 - 3][pos2 - 3] }, { m_W[pos1 - 2][pos2 - 2] }, { m_W[pos1 - 1][pos2 - 1] }, { m_W[pos1 - 0][pos2 - 0] }
        };
        xhqm::matr<4, 3> P{
            { m_W[pos1 - 3 + 0][pos2 - 3 + 0] * m_P[pos1 - 3 + 0][pos2 - 3 + 0].x(), m_W[pos1 - 3 + 0][pos2 - 3 + 0] * m_P[pos1 - 3 + 0][pos2 - 3 + 0].y(), m_W[pos1 - 3 + 0][pos2 - 3 + 0] * m_P[pos1 - 3 + 0][pos2 - 3 + 0].z() },
            { m_W[pos1 - 3 + 1][pos2 - 3 + 1] * m_P[pos1 - 3 + 1][pos2 - 3 + 1].x(), m_W[pos1 - 3 + 1][pos2 - 3 + 1] * m_P[pos1 - 3 + 1][pos2 - 3 + 1].y(), m_W[pos1 - 3 + 1][pos2 - 3 + 1] * m_P[pos1 - 3 + 1][pos2 - 3 + 1].z() },
            { m_W[pos1 - 3 + 2][pos2 - 3 + 2] * m_P[pos1 - 3 + 2][pos2 - 3 + 2].x(), m_W[pos1 - 3 + 2][pos2 - 3 + 2] * m_P[pos1 - 3 + 2][pos2 - 3 + 2].y(), m_W[pos1 - 3 + 2][pos2 - 3 + 2] * m_P[pos1 - 3 + 2][pos2 - 3 + 2].z() },
            { m_W[pos1 - 3 + 3][pos2 - 3 + 3] * m_P[pos1 - 3 + 3][pos2 - 3 + 3].x(), m_W[pos1 - 3 + 3][pos2 - 3 + 3] * m_P[pos1 - 3 + 3][pos2 - 3 + 3].y(), m_W[pos1 - 3 + 3][pos2 - 3 + 3] * m_P[pos1 - 3 + 3][pos2 - 3 + 3].z() }
        };

        xhqm::matr<1, 1> Wt = mt * Nt * Z;
        xhqm::matr<1, 1> Ws = ms * Ns * Z;
        xhqm::matr<1, 3> Ct = mt * Nt * P;
        xhqm::matr<1, 3> Cs = mt * Ns * P;
        xhqm::matr<1, 3> poit1 = Ct / Wt[0][0];
        xhqm::matr<1, 3> poit2 = Cs / Ws[0][0];
        xhqm::poit<3> point1{ poit1[0][0], poit1[0][1], poit1[0][2] };
        xhqm::poit<3> point2{ poit2[0][0], poit2[0][1], poit2[0][2] };
        return (point1 + point2) / 2.0;
    }

    xtd::matrix<xhqm::poit<3>> nurbs_face::creat(const std::vector<xhqm::measure>& v1, const std::vector<xhqm::measure>& v2) const
	{
		xhqm::size poitSize1 = v1.size();
		xhqm::size poitSize2 = v2.size();
        xtd::matrix<xhqm::poit<3>> poits(poitSize1, std::vector<xhqm::poit<3>>(poitSize2));
		for (xhqm::size i = 0; i < poitSize1; i++)
			for (xhqm::size j = 0; j < poitSize2; j++)
				poits[i][j] = creat(v1[i], v2[j]);
		return poits;
	}


}
