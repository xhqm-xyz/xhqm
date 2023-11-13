#ifndef XHQM_TUPLE
#define XHQM_TUPLE
#include <tuple>
#include "template.h"
namespace xhqm 
{
	inline namespace templates 
	{
		//类型数组
		template<xhqm::size size, class type_add, class ...type_arg>
		struct tuple_s { using type = typename tuple_s<size - 1, type_add, type_add, type_arg...>::type; };
		template<class type_add, class ...type_arg>
		struct tuple_s<1, type_add, type_arg...> { using type = typename std::tuple<type_add, type_arg...>; };
		template<xhqm::size size, class ...type_arg>
		using tuple = typename tuple_s<size, type_arg...>::type;
		template<xhqm::size size, class ...type_arg>
		using tuple_less = typename tuple_s<size - 1, type_arg...>::type;
		template<xhqm::size size, class ...type_arg>
		using tuple_more = typename tuple_s<size + 1, type_arg...>::type;


		//template<typename tuple_type1, typename tuple_type2>
		//struct tuple_add {

		//	template <class _Ty, class... _For_array>
		//	struct _View_as_tuple { // tuple_cat() supports only tuples, pairs, and arrays
		//		static_assert(std::_Always_false<_Ty>, "Unsupported tuple_cat arguments.");
		//	};

		//	template <class _Ty, class... _For_array>
		//	struct _View_as_tuple;

		//	template <class... _Types>
		//	struct _View_as_tuple<std::tuple<_Types...>> { // view a tuple as a tuple
		//		using type = std::tuple<_Types...>;
		//	};

		//	template <size_t _Nx, class _Ty>
		//	struct _Repeat_for : std::integral_constant<size_t, _Nx> {};

		//	template <class _Seq_type1, class _Seq_type2>
		//	struct _Cat_sequences;

		//	template <size_t... _Indexes1, size_t... _Indexes2>
		//	struct _Cat_sequences<std::index_sequence<_Indexes1...>,
		//		std::index_sequence<_Indexes2...>> { // concatenates two index_sequence types
		//		using type = std::index_sequence<_Indexes1..., _Indexes2...>;
		//	};

		//	template <class _Ret, class _Kx_arg, class _Ix_arg, size_t _Ix_next, class... _Tuples>
		//	struct _Tuple_cat2 { // determine tuple_cat's return type and _Kx/_Ix indices
		//		static_assert(sizeof...(_Tuples) == 0, "Unsupported tuple_cat arguments.");
		//		using type = _Ret;
		//		using _Kx_arg_seq = _Kx_arg;
		//		using _Ix_arg_seq = _Ix_arg;
		//	};

		//	template <class... _Types1, class _Kx_arg, size_t... _Ix, size_t _Ix_next, class... _Types2, class... _Rest>
		//	struct _Tuple_cat2<std::tuple<_Types1...>, _Kx_arg, std::index_sequence<_Ix...>, _Ix_next, std::tuple<_Types2...>, _Rest...>
		//		: _Tuple_cat2<std::tuple<_Types1..., _Types2...>, typename _Cat_sequences<_Kx_arg, std::index_sequence_for<_Types2...>>::type,
		//		std::index_sequence<_Ix..., _Repeat_for<_Ix_next, _Types2>::value...>, _Ix_next + 1,
		//		_Rest...> { // determine tuple_cat's return type and _Kx/_Ix indices
		//	};

		//	template <class... _Tuples>
		//	struct _Tuple_cat1 : _Tuple_cat2<std::tuple<>, std::index_sequence<>, std::index_sequence<>, 0,
		//		typename _View_as_tuple<std::decay_t<_Tuples>>::type...> { // prepare to determine tuple_cat's
		//		// return type and _Kx/_Ix indices
		//	};

		//	using type = typename  _Tuple_cat1<tuple_type1, tuple_type2>::type;
		//};

		//template<xhqm::size size, typename tuple_type>
		//struct tuple_sub {
		//	static_assert(size <= std::tuple_size<tuple_type>::value, "tuple size out of bounds");

		//	template<xhqm::size stop>
		//	struct in_tuple_sub_s
		//	{
		//		using this_type = std::tuple<std::tuple_element<stop, tuple_type>::type>;
		//		using type = typename tuple_add<in_tuple_sub_s<stop - 1>::type, this_type>::type; ;
		//	};

		//	template<>
		//	struct in_tuple_sub_s<0>
		//	{
		//		using type = std::tuple<std::tuple_element<0, tuple_type>::type>;
		//	};

		//	using type = typename in_tuple_sub_s<size - 1>::type;
		//};

		//template<typename tuple_type>
		//struct tuple_sub<0, tuple_type>
		//{
		//	using type = std::tuple<>;
		//};

	}
}
#endif