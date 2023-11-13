#ifndef XHQM_COMPUTE
#define XHQM_COMPUTE
#include "../head.h"
#include "template.h"

namespace xhqm {

	inline namespace templates {

		//����
		template<class type>
		struct compute {
			//����
			template<type ...vals> static constexpr xhqm::size size_count = sizeof...(vals);

			//bool ֵѡ��
			template<bool select, type val_1, type val_2> struct select_if { static constexpr type value = val_1; };
			template<type val_1, type val_2> struct select_if<false, val_1, val_2> { static constexpr type value = val_2; };

			//�±� ֵѡ��
			template<xhqm::size select, type val, type ...vals>
			struct select_index { static constexpr type value = select_index<select - 1, vals...>::value; };
			template<type val, type ...vals>
			struct select_index<0, val, vals...> { static constexpr type value = val; };

			//���
			template<type val, type ...vals>
			struct sum { static constexpr type value = val + sum<vals...>::value; };
			template<type val>
			struct sum<val> { static constexpr type value = val; };
			template<type ...vals>
			static constexpr type sum_value = sum<vals...>::value;
			//���
			template<bool select, type val, type ...vals>
			struct sub { static constexpr type value = val - compute::select_if<select, sum<vals...>::value, sub<select, vals...>::value>::value; };
			template<bool select, type val>
			struct sub<select, val> { static constexpr type value = val; };
			template<bool select, type ...vals>
			static constexpr type sub_value = sub<select, vals...>::value;
			//���
			template<type val, type ...vals>
			struct dot { static constexpr type value = val * dot<vals...>::value; };
			template<type val>
			struct dot<val> { static constexpr type value = val; };
			template<type ...vals>
			static constexpr type dot_value = dot<vals...>::value;
			//����
			template<bool select, type val, type ...vals>
			struct div { static constexpr type value = val / compute::select_if<select, dot<vals...>::value, div<select, vals...>::value>::value; };
			template<bool select, type val>
			struct div<select, val> { static constexpr type value = val; };
			template<bool select, type ...vals>
			static constexpr type div_value = div<select, vals...>::value;
		};

		//template <class type>
		//void fill_memset(void* dest, const type& value, const xhqm::size& size) {
		//	std::memset(dest, static_cast<unsigned char>(value), size * sizeof(type));
		//};

		//template <class type>
		//void fill_zero_memset(xhqm::class_ptr<xhqm::remove_type<type>> dest, const xhqm::size& size) {
		//	xhqm::fill_memset<type>(dest, 0, size);
		//};

	}
}
#endif