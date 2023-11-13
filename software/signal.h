#ifndef XHQM_SIGNAL
#define XHQM_SIGNAL

//#undef emit
//#undef signals
#include "signalslot_events.h"

namespace xhqm
{
	namespace signals
	{
		using event = xhqm::software::signal_event;

		class xhqmclass events
			: public xhqm::exist
			, public xhqm::software::except_signalslot_events
		{
			friend xhqm::instance<xhqm::signals::events>;
		protected:
			events() = default;
			~events() = default;
			events(events&&) = delete;
			events(const events&) = delete;
		protected:
			virtual void doexcept();//辅线程首次执行一次
			virtual void runexcept();//辅线程循环执行多次
			virtual void undoexcept();//辅线程末尾执行一次

			static void sand_signal(const xhqm::signals::event& event);
		};

		inline xhqm::signals::events& pool()
		{
			return xhqm::instance<xhqm::signals::events>::get();
		};

		inline void enter()
		{
			xhqm::instance<xhqm::signals::events>::get().enter();
		};

		inline void leave()
		{
			xhqm::instance<xhqm::signals::events>::get().leave();
		};

		template <typename... more_values_type> struct overload
		{
			xhqm::software::_adress adress;
			std::function<void(more_values_type...)> overfunc = nullptr;

			template<typename... less_values_type, xhqm::size... index>
			static void copy_value(
				std::tuple<less_values_type...>& to, const std::tuple<more_values_type...>& form,
				std::index_sequence<index...>)
			{
				((std::get<index>(to) = std::get<index>(form)), ...);
			}

			template<typename... less_values_type>
			static std::tuple<less_values_type...> copy(more_values_type&&... more_values)
			{
				std::tuple<less_values_type...> to;
				std::tuple<more_values_type...> form{ std::forward<more_values_type>(more_values)... };
				copy_value(to, form, std::make_index_sequence<sizeof...(less_values_type)>());
				return to;
			}

			template <typename object_type, typename return_type, typename... less_values_type>
			overload(object_type* object, return_type(object_type::* function)(less_values_type...) const, bool isconst)
				: adress(object, function)
			{
				overfunc = [=](more_values_type&&... more_values) {
					std::tuple<less_values_type...> less_tuple = copy<less_values_type...>(std::forward<more_values_type>(more_values)...);
					std::function<void(less_values_type...)> lessfun = [=](less_values_type&&... less_values)
					{
						(object->*function)(std::forward<less_values_type>(less_values)...);
					};
					std::apply(lessfun, less_tuple);
				};
			}

			template <typename object_type, typename return_type, typename... less_values_type>
			overload(object_type* object, return_type(object_type::* function)(less_values_type...))
				: adress(object, function)
			{
				overfunc = [=](more_values_type&&... more_values) {
					std::tuple<less_values_type...> less_tuple = copy<less_values_type...>(std::forward<more_values_type>(more_values)...);
					std::function<void(less_values_type...)> lessfun = [=](less_values_type&&... less_values)
					{
						(object->*function)(std::forward<less_values_type>(less_values)...);
					};
					std::apply(lessfun, less_tuple);
				};
			}

			template <typename return_type, typename... less_values_type>
			overload(return_type(*function)(less_values_type...))
				: adress(function)
			{
				overfunc = [=](more_values_type&&... more_values) {
					std::tuple<less_values_type...> less_tuple = copy<less_values_type...>(std::forward<more_values_type>(more_values)...);
					std::function<return_type(less_values_type...)> lessfun = function;
					std::apply(lessfun, less_tuple);
				};
			}


			template <typename object_type, typename return_type, typename... less_values_type>
			static overload<more_values_type...> of(object_type* object, return_type(object_type::* function)(less_values_type...) const, bool isconst)
			{
				return overload<more_values_type...>(object, function, isconst);
			}

			template <typename object_type, typename return_type, typename... less_values_type>
			static overload<more_values_type...> of(object_type* object, return_type(object_type::* function)(less_values_type...))
			{
				return overload<more_values_type...>(object, function);
			}

			template <typename return_type, typename... less_values_type>
			static overload<more_values_type...> of(return_type(*function)(less_values_type...))
			{
				return overload<more_values_type...>(function);
			}

			inline void operator()(more_values_type&&...values) const { overfunc(std::forward<more_values_type>(values)...); }

			inline bool operator==(const overload& other) const { return other.adress == adress; }

			inline std::function<void()> function(more_values_type&&...values) const
			{
                return [this, values...]()
				{
					overfunc(std::forward<more_values_type>(values)...);
				}; 
			}
		};
	};

