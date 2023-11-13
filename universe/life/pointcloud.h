#ifndef XHQM_SHAPE_POINTCLOUD
#define XHQM_SHAPE_POINTCLOUD
#include "shape.h"
#include "../../metaclass/template.h"
namespace xhqm::shape
{
	//点类判断
	template <xhqm::size dim, typename poitType> struct pointcloud_s
	{
		using point_type0 = poitType;
		using point_type1 = xhqm::select_if_type<std::is_same_v<point_type0, xhqm::size>, xhqm::poit<dim, xhqm::size>, point_type0>;
		using point_type2 = xhqm::select_if_type<std::is_same_v<point_type1, xhqm::inte>, xhqm::poit<dim, xhqm::inte>, point_type1>;
		using point_type3 = xhqm::select_if_type<std::is_same_v<point_type2, xhqm::color>, xhqm::poit<dim, xhqm::color>, point_type2>;
		using point_type4 = xhqm::select_if_type<std::is_same_v<point_type3, float>, xhqm::poit<dim, float>, point_type3>;
		using point_type5 = xhqm::select_if_type<std::is_same_v<point_type4, double>, xhqm::poit<dim, double>, point_type4>;
		using point_type6 = xhqm::select_if_type<std::is_same_v<point_type5, long double>, xhqm::poit<dim, long double>, point_type5>;
		using value_type = typename point_type6::value_type;
		using point_type = point_type6;
	};
	//点云基类
	template <xhqm::size dim, typename poitType, typename cloudType>
	struct _cloud_base : public shape_base<cloudType>, std::vector<typename pointcloud_s<dim, poitType>::point_type>
	{
		using value_type = typename pointcloud_s<dim, poitType>::value_type;
		using point_type = typename pointcloud_s<dim, poitType>::point_type;

        _cloud_base(const std::vector<point_type>& points, xhqm::string name = "pointcloud<type>")
			: shape_base<cloudType>(name), std::vector<point_type>(points) { }

        _cloud_base(const xhqm::size& size, xhqm::string name = "pointcloud<type>")
			: shape_base<cloudType>(name), std::vector<point_type>(size) { }

		constexpr xhqm::size dimension() const { return dim; }
	};

	//点云泛型 poitType::value_type poitType::dimension
	template <typename poitType = xhqm::poit<3, xhqm::measure>>
	struct pointcloud : public _cloud_base<poitType::dimension, poitType, pointcloud<poitType>> {

        using cloud_base = _cloud_base<poitType::dimension, poitType, pointcloud<poitType>>;
		using point_type = typename cloud_base::point_type;
		using value_type = typename cloud_base::value_type;

		constexpr pointcloud(const std::vector<point_type>& points)
			: cloud_base(points) { }

		constexpr pointcloud(const xhqm::size& size = 0)
			: cloud_base(size) { }
	};

	template <typename type = xhqm::measure, xhqm::size dim = 3>
	using pointType = typename pointcloud_s<dim, type>::point_type;

	template <typename type = xhqm::poit<3, xhqm::measure>, xhqm::size dim = 3>
	using cloudType = pointcloud<typename pointcloud_s<dim, type>::point_type>;
}

#endif
