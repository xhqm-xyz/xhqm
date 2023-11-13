#ifndef XHQM_MATH_SHAPE
#define XHQM_MATH_SHAPE
#include "../../head.h"
//#include "../../metaclass/template.h"
#include "../math/algorithm/geometry.h"
//#include "point.h"
namespace xhqm
{
	//形状解析器基类 //将数据解析为形状
	struct parser {
		virtual bool operator ()() = 0;
	};

	//形状转化器基类 //形状互转
	struct converter {
		virtual bool operator ()() = 0;
	};

	struct xhqmclass shape_info
	{
	protected:
		xhqm::size this_id = 0;
		xhqm::string this_name = "";
		inline static xhqm::size shape_type_count = 0;
	public:
		virtual void rander() {};
		xhqm::size shape_id() const
		{
			return this_id;
		}
		xhqm::string shape_name() const
		{
			return this_name;
		}
	};

	template<typename type>
	struct shape_base : public xhqm::shape_info
	{
		shape_base(std::string _name)
		{
			this_name = _name;
			this_id = shape_id();
		}

		static xhqm::size shape_id()
		{
			static xhqm::size id = ++shape_type_count;
			return id;
		}
	};

	namespace shape
	{
		//形状点
		struct poit
			: public shape_base<xhqm::shape::poit>
		{
		protected:
			xhqm::poit<3> point;
		public:
			inline operator xhqm::poit<3>() { return point; }
			inline operator xhqm::vect<3>() { return xhqm::vect<3>(point); }

            inline xhqm::poit<3> pot() const { return point; }
            inline xhqm::vect<3> vec() const { return xhqm::vect<3>(point); }

            inline xhqm::measure modulus() const { return vec().modulus(); }
		public:
			xhqm::measure& x; xhqm::measure& y; xhqm::measure& z;
			poit(xhqm::measure _x = 0.0, xhqm::measure _y = 0.0, xhqm::measure _z = 0.0)
				: shape_base("poit"), x(point[0]), y(point[1]), z(point[2])
			{
				x = _x; y = _y; z = _z;
			}
			poit(const xhqm::poit<3>& poit)
				: shape_base("poit")
				, x(point[0]), y(point[1]), z(point[2])
			{
				x = poit[0]; y = poit[1]; z = poit[2];
			}

			//xhqm::measure& x() { return point.x(); }
			//xhqm::measure& y() { return point.y(); }
			//xhqm::measure& z() { return point.z(); }
			//const xhqm::measure& x() const { return point.x(); }
			//const xhqm::measure& y() const { return point.y(); }
			//const xhqm::measure& z() const { return point.z(); }
		};
		//形状线
		struct line
			: public shape_base<xhqm::shape::line>
		{
		public:
			xhqm::poit<3> star;
			xhqm::poit<3> stop;
		public:
			inline operator xhqm::vect<3>() { return xhqm::vect<3>(stop - star); }

            inline xhqm::vect<3> vec() const { return xhqm::vect<3>(stop - star); }

            inline xhqm::measure length() const { return vec().modulus(); }
		public:
			line(xhqm::poit<3> _star = xhqm::poit<3>(), xhqm::poit<3> _stop = xhqm::poit<3>())
				: shape_base("line")
				, star(_star), stop(_stop)
			{

			}
		};
		//形状面
		struct face
			: public shape_base<xhqm::shape::face>
		{
		public:
			xhqm::poit<3> A;
			xhqm::poit<3> B;
			xhqm::poit<3> C;
		public:
            inline xhqm::measure d() const {
				xhqm::measure D;
				xhqm::vect<3> V;
				xhqm::geometry::toFace(A, B, C, V, D);
				return D;
			}
            inline xhqm::vect<3> v() const {
				xhqm::measure D;
				xhqm::vect<3> V;
				xhqm::geometry::toFace(A, B, C, V, D);
				return V;
			}
			inline operator xhqm::vect<3>() {
				xhqm::measure D;
				xhqm::vect<3> V;
				xhqm::geometry::toFace(A, B, C, V, D);
				return V;
			}
			inline operator xhqm::vect<4>() {
				xhqm::measure D;
				xhqm::vect<3> V;
				xhqm::geometry::toFace(A, B, C, V, D);
				return { V[0], V[1], V[2], D };
			}

            inline xhqm::vect<4> length(xhqm::poit<3> p) {
				xhqm::measure d;
				xhqm::vect<3> v;
				xhqm::geometry::toFace(A, B, C, v, d);
				xhqm::pot4 L = xhqm::geometry::potLenFace(p, v, d);
				return { L[0], L[1], L[2], L[3] };
			}

            inline xhqm::measure area() const { return xhqm::geometry::TriangleArea(A, B, C); }
		public:
			face(xhqm::poit<3> _A = xhqm::poit<3>(), xhqm::poit<3> _B = xhqm::poit<3>(), xhqm::poit<3> _C = xhqm::poit<3>())
				: shape_base("face")
				, A(_A), B(_B), C(_C)
			{

			}
		};
		//形状体
		struct cube
			: public shape_base<xhqm::shape::cube>
		{
		public:
			xhqm::poit<3> A;
			xhqm::poit<3> B;
			xhqm::poit<3> C;
			xhqm::poit<3> D;
		public:
            inline xhqm::measure volume() const {
				xhqm::shape::face face(A, B, C);
				return face.area() * face.length(D)[3];
			}

		public:
			cube(xhqm::poit<3> _A = xhqm::poit<3>(), xhqm::poit<3> _B = xhqm::poit<3>(), xhqm::poit<3> _C = xhqm::poit<3>(), xhqm::poit<3> _D = xhqm::poit<3>())
				: shape_base("cube")
				, A(_A), B(_B), C(_C), D(_D)
			{

			}
		};
		//折曲线
		struct lines
			: public shape_base<xhqm::shape::lines>
		{
		protected:
			std::vector<xhqm::poit<3>> points;
		public:

			inline void sub()
			{
				points.pop_back();
			}
			inline void add(const xhqm::poit<3>& pot)
			{
				points.push_back(pot);
			}

			inline xhqm::poit<3>& pot(xhqm::size pos) { return points[pos]; }
			inline const xhqm::poit<3>& pot(xhqm::size pos) const { return points[pos]; }
		public:
			lines(xhqm::size size = 0) : shape_base("lines"), points(size)
			{
			}
		};
		//折曲面
		struct faces
			: public shape_base<xhqm::shape::faces>
		{
		protected:
			std::vector<std::array<xhqm::poit<3>, 3>> triangles;
		public:

			inline void sub()
			{
				triangles.pop_back();
			}
			inline void add(const std::array<xhqm::poit<3>, 3>& tir)
			{
				triangles.push_back(tir);
			}
			inline void add(const xhqm::poit<3>& A, const xhqm::poit<3>& B, const xhqm::poit<3>& C)
			{
				triangles.push_back({ A,B,C });
			}

			inline std::array<xhqm::poit<3>, 3>& tir(xhqm::size pos) { return triangles[pos]; }
			inline const std::array<xhqm::poit<3>, 3>& tir(xhqm::size pos) const { return triangles[pos]; }
            inline const xhqm::vect<3> vec(xhqm::size pos) const { return xhqm::shape::face(triangles[pos][0], triangles[pos][1], triangles[pos][2]); }
		public:
			faces(xhqm::size size = 0) : shape_base("faces"), triangles(size)
			{
			}
		};
	}
}
#endif