	template<class ...values_type> class signal
	{
		struct _hander
		{
			std::function<void(values_type...)> lambda;
			xhqm::software::_adress adress;
			xhqm::signal_type type;
		};
		std::mutex mutex;
		std::list<_hander> handers;
	public:
		signal() = default;
		signal(signal&&) = delete;
		signal(const signal&) = delete;

		inline void emit(const values_type& ...values)
		{
			std::lock_guard lock(mutex);
			for (auto& hander : handers)
			{
				//本线程直接执行
				if (hander.type == signal_type::signal_direct)
				{
					hander.lambda(values...);
				}
				else
				{
					xhqm::software::_signal* signal = new xhqm::software::_signal;
					signal->m_belong_thread = hander.adress.m_belong_thread;
					signal->exec_type = hander.type;
					signal->exec_func = [hander, values...]()
					{
						hander.lambda(values...);
					};

					if (hander.type == signal_type::signal_auto)
					{
						if (hander.adress.this_thread())
						{
							hander.lambda(values...);
							delete signal;
						}
						else
						{
							signal->exec_type = signal_type::signal_queued;
							xhqm::instance<xhqm::signals::events>::get().ins_event(signal);
						}
					}
					//异线程队列执行
					if (hander.type == signal_type::signal_queued)
					{
						xhqm::instance<xhqm::signals::events>::get().ins_event(signal);
					}
					//异线程等待执行
					if (hander.type == signal_type::signal_waited)
					{
						xhqm::instance<xhqm::signals::events>::get().ins_event(signal);
						while (signal->this_exec() == false) { /*wait*/ };
						delete signal;
					}
				}
			}
		}
		inline void operator() (values_type&& ...values)
		{
			emit(std::forward<values_type>(values)...);
		}


		inline void regist(const std::function<void(values_type...)>& lambda, const xhqm::software::_adress& adress, xhqm::signal_type type)
		{
			std::lock_guard lock(mutex);
			handers.push_back(_hander{ lambda,adress, type });
		}
		//仿函数
		template<class object_type>
		inline void regist(object_type& object, xhqm::signal_type type = signal_type::signal_auto)
		{
			std::function<void(values_type...)> lambda = [&object](values_type&&...values)
			{
				object(std::forward<values_type>(values)...);
			};
			void* receiver = nullptr;
			std::memcpy(&receiver, &object, sizeof(void*));
			regist(lambda, xhqm::software::_adress(receiver, nullptr), type);
		}
		template<class object_type>
		inline void regist(const object_type& object, xhqm::signal_type type = signal_type::signal_auto)
		{
			std::function<void(values_type...)> lambda = [object](values_type&&...values)
			{
				object(std::forward<values_type>(values)...);
			};
			void* receiver = nullptr;
			std::memcpy(&receiver, &object, sizeof(void*));
			regist(lambda, xhqm::software::_adress(receiver, nullptr), type);
		}
//		template<>
//		inline void regist(const signals::overload<values_type...>& overload, xhqm::signal_type type)
//		{
//			regist(overload.overfunc, overload.adress, type);
//		}
		//普通函数
		template<class return_type>
		inline void regist(return_type(*function)(values_type...), xhqm::signal_type type = signal_type::signal_auto)
		{
			regist(function, xhqm::software::_adress(function), type);
		}
		//成员函数
		template<class object_type, class return_type>
		inline void regist_notconst(object_type* object, return_type(object_type::* function)(values_type...), signal_type type = signal_type::signal_auto)
		{
			std::function<void(values_type...)> lambda = [=](values_type&&...values)
			{
				(object->*function)(std::forward<values_type>(values)...);
			};
			regist(lambda, xhqm::software::_adress(object, function), type);
		}
		template<class object_type, class return_type>
		inline void regist_hasconst(object_type* object, return_type(object_type::* function)(values_type...) const, signal_type type = signal_type::signal_auto)
		{
			std::function<void(values_type...)> lambda = [=](values_type&&...values)
			{
				(object->*function)(std::forward<values_type>(values)...);
			};
			regist(lambda, xhqm::software::_adress(object, function), type);
		}
		template<class object_type, class return_type>
		inline void regist(object_type* object, return_type(object_type::* function)(values_type...), signal_type type = signal_type::signal_auto)
		{
			regist_notconst<object_type, return_type>(object, function, type);
		}
		template<class object_type, class return_type>
		inline void regist(object_type* object, return_type(object_type::* function)(values_type...) const, signal_type type = signal_type::signal_auto)
		{
			regist_hasconst<object_type, return_type>(object, function, type);
		}

		inline void remove()
		{
			std::lock_guard lock(mutex);
			handers.clear();
		}
		//仿函数
		template<class object_type>
		inline void remove(const object_type& object)
		{
			std::lock_guard lock(mutex);
			void* receiver = nullptr;
			std::memcpy(&receiver, &object, sizeof(void*));
			xhqm::software::_adress adress(receiver, nullptr);
			handers.remove_if([adress](const _hander& select)
				{
					return adress == select.adress;
				});
		}
//		template<>
//		inline void remove(const signals::overload<values_type...>& overload)
//		{
//			std::lock_guard lock(mutex);
//			handers.remove_if([overload](const _hander& select)
//				{
//					return overload.adress == select.adress;
//				});
//		}
		//普通函数
		template<class return_type>
		inline void remove(return_type(*function)(values_type...))
		{
			std::lock_guard lock(mutex);
			xhqm::software::_adress adress(function);
			handers.remove_if([adress](const _hander& select)
				{
					return adress == select.adress;
				});
		}
		//成员函数
		template<class object_type, class return_type>
		inline void remove_notconst(object_type* object, return_type(object_type::* function)(values_type...))
		{
			std::lock_guard lock(mutex);
			xhqm::software::_adress adress(object, function);
			handers.remove_if([adress](const _hander& select)
				{
					return adress == select.adress;
				});
		}
		template<class object_type, class return_type>
		inline void remove_hasconst(object_type* object, return_type(object_type::* function)(values_type...) const)
		{
			std::lock_guard lock(mutex);
			xhqm::software::_adress adress(object, function);
			handers.remove_if([adress](const _hander& select)
				{
					return adress == select.adress;
				});
		}
		template<class object_type, class return_type>
		inline void remove(object_type* object, return_type(object_type::* function)(values_type...))
		{
			remove_notconst<object_type, return_type>(object, function);
		}
		template<class object_type, class return_type>
		inline void remove(object_type* object, return_type(object_type::* function)(values_type...) const)
		{
			remove_hasconst<object_type, return_type>(object, function);
		}
    };
};
#endif
