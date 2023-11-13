#include "ransac.h"
#ifdef _MSC_VER
#pragma warning(disable : 4267)
#endif
namespace xhqm
{
	namespace ransac
	{
		bool Pot_similarityfun(const xhqm::ransac::model<xhqm::pot3, 1>& poit, const xhqm::pot3& mespot, const xhqm::measure& maxdis)
		{
			xhqm::pot3 despot = poit.describe()[0];
			xhqm::measure dis = xhqm::vec3(mespot - despot).modulus();
			return (dis <= maxdis);
		}
		bool Wire_similarityfun(const xhqm::ransac::model<xhqm::pot3, 2>& line, const xhqm::pot3& pot, const xhqm::measure& maxdis)
		{
			std::vector<xhqm::pot3> describe = line.describe();
			xhqm::pot3 StarPot = describe[0];
			xhqm::pot3 StopPot = describe[1];
			if (geometry::isLineseg(StarPot, StopPot))
			{
				xhqm::pot3 pfoot = geometry::potProjectionLine(pot, StarPot, xhqm::vec3(StopPot - StarPot));
				xhqm::measure dis = xhqm::vec3(pot - pfoot).modulus();
				return (dis <= maxdis);
			}
			return false;
		}
		bool Patch_similarityfun(const xhqm::ransac::model<xhqm::pot3, 3>& face, const xhqm::pot3& pot, const xhqm::measure& maxdis)
		{
			std::vector<xhqm::pot3> describe = face.describe();
			xhqm::pot3 pt1 = describe[0];
			xhqm::pot3 pt2 = describe[1];
			xhqm::pot3 pt3 = describe[2];
			xhqm::vec3 v;
			xhqm::measure d;
			if (geometry::toFace(pt1, pt2, pt3, v, d))
			{
				xhqm::measure dis = geometry::potLenFace(pot, v, d)[3];
				return (std::abs(dis) <= maxdis);
			}
			return false;
		}

		bool Ball_similarityfun(const xhqm::ransac::model<xhqm::pot3, 4>& ball, const xhqm::pot3& pot, const xhqm::measure& maxdis)
		{
			std::vector<xhqm::pot3> describe = ball.describe();
			xhqm::mat<xhqm::measure> mat
			{
				{2 * (describe[0][0] - describe[1][0]), 2 * (describe[0][1] - describe[1][1]), 2 * (describe[0][2] - describe[1][2])},
				{2 * (describe[1][0] - describe[2][0]), 2 * (describe[1][1] - describe[2][1]), 2 * (describe[1][2] - describe[2][2])},
				{2 * (describe[2][0] - describe[3][0]), 2 * (describe[2][1] - describe[3][1]), 2 * (describe[2][2] - describe[3][2])}
			};
			xhqm::vec<xhqm::measure> vec
			{
			 xhqm::vec3(describe[0]).modulus() - xhqm::vec3(describe[1]).modulus(),
			 xhqm::vec3(describe[1]).modulus() - xhqm::vec3(describe[2]).modulus(),
			 xhqm::vec3(describe[2]).modulus() - xhqm::vec3(describe[3]).modulus(),
			};
			xhqm::measure dete = mat.det();
			if (std::abs(dete) > xhqm::preci)
			{
				xhqm::mat<xhqm::measure> inv = mat.adjmat() / dete;
				xhqm::pot3 ballO;
				xhqm::measure ballR;
				vec = inv * vec;
				ballO = xhqm::pot3{ vec[0], vec[1], vec[2] };
				vec = inv * vec;
				ballR = xhqm::vec3(describe[0] - ballO).modulus();
				xhqm::measure length = xhqm::vec3(pot - ballO).modulus();
				return (std::abs(ballR - length) <= maxdis);
			}
			return false;
		}
	};
}
