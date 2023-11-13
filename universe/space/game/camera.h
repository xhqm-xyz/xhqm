#ifndef XHQM_GAME_EYE
#define XHQM_GAME_EYE
#include "model.h"
#include "../tool/timesys.h"
#include "../tool/instance.h"
namespace xhqm
{
	namespace game
	{
		template<class type>
		class group :public xhqm::game::model<type>
		{
		public:
			xhqmtype(gamegroup)
			virtual void creat() {};//创建模型
			group() : xhqm::game::model<type>()
			{ this->name = "new group"; }
			virtual ~group() {};
		};

		template<class type>
		class root :public xhqm::game::group<type>
		{
		public:
			xhqmtype(gameroot)
			virtual void creat() {};//创建模型
			root() : xhqm::game::group<type>()
			{ this->name = "new root"; }
			virtual ~root() {};

			static root* instance() {
				if (!xhqm::instance<root*>::get())
					xhqm::instance<root*>::get() = new root();
				return xhqm::instance<root*>::get();
			}
		};
		
        template<class type>
		class eye:public xhqm::game::model<type>
		{
		public:
			xhqmtype(gameeye)

			virtual void draw()
			{
				xhqm::game::model<type>::dynamic();
			}


			virtual void creat()
			{
				this->data.staticdata.init(1, 0, 0);

				this->data.staticdata.m_vertexs[0] = { 0,0,-1 };//视点位置
				this->data.staticdata.m_normals[0] = xhqm::game::sys<type>::veco() - this->data.staticdata.m_vertexs[0];//视面方向
				this->viewlen = this->data.staticdata.m_normals[0].modulus();
				this->data.init();
			}

			eye(xhqm::natu w, xhqm::natu h)
				: xhqm::game::model<type>(), height(h), width(w)
			{
				m_flexible = xhqm::game::mat<type>::flexible(w / (type)h, 1, 1);
				this->name = "eye-" + std::to_string(w)+"*"+ std::to_string(h);
			}

			virtual ~eye() {};

			virtual void move(type dx, type dy, type dz)
			{
				xhqm::game::mat<type> from;
				xhqm::game::vec<type> move;
				xhqm::game::model<type>::mic2mic(this->root(), this, from, move);
				this->data.m_vec = this->data.m_vec + xhqm::game::vec<type>(dx, dy, dz) * m_flexible * from.invmat();
			}
			virtual void rote(type dx, type dy, type dz)
			{
				xhqm::game::mat<type> from;
				xhqm::game::vec<type> move;
				this->getmac(from, move);
				xhqm::game::mat<type> rote = xhqm::game::mat<type>::rotate(dx, dy, dz) * from;
				this->setmac(rote, move);
			}
			virtual void flex(type dx, type dy, type dz)
			{
				m_flexible = xhqm::game::mat<type>::flexible(dx, dy ,dz) * m_flexible;
			}
			virtual void view(xhqm::natu w, xhqm::natu h)
			{
				w = (w == 0 ? 1 : w);
				h = (h == 0 ? 1 : h);
				xhqm::natu maxw = xmax(w, width);
				xhqm::natu minw = xmin(w, width);
				xhqm::natu maxh = xmax(h, height);
				xhqm::natu minh = xmin(h, height);
				type dw = w > width ? maxw / (type)minw : minw / (type)maxw;
				type dh = h > height ? maxh / (type)minh : minh / (type)maxh;
				m_flexible = xhqm::game::mat<type>::flexible(dw, dh, 1.0) * m_flexible;
				width = w;
				height = h;
			}
		public:    
			xhqm::color m_backcolor = xrgba(0, 0, 0, 255);
			xhqm::game::mat<type> m_flexible;
		protected:
			type viewlen;
			xhqm::natu height;
			xhqm::natu width;
		};


		template<class type>
		class light :public xhqm::game::model<type>
		{
		public:
            virtual ~light() {};
			xhqmtype(light)
			light() : xhqm::game::model<type>() { this->name = "light"; }
			virtual void creat()
			{
				this->data.staticdata.init(1, 0, 0);
//				this->data.staticdata.m_vertexs[0];//光源位置
//				this->data.staticdata.m_normals[0];//有方向，平行光源 无方向，点光源
//				this->data.staticdata.m_colours[0] = xhqm::game::colour<xhqm::byte>( 255, 255, 255, 255 );//光源颜色
				this->data.init();
			}
			void upcolor(xhqm::color col)
			{
				std::lock_guard<std::mutex> lock(this->data.mutex);
				this->data.staticdata.m_colours[0] = { xrgbar(col), xrgbag(col), xrgbag(col), xrgbaa(col) };
				this->data.init();
			}
			void moveto(type dx, type dy, type dz)
			{
				std::lock_guard<std::mutex> lock(this->data.mutex);
				this->data.staticdata.m_vertexs[0] = { dx,dy,dz };
				this->data.init();
			}
			void move(type dx, type dy, type dz)
			{
				this->data.m_vec = this->data.m_vec + xhqm::game::vec<type>(dx, dy, dz);
			}
			void rote(type dx, type dy, type dz)
			{
				this->data.m_mat = xhqm::game::mat<type>::rotate(dx, dy, dz) * this->data.m_mat;
			}
		};
	}
}

#endif 
