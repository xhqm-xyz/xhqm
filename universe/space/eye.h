#ifndef XHQM_SPACE_EYE
#define XHQM_SPACE_EYE
#include "model.h"
#include "../tool/timesys.h"
#include "../tool/instance.h"
#include "../math/dimension.h"
namespace xhqm
{
	namespace space
	{
		template<class datatype>
		class group :public xhqm::space::model<datatype>
		{
		public:
			xhqmtype(spacegroup)
			virtual void creat() {};//创建模型
			group(xhqm::natural dim) 
				: xhqm::space::model<datatype>(dim)
			{ this->name = "new group"; }
			virtual ~group() {};
		};

		template<class datatype, xhqm::natural dim>
		class root :public xhqm::space::group<datatype>
		{
		public:
			xhqmtype(spaceroot)
			virtual void creat() {};//创建模型
			root() : xhqm::space::group<datatype>(dim)
			{ this->name = "new root-" + std::to_string(dim); }
			virtual ~root() {};

			static root* instance() {
				if (!xhqm::instance<root*>::get())
					xhqm::instance<root*>::get() = new root();
				return xhqm::instance<root*>::get();
			}
		};
		

        template<class datatype>
		class eye:public xhqm::space::model<datatype>
		{
		protected:
            using xview = typename xhqm::math::matrix<xhqm::color>;
		public:
			virtual void dynamicmodel(model<datatype>* model) 		//绘制模型
			{
				model->data.updata();
				xhqm::space::xmat from;
				xhqm::space::xvec move;
				xhqm::space::xmat oldfrom;
				xhqm::space::xvec oldmove;
				this->GetMicroPosition(oldfrom, oldmove);
				m_flexible* (*this);
				xhqm::space::model<datatype>::MicroToMicro(model, this, from, move);
				this->SetMicroPosition(oldfrom, oldmove);

				//datatype * from + move
			};
			virtual void draw()
			{
				xhqm::space::model<datatype>::dynamic();
			}
		public:
		public:
			xhqmtype(eye)


			eye(std::size_t w, std::size_t h, xhqm::natural d)
                : xhqm::space::model<datatype>(d)
			{
				m_flexible = (xhqm::space::system::flexible({ true, false, false }, w / (double)h) + xhqm::space::system::mati(d));
				this->name = "eye-" + std::to_string(w)+"*"+ std::to_string(h);
				resetview(w, h);
			}
			virtual ~eye() { }

			void resetview(std::size_t w, std::size_t h)
			{
				m_view = xview(w, h);
				clearview();
			}
			void clearview()
			{
				for (auto&row: m_view)
					for (auto& rgba : row)
						rgba = m_backcolor;
			}
			std::size_t width()
			{
				std::size_t rowdim;
				std::size_t coldim;
				m_view.dimension(rowdim, coldim);
				return rowdim;
			}
			std::size_t height()
			{
				std::size_t rowdim;
				std::size_t coldim;
				m_view.dimension(rowdim, coldim);
				return coldim;
			}

			virtual void move(measure dx, measure dy, measure dz)
			{
				xhqm::space::xmat from;
				xhqm::space::xvec move;
				xhqm::space::model<datatype>::MicroToMicro(this->root(), this, from, move);
				from = xhqm::space::system::matdim(from, this->dim);
				this->data.m_vector = this->data.m_vector + xhqm::space::xvec{ dx, dy, dz } * m_flexible * from.invmat();
			}
			virtual void rote(measure dx, measure dy, measure dz)
			{
				xhqm::space::xmat from;
				xhqm::space::xvec move;
				this->GetMacroPosition(from, move);
				xhqm::space::xmat rotex{ {1.0, 0.0, 0.0}, {0.0, std::cos(dx), std::sin(dx)}, {0.0, -std::sin(dx), std::cos(dx) } };
				xhqm::space::xmat rotey{ {std::cos(dy), 0.0, -std::sin(dy)}, {0.0, 1.0, 0.0}, {std::sin(dy), 0.0, std::cos(dy) } };
				xhqm::space::xmat rotez{ {std::cos(dz), std::sin(dz), 0.0}, {-std::sin(dz), std::cos(dz), 0.0}, {0.0, 0.0, 1.0 } };
				xhqm::space::xmat rote = xhqm::space::system::matdim(rotex * rotey * rotez * from, this->dim);
				this->SetMacroPosition(rote, move);
			}
			virtual void flexible(measure dx, measure dy, measure dz)
			{
				xhqm::space::xmat flexible{ {dx, 0.0, 0.0}, {0.0, dy, 0.0}, {0.0, 0.0, dz} };
				flexible = xhqm::space::system::matdim(flexible, this->dim);
				m_flexible = flexible * m_flexible;
			}

		public:    
			xhqm::color m_backcolor = xrgba(0, 0, 0, 255);
			xhqm::space::xmat m_flexible;
			xview m_view;
		};
	}
}

#endif 