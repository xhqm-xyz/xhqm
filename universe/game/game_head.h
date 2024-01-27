#ifndef XHQM_GAME
#define XHQM_GAME
#include "../../head.h"
#include "../../conception/exist.h"
#include "../../conception/struct.h"
#include "../../metaclass/template.h"
namespace xhqm
{
	namespace game
	{
		//精灵
		struct sprite
		{
			xhqm::string name;
			virtual bool features() = 0;//特性
		};
		//历史
		struct frame :public xhqm::game::sprite
		{
			//进入退出
			virtual bool init() = 0;
			virtual bool live() = 0;
			virtual bool exit() = 0;
		};
		//地图
		struct space :public xhqm::game::sprite
		{
			//进入退出
			virtual bool init() = 0;
			virtual bool live() = 0;
			virtual bool exit() = 0;
		};
		//时空位置
		struct place :public xhqm::game::sprite
		{
			//触发
			virtual bool trigger() = 0;
		};

		
		//事情基类
		struct thing :public xhqm::game::sprite
		{
			xhqm::size step = 0;
			//发生推进结束
			virtual bool happen() = 0;
			virtual bool except() = 0;
			virtual bool finish() = 0;
		};
		//物体基类
		struct object :public xhqm::game::sprite
		{
			//能力
			virtual bool ability() = 0;
		};


		//技能
		struct skill :public xhqm::game::thing
		{

		};
		//事件
		struct event :public xhqm::game::thing
		{

		};

		//人物
		struct people :public xhqm::game::object
		{

		};

		//材料
		struct material :public xhqm::game::object
		{

		};
		//器具
		struct fixtures :public xhqm::game::material
		{

		};



		//全局游戏系统
		class system : public xhqm::game::sprite, xhqm::exist
		{
		public:
			virtual bool star() = 0;
			virtual bool live() = 0;
			virtual bool over() = 0;
		protected:
			virtual void doexcept() override { this->star(); };
			virtual void runexcept() override { this->live(); };
			virtual void undoexcept() override { this->over(); };
		};
	}
}

#endif