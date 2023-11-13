#ifndef XHQM_SOUL_SOUL
#define XHQM_SOUL_SOUL
#include "function.h"
#include "layer.h"
namespace xhqm
{
	namespace soul
	{
		template<class matrix_type>
		class neural {
		public:
			using size_type = typename matrix_type::size_type;
			using value_type = typename matrix_type::value_type;
			using function_type = xhqm::soul::functionloss<matrix_type>;
		protected:
			function_type _loss;
			std::vector<layerbase<matrix_type>> _layers;
		public:
			neural() { };

			virtual void soul() = 0;
			virtual void loss() = 0;

			//in(1, n) out(1, m)
			virtual matrix_type forward(const matrix_type& in) {
				matrix_type out = in;
				for (auto& lay : _layers)
					out = lay.forward(out);
				return out;
			}
			//lossback(1, m)
			virtual matrix_type backward(const matrix_type& lossback) {
				matrix_type back = lossback;
				for (size_type i = _layers.size(); i != 0; --i)
					back = _layers[i - 1].backward(back);
				return back;
			}
			//mini_bach(bach_size, n)
			virtual value_type train(const matrix_type& mini_bach, const matrix_type& table_bach)
			{
				assert(mini_bach.size() == table_bach.size());

				size_type size = mini_bach.size();
				matrix_type X = neural<matrix_type>::forward(mini_bach);
				matrix_type L = neural<matrix_type>::_loss.backward(X, table_bach);
				matrix_type B = neural<matrix_type>::backward(L);
				return neural<matrix_type>::_loss.forward(X, table_bach)[0][0];
			}
			//dirpath末尾要带"/"
			virtual bool read(std::string dirpath) {
				for (size_type i = 0; i != _layers.size(); ++i) {
					std::string laypath = dirpath + std::to_string(i);
					if (!_layers[i].read(laypath)) return false;
				}
				return true;
			}
			//dirpath末尾要带"/"
			virtual bool save(std::string dirpath) {
				for (size_type i = 0; i != _layers.size(); ++i) {
					std::string laypath = dirpath + std::to_string(i);
					if(!_layers[i].save(laypath)) return false;
				}
				return true;
			}
		};


		template<class matrix_type>
		class tln : public neural<matrix_type>
		{
			using size_type = typename matrix_type::size_type;
			using value_type = typename matrix_type::value_type;
		public:
			tln() :neural<matrix_type>() {
				soul();
				loss();
			};

			virtual void soul() 
			{
				neural<matrix_type>::_layers.push_back(xhqm::soul::layer<xhqm::math::matrix<xhqm::measure>>(28 * 28, 200));
				neural<matrix_type>::_layers.push_back(xhqm::soul::layer<xhqm::math::matrix<xhqm::measure>>(200, 10));
				xhqm::soul::sigmoid<xhqm::measure> funct;
				neural<matrix_type>::_layers[0].function(funct);
			}
			virtual void loss()
			{
				neural<matrix_type>::_loss = xhqm::soul::softmax_with_loss<matrix_type>();
			}
		};
	}
}
#endif