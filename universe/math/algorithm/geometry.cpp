#include "geometry.h"
namespace xhqm
{
	namespace geometry
	{
		bool isLineseg(const xhqm::pot3& pt1, const xhqm::pot3& pt2)
		{
			xhqm::measure l0 = xhqm::vec3(pt1 - pt2).modulus();
			return (l0 > xhqm::preci);
		}
		bool isTriangle(const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3)
		{
			xhqm::measure l1 = xhqm::vec3(pt1 - pt2).modulus();
			xhqm::measure l2 = xhqm::vec3(pt2 - pt3).modulus();
			xhqm::measure l3 = xhqm::vec3(pt3 - pt1).modulus();
			return (l1 + l2 > l3 + xhqm::preci && l2 + l3 > l1 + xhqm::preci && l3 + l1 > l2 + xhqm::preci);
		}
		xhqm::measure LinesegLen(const xhqm::pot3& pt1, const xhqm::pot3& pt2)
		{
			if (isLineseg(pt1, pt2))
			{
				return xhqm::vec3(pt1 - pt2).modulus();
			}
			return 0.0;
		}
		xhqm::measure TriangleArea(const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3)
		{
			if (isTriangle(pt1, pt2, pt3))
			{
				xhqm::measure l1 = xhqm::vec3(pt1 - pt2).modulus();
				xhqm::measure l2 = xhqm::vec3(pt2 - pt3).modulus();
				xhqm::measure l3 = xhqm::vec3(pt3 - pt1).modulus();
				xhqm::measure ls = (l1 + l2 + l3) / 2.0;
				return std::sqrt(ls * (ls - l1) * (ls - l2) * (ls - l3));
			}
			return 0.0;
		}
		bool inLineseg(const xhqm::pot3& pt, const xhqm::pot3& pt1, const xhqm::pot3& pt2)
		{
			xhqm::measure l0 = LinesegLen(pt1, pt2);
			xhqm::measure l1 = LinesegLen(pt, pt2);
			xhqm::measure l2 = LinesegLen(pt1, pt);
			return (l1 + l2 <= l0 + xhqm::preci);
		}

		bool inTriangle(const xhqm::pot3& pt, const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3)
		{
			xhqm::measure a0 = TriangleArea(pt1, pt2, pt3);
			xhqm::measure a1 = TriangleArea(pt, pt2, pt3);
			xhqm::measure a2 = TriangleArea(pt1, pt, pt3);
			xhqm::measure a3 = TriangleArea(pt1, pt2, pt);
			return (a1 + a2 + a3 <= a0 + xhqm::preci);
		}

		bool inLine(const xhqm::pot3& pt, const xhqm::pot3& star, const xhqm::vec3& div)
		{
			xhqm::vec3 v1 = div.normalvec();
			xhqm::vec3 v2 = xhqm::vec3(pt - star).normalvec();
			xhqm::measure dv = v1 * v2;
			return (std::abs(std::abs(dv) - 1.0) <= xhqm::preci);
		}

		bool inFace(const xhqm::pot3& pt, const xhqm::vec3& v, const xhqm::measure& d)
		{
			xhqm::measure dp = xhqm::vec3(pt) * v;
			return (std::abs(dp - d) <= xhqm::preci);
		}

		bool toLine(const xhqm::pot3& pt1, const xhqm::pot3& pt2, xhqm::pot3& star, xhqm::vec3& div)
		{
			star = pt1;
			if (isLineseg(pt1, pt2))
			{
				div = xhqm::vec3(pt2 - pt1);
				div.normalize();
				return true;
			}
            div = xhqm::vec3();
			return false;
		}

		bool toFace(const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3, xhqm::vec3& v, xhqm::measure& d)
		{
			if (isTriangle(pt1, pt2, pt3))
			{
				xhqm::vec3 v2 = xhqm::vec3(pt2 - pt1);
				xhqm::vec3 v3 = xhqm::vec3(pt3 - pt1);
				v = v2 / v3;
				v.normalize();
				d = v * xhqm::vec3(pt1);
				return true;
			}
            v = xhqm::vec3();
            d = 0.0;
			return false;
		}

		xhqm::pot3 potProjectionLine(const xhqm::pot3& pt, const xhqm::pot3& star, const xhqm::vec3& div)
		{
			if (std::abs(div[0]) < xhqm::preci && std::abs(div[1]) < xhqm::preci && std::abs(div[2]) < xhqm::preci)
			{
				return star;
			}
			if (inLine(pt, star, div))
			{
				return pt;
			}
			xhqm::vec3 div1 = div.normalvec();
			xhqm::vec3 div2 = xhqm::vec3(pt - star);
			xhqm::vec3 div3 = div2 / div1;//叉乘"/"
			xhqm::vec3 div4 = div3 / div1;
			return  pt + div4;
		}

		xhqm::pot3 potProjectionFace(const xhqm::pot3& p, const xhqm::vec3& v, const xhqm::measure& d)
		{
			if (std::abs(v[0]) < xhqm::preci && std::abs(v[1]) < xhqm::preci && std::abs(v[2]) < xhqm::preci)
			{
				return p;
			}
			xhqm::measure dis = (v * xhqm::vec3(p) - d) / v.modulus();
			return (p - (v * dis));
		}

		xhqm::pot4 potLenLine(const xhqm::pot3& pt, const xhqm::pot3& star, const xhqm::vec3& div)
		{
			xhqm::pot4 len;
			xhqm::pot3 ptfoot = potProjectionLine(pt, star, div);
			len[0] = std::abs(len.x() - ptfoot.x());
			len[1] = std::abs(len.x() - ptfoot.x());
			len[2] = std::abs(len.x() - ptfoot.x());
			len[3] = xhqm::vec3(pt - ptfoot).modulus();
			return len;
		}

		xhqm::pot4 potLenFace(const xhqm::pot3& p, const xhqm::vec3& v, const xhqm::measure& d)
		{
			xhqm::pot4 len;
			xhqm::pot3 ptfoot = potProjectionFace(p, v, d);
			len[0] = std::abs(len.x() - ptfoot.x());
			len[1] = std::abs(len.x() - ptfoot.x());
			len[2] = std::abs(len.x() - ptfoot.x());
			len[3] = xhqm::vec3(p - ptfoot).modulus();
			return len;
		}

	}
}
