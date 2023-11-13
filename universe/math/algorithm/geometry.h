#ifndef XHQM_ALGOR_GEOMETOR
#define XHQM_ALGOR_GEOMETOR
#include "../../../head.h"
#include "../point.h"
namespace xhqm
{
	namespace geometry
	{
		//三维几何学

		//判断两点是否为线段
		bool xhqmclass isLineseg(const xhqm::pot3& pt1, const xhqm::pot3& pt2);
		//判断三点是否为三角形
		bool xhqmclass isTriangle(const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3);
		//计算线段长度
		xhqm::measure xhqmclass LinesegLen(const xhqm::pot3& pt1, const xhqm::pot3& pt2);
		//计算三角形面积
		xhqm::measure xhqmclass TriangleArea(const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3);
		//点pt是否在线段之间
		bool xhqmclass inLineseg(const xhqm::pot3& pt, const xhqm::pot3& pt1, const xhqm::pot3& pt2);
		//点pt是否在三角形之内
		bool xhqmclass inTriangle(const xhqm::pot3& pt, const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3);
		//点pt是否在直线上
		bool xhqmclass inLine(const xhqm::pot3& pt, const xhqm::pot3& star, const xhqm::vec3& div);
		//点pt是否在平面上
		bool xhqmclass inFace(const xhqm::pot3& pt, const xhqm::vec3& v, const xhqm::measure& d);
		//线段转为直线
		bool xhqmclass toLine(const xhqm::pot3& pt1, const xhqm::pot3& pt2, xhqm::pot3& star, xhqm::vec3& div);
		//三角形转为平面
		bool xhqmclass toFace(const xhqm::pot3& pt1, const xhqm::pot3& pt2, const xhqm::pot3& pt3, xhqm::vec3& v, xhqm::measure& d);
		//计算点pt在直线上的投影
		xhqm::pot3 xhqmclass potProjectionLine(const xhqm::pot3& pt, const xhqm::pot3& star, const xhqm::vec3& div);
		//计算点pt在平面上的投影
		xhqm::pot3 xhqmclass potProjectionFace(const xhqm::pot3& p, const xhqm::vec3& v, const xhqm::measure& d);
		//点pt到直线上的距离，三个空间分量距离，一个直线距离
		xhqm::pot4 xhqmclass potLenLine(const xhqm::pot3& pt, const xhqm::pot3& star, const xhqm::vec3& div);
		//点pt到平面上的距离，三个空间分量距离，一个直线距离
		xhqm::pot4 xhqmclass potLenFace(const xhqm::pot3& p, const xhqm::vec3& v, const xhqm::measure& d);


	}
}
#endif