#ifndef XHQM_SOUL_FUNCTION
#define XHQM_SOUL_FUNCTION
#include "../../head.h"
#include <assert.h>
#include <functional>
namespace xhqm
{
	namespace soul
	{
		constexpr auto step_d_value = 0.000000001;

		template<class Valuetype, typename ... Args>
		using functionbase = std::function<Valuetype(Valuetype, Args ...)>;

		template<class Valuetype, typename ... Args>
		class funcation {
		protected:
			std::string function_name = "funcation";
			xhqm::soul::functionbase<Valuetype, Args ...> _forward;
			xhqm::soul::functionbase<Valuetype, Args ...> _backward;
		public:
			funcation() : _forward(nullptr), _backward(nullptr) { }
			funcation(xhqm::soul::functionbase<Valuetype, Args ...> forward) : _forward(forward), _backward(nullptr) { }
			funcation(xhqm::soul::functionbase<Valuetype, Args ...> forward, xhqm::soul::functionbase<Valuetype, Args ...> backward) : _forward(forward), _backward(backward) { }

			void forward(xhqm::soul::functionbase<Valuetype, Args ...> forward)
			{
				_forward = forward;
			}
			void backward(xhqm::soul::functionbase<Valuetype, Args ...> backward)
			{
				_backward = backward;
			}

			Valuetype forward(Valuetype value, Args ...args) {
				if (_forward) {
					return _forward(value, std::forward<Args>(args)...);
				}
				else {
					return value;
				}
			}
			Valuetype backward(Valuetype value, Args ...args) {
				if (_backward) {
					return _backward(value, std::forward<Args>(args)...);
				}
				else {
					return (_forward(value + xhqm::soul::step_d_value, std::forward<Args>(args)...) - _forward(value, std::forward<Args>(args)...)) / xhqm::soul::step_d_value;
				}
			}

			xhqm::soul::functionbase<Valuetype, Args ...>& forward() { return _forward; };
			xhqm::soul::functionbase<Valuetype, Args ...>& backward() { return _backward; };
		};

		template<class value_type>
		using functionlive = xhqm::soul::funcation<value_type>;
		template<class matrix_type>
		using functionloss = xhqm::soul::funcation<matrix_type, matrix_type>;


		template<class value_type>
		class identical
			: public xhqm::soul::functionlive<value_type>
		{
		public:
			identical() : xhqm::soul::functionlive<value_type>() {
				xhqm::soul::functionlive<value_type>::function_name = "identical";
				xhqm::soul::functionlive<value_type>::forward([](value_type value) ->value_type {
					return value;
					});
				xhqm::soul::functionlive<value_type>::backward([](value_type value) ->value_type {
					return 1;
					});
			}
		};

		template<class value_type>
		class sigmoid 
			: public xhqm::soul::functionlive<value_type>
		{
		public:
			sigmoid() : xhqm::soul::functionlive<value_type>() {
				xhqm::soul::functionlive<value_type>::function_name = "sigmoid";
				xhqm::soul::functionlive<value_type>::forward([](value_type value) ->value_type {
					return 1 / (1 + std::exp(-value));
					; });
				xhqm::soul::functionlive<value_type>::backward([](value_type value) ->value_type {
					return 1 / (2 + std::exp(value) + std::exp(-value));
					});
			}
		};

		template<class value_type>
		class relu
			: public xhqm::soul::functionlive<value_type>
		{
		public:
			relu() : xhqm::soul::functionlive<value_type>() {
				xhqm::soul::functionlive<value_type>::function_name = "relu";
				xhqm::soul::functionlive<value_type>::forward([](value_type value) ->value_type {
					return value > 0 ? value : 0;
					});
				xhqm::soul::functionlive<value_type>::backward([](value_type value) ->value_type {
					return value > 0 ? 1 : 0;
					});
			}
		};


		template<class matrix_type>
		class softmax_with_loss : public xhqm::soul::functionloss<matrix_type>
		{
			using size_type = typename matrix_type::size_type;
			using value_type = typename matrix_type::value_type;
		public:
			softmax_with_loss() : xhqm::soul::functionloss<matrix_type>() {
				xhqm::soul::functionloss<matrix_type>::function_name = "softmax_with_loss";
				//X(?, n) T(n, ?) return value(1,1)
				xhqm::soul::functionloss<matrix_type>::forward([](matrix_type X, matrix_type T) ->matrix_type {
					for (auto& vec : X) {
						value_type addvar = 0;
						for (auto& var : vec)
							addvar = addvar + std::exp(var);
						for (auto& var : vec)
							var = std::exp(var) / addvar;

						for (auto& var : vec)
							var = -std::log(var);
					}

					value_type value = 0.0;
					for (size_type i = 0; i != X.size(); ++i)
						value = value + X.row(i) * T.row(i);
					matrix_type V(1, 1, value);
					return (V / X.size());
					});
				//X(?, n) T(n, ?) return gardB(1,m)
				xhqm::soul::functionloss<matrix_type>::backward([](matrix_type X, matrix_type T) ->matrix_type {
					for (auto& vec : X) {
						value_type addvar = 0;
						for (auto& var : vec)
							addvar = addvar + std::exp(var);
						for (auto& var : vec)
							var = std::exp(var) / addvar;
					}

					return ((X - T) / X.size());
					});
			}
		};
	}
}
#endif