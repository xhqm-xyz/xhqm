#ifndef XHQM_SOUL_LAYER
#define XHQM_SOUL_LAYER
#include <random>
#include "function.h"
#include "../math/vector.h"
#include "../math/matrix.h"
#include "../../system/codesys.h"
namespace xhqm
{
	namespace soul
	{
		constexpr auto learning_rate = 0.01;

		template<class matrix_type>
		class layerbase {
		public:
			using size_type = typename matrix_type::size_type;
			using value_type = typename matrix_type::value_type;
			using function_type = xhqm::soul::functionlive<value_type>;
		protected:
			size_type _n;
			size_type _m;
			matrix_type _I;
			matrix_type _W;
			matrix_type _B;
			matrix_type _O;
			matrix_type _gradI;
			matrix_type _gradW;
			matrix_type _gradB;
			matrix_type _gradO;
			function_type _function;
		public:

			layerbase(const size_type& n = 0, const size_type& m = 0)
				: _n(n), _m(m), _W(n, m), _B(1, m), _gradW(n, m), _gradB(1, m){
				_function = xhqm::soul::identical<value_type>();
				//out = function(in * W + B)
			}

			virtual void WValue() {};
			virtual void BValue() {};
			virtual void function() {};
			void function(const function_type& fun)
			{
				_function = fun;
			}
			//I(1, n) O(1, m)
			virtual const matrix_type& forward(const matrix_type& I)
			{
				matrix_type B(I.size(), _B[0].size());
				for (auto& vec : B) vec = _B[0];

				_I = I;
				_O = _I * _W + B;
				_gradO = _O;
				if (_function.forward()) 
					_O.execfun(_function.forward());
				if (_function.backward())
					_gradO.execfun(_function.backward());
				return _O;
			}
			//gradO 携带损失函数对当前层激活函数的导数信息 F'loss/F'n 
			virtual const matrix_type& backward(const matrix_type& gradO)
			{
				for (size_type i = 0; i != _O.size(); ++i)
					for (size_type j = 0; j != _O[0].size(); ++j)
						_gradO[i][j] = _gradO[i][j] * gradO[i][j];

				_gradB.fill(0);
				for (size_type i = 0; i != _O.size(); ++i)
					for (size_type j = 0; j != _O[0].size(); ++j)
						_gradB[0][j] = _gradB[0][j] + _gradO[i][j];

				_gradI = _gradO * _W.tramat();
				_gradB = _gradB / _O.size();
				_gradW = _I * _gradO;

				_W = _W - xhqm::soul::learning_rate * _gradW;
				_B = _B - xhqm::soul::learning_rate * _gradB;

				return _gradI;
			}

			virtual bool read(std::string path) {

				std::fstream file(path, std::ios::in);
				if (!file.is_open()) return false;

				std::string n; std::string m;
				file >> n; file >> m;
				xhqm::templates::str2val<size_type>(n, _n);
				xhqm::templates::str2val<size_type>(m, _m);

				std::string data;
				_B = matrix_type(1, _m);
				_W = matrix_type(_n, _m);

				file >> data;
				if (data != "B") return false;
				file >> data;
				auto B = xhqm::codesys::split_string(data, ',');
				for (size_type i = 0; i != _m; ++i)
					xhqm::templates::str2val<value_type>(B[i], _B[0][i]);

				file >> data;
				if (data != "W") return false;
				for (size_type i = 0; i != _n; ++i) {
					file >> data;
					auto W = xhqm::codesys::split_string(data, ',');
					for (size_type j = 0; j != _m; ++j) {
						xhqm::templates::str2val<value_type>(W[j], _W[i][j]);
					}
				}

				file.close();
				return true;
			}
			virtual bool save(std::string path) {
				std::fstream file(path, std::ios::out);
				if (!file.is_open())return false;
				file << _n << std::endl;
				file << _m << std::endl;

				file << "B" << std::endl;
				for (auto& vec : _B) {
					for (auto& var : vec) {
						file << std::fixed << std::setprecision(17) << var << ",";
					}
					file << std::endl;
				}
				file << "W" << std::endl;
				for (auto& vec : _W) {
					for (auto& var : vec) {
						file << std::fixed << std::setprecision(17) << var << ",";
					}
					file << std::endl;
				}
				file << "END" << std::endl;
				file.close();
				return true;
			}
		};


		template<class matrix_type>
		class layer : public layerbase<matrix_type> {
		public:
			using size_type = typename layerbase<matrix_type>::size_type;
			using value_type = typename layerbase<matrix_type>::value_type;
			using function_type = typename layerbase<matrix_type>::function_type;
		public:
			layer(const size_type& n, const size_type& m) : layerbase<matrix_type>(n, m)
			{
				WValue();
				BValue();
				function();
			}

			virtual void WValue()
			{
				// 第一个参数为高斯分布的平均值，第二个参数为标准差
				std::normal_distribution<value_type> distribution(0.0, 1/std::sqrt(layerbase<matrix_type>::_m));
				std::default_random_engine generator(xhqm::timesys::utime());
				for (auto& vec : layerbase<matrix_type>::_W)
					for (auto& var : vec)
						var = distribution(generator);
			}
			virtual void BValue()
			{
				// 第一个参数为高斯分布的平均值，第二个参数为标准差
				std::normal_distribution<value_type> distribution(0.0, 1 / std::sqrt(layerbase<matrix_type>::_m));
				std::default_random_engine generator(xhqm::timesys::utime());
				for (auto& vec : layerbase<matrix_type>::_B)
					for (auto& var : vec)
						var = distribution(generator);
			}
			virtual void function()
			{
				// 默认使用恒等函数 xhqm::soul::identical<value_type>()
			};
		};
	}
}
#endif