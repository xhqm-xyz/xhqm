#ifndef XHQM_RPGASTAR
#define XHQM_RPGASTAR
#include "rpg_path.h"
#include <queue>

namespace xhqm::rpg
{
	struct star : public xhqm::rpg::path::algorithm { };

	class AStar : public star
	{
	public:
		struct state
		{
			xhqm::measure g = 0; //��û�ɱ�
			xhqm::measure h = 0; //Ԥ�Ƴɱ�
			xhqm::rpg::path::place_dis<3> postion{0, 0, 0};
			inline xhqm::measure price() { return g + h; }; //���մ���
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
		//using function = std::function<void(xhqm::tree<state>*)>;
	protected:
		const xhqm::size space_lay = 0;
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//�Թ���ͼ true ����
		space currMap = {};//ʵʱ�Թ� true ����
		place starPos = {};//��ʼλ��
		place currPos = {};//ʵʱλ��
		place goalPos = {};//Ŀ��λ��

		xhqm::tree<state>* rootPtr = nullptr;//·����
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;
		//function funGreedy = nullptr; //���㺯��
	public:
		AStar(xhqm::size lay, xhqm::size row, xhqm::size col);
		virtual ~AStar();

		virtual void walk(xhqm::size x, xhqm::size y, xhqm::size z, bool val) { mazeMap[x][y][z] = val; };
		virtual bool walk(xhqm::size x, xhqm::size y, xhqm::size z) const { return mazeMap[x][y][z]; };

		virtual void star(place pos) { starPos = pos; currPos = pos; };
		virtual void stop(place pos) { goalPos = pos; };
		virtual place star() const { return starPos; };
		virtual place curr() const { return currPos; };
		virtual place stop() const { return goalPos; };
		virtual bool good() { return goalPtr; };

		virtual std::vector<place> path();
		virtual void show(place showPos);

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;
	protected:
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions);
	};

	//xhqm�޸��㷨 20231103
	class AStarDynamic : public AStar
	{
	public:
		using state = xhqm::rpg::AStar::state;
		using place = xhqm::rpg::AStar::place;
		using space = xhqm::rpg::AStar::space;
	public:
		AStarDynamic(xhqm::size lay, xhqm::size row, xhqm::size col);

		virtual bool check(const place& pos) const {
			bool ok = true;
			ok &= (0 <= pos[0] && pos[0] < space_lay);
			ok &= (0 <= pos[1] && pos[1] < space_row);
			ok &= (0 <= pos[2] && pos[2] < space_col);
			if(ok) ok &= (currMap[pos[0]][pos[1]][pos[2]]);
			return ok;
		}

		virtual void stop(place pos) { 
			goalPos = pos; 
			currMap = mazeMap; 
		};
		virtual place stop() const;

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;
	protected:
		
		//virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::path::actions>& actions);
	};

	//xhqm�޸��㷨 20231103
	class AStarDynMultiple : public AStarDynamic
	{
	public:
		using state = xhqm::rpg::AStar::state;
		using place = xhqm::rpg::AStar::place;
		using space = xhqm::rpg::AStar::space;
	protected:
		std::vector<place> starsPos;//��ʼλ��
		std::vector<place> currsPos;//ʵʱλ��
		std::vector<xhqm::tree<state>*> currPtrs;
	public:
		AStarDynMultiple(xhqm::size lay, xhqm::size row, xhqm::size col);

		virtual place stop() const override;
		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;
	protected:

		//virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::path::actions>& actions);
	};
}


#endif