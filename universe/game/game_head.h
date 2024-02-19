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
		//����
		struct sprite
		{
			xhqm::string name;
			virtual bool features() = 0;//����
		};
		//��ʷ
		struct frame :public xhqm::game::sprite
		{
			//�����˳�
			virtual bool init() = 0;
			virtual bool live() = 0;
			virtual bool exit() = 0;
		};
		//��ͼ
		struct space :public xhqm::game::sprite
		{
			//�����˳�
			virtual bool init() = 0;
			virtual bool live() = 0;
			virtual bool exit() = 0;
		};
		//ʱ��λ��
		struct place :public xhqm::game::sprite
		{
			//����
			virtual bool trigger() = 0;
		};

		
		//�������
		struct thing :public xhqm::game::sprite
		{
			xhqm::size step = 0;
			//�����ƽ�����
			virtual bool happen() = 0;
			virtual bool except() = 0;
			virtual bool finish() = 0;
		};
		//�������
		struct object :public xhqm::game::sprite
		{
			//����
			virtual bool ability() = 0;
		};


		//����
		struct skill :public xhqm::game::thing
		{

		};
		//�¼�
		struct event :public xhqm::game::thing
		{

		};

		//����
		struct people :public xhqm::game::object
		{

		};

		//����
		struct material :public xhqm::game::object
		{

		};
		//����
		struct fixtures :public xhqm::game::material
		{

		};



		//ȫ����Ϸϵͳ
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