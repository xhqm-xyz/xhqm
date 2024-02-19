#include "rpg_astar.h"

namespace xhqm::rpg
{
	AStar::AStar(xhqm::size lay, xhqm::size row, xhqm::size col)
		: space_lay(lay), space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0,0 };
		this->goalPos = place{ 0,0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<3>(lay, xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true)));
	}
	AStar::~AStar()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void AStar::init()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
		nextPtr = new xhqm::tree<state>(state{ 0.0, 0.0, currPos });
		rootPtr = new xhqm::tree<state>();
		rootPtr->insert(nextPtr);
		currPtr = rootPtr;
		goalPtr = nullptr;
		currMap = mazeMap;
	}
	bool AStar::walk()
	{
		init();
		bool isFindEnd = false;//�ܷ��ߵ����յ�

		while (currPtr)
		{
			//û����һ�ڵ㣬������һ�ڵ�
			if (currPtr->empty()) {
				currPtr = currPtr->parent();
				continue;
			}

			//�����߹��ĵ��Ƶ����
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* nodePtr)
				{
					return !(Check(nodePtr->data));
				});

			//����·��������ͬ��������һ��
			nextPtr = currPtr->child(0); 
			if (!Check(nextPtr->data)) {
				currPtr = currPtr->parent();
				continue;
			}
			//�ƶ� 
			currPtr = nextPtr;
			currPos = currPtr->data.postion;
			currMap[currPos[0]][currPos[1]][currPos[2]] = false;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}

			state next; // ���չ���������һ��״̬ ���״̬����Լ������������
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					for (xhqm::size k = 0; k < action_num; ++k)
						if (Exec(next, currPtr->data, { action[i], action[j], action[k] }))
							currPtr->insert(new xhqm::tree<state>(next));

			//���ճɱ����򣬻�ȡ��С�ɱ�
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price() < second->data.price());
				});
		}

		return isFindEnd;
	}
	bool AStar::next()
	{
		if (currPtr)
		{
			//û����һ�ڵ㣬������һ�ڵ�
			if (currPtr->empty()) {
				currPtr = currPtr->parent();
				return next();
				//return false;
			}

			//�����߹��ĵ��Ƶ����
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* nodePtr)
				{
					return !(Check(nodePtr->data));
				});

			//����·��������ͬ��������һ��
			nextPtr = currPtr->child(0);
			if (!Check(nextPtr->data)) {
				currPtr = currPtr->parent();
				return next();
				//return false;
			}
			//�ƶ� 
			currPtr = nextPtr;
			currPos = currPtr->data.postion;
			currMap[currPos[0]][currPos[1]][currPos[2]] = false;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			state next; // ���չ���������һ��״̬ ���״̬����Լ������������
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					for (xhqm::size k = 0; k < action_num; ++k)
						if (Exec(next, currPtr->data, { action[i], action[j], action[k] }))
							currPtr->insert(new xhqm::tree<state>(next));

			//���ճɱ����򣬻�ȡ��С�ɱ�
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price() < second->data.price());
				});
		}
		else
		{
			return true;
		}

		return false;
	}
	std::vector<AStar::place> AStar::path()
	{
		std::vector<place> paths;
		xhqm::tree<state>* pathPtr = goalPtr;
		if (pathPtr) {
			paths.push_back(pathPtr->data.postion);
			while (pathPtr->parent())
			{
				pathPtr = pathPtr->parent();
				paths.push_back(pathPtr->data.postion);
			}
		}
		return paths;
	}
	void AStar::show(place showPos)
	{
		std::cout << "\033c";
		for (xhqm::size i = 0; i < space_lay; ++i) {
			for (xhqm::size j = 0; j < space_row; ++j) {
				for (xhqm::size k = 0; k < space_col; ++k) {
					const place Pos{ i, j, k };
					if (Pos != showPos && Pos != goalPos)
						std::cout << (mazeMap[i][j][k] ? "\033[0;37;47m  \033[0m" : "\033[0;31;41m  \033[0m");
					else if (Pos == showPos)
						std::cout << "\033[0;32;42m  \033[0m";
					else if (Pos == goalPos)
						std::cout << "\033[0;34;44m  \033[0m";
				}
				std::cout << j + 1 << std::endl;
			}
			std::cout << std::endl << i + 1 << std::endl << std::endl;
		}
	}
	bool AStar::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]][now.postion[2]];
	}
	bool AStar::Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions)
	{
		bool exec = true; state temp1, temp2;
		//��ȡ��λ��
		if (exec) exec &= xhqm::rpg::path::execAction<3>(0, space_lay, temp1.postion, curr.postion, actions[0]);
		if (exec) exec &= xhqm::rpg::path::execAction<3>(1, space_row, temp2.postion, temp1.postion, actions[1]);
		if (exec) exec &= xhqm::rpg::path::execAction<3>(2, space_col, next.postion, temp2.postion, actions[2]);
		if (exec) exec &= currMap[next.postion[0]][next.postion[1]][next.postion[2]];
		//��û�ɱ�
		xhqm::measure gval = 0.0;
		if (actions[0] == xhqm::rpg::path::actions::stoped) gval += 1.0;
		if (actions[1] == xhqm::rpg::path::actions::stoped) gval += 1.0;
		if (actions[2] == xhqm::rpg::path::actions::stoped) gval += 1.0;
		next.g = curr.g + std::sqrt(gval);
		//Ԥ�Ƴɱ�
		xhqm::size hval = 0;
		//hval += (xhqm_abs(next.postion[0], goalPos[0]) * xhqm_abs(next.postion[0], goalPos[0]));
		//hval += (xhqm_abs(next.postion[1], goalPos[1]) * xhqm_abs(next.postion[1], goalPos[1]));
		//hval += (xhqm_abs(next.postion[2], goalPos[2]) * xhqm_abs(next.postion[2], goalPos[2]));
		//next.h = std::sqrt(static_cast<xhqm::measure>(hval));
		hval += xhqm_abs(next.postion[0], goalPos[0]);
		hval += xhqm_abs(next.postion[1], goalPos[1]);
		hval += xhqm_abs(next.postion[2], goalPos[2]);
		next.h = static_cast<xhqm::measure>(hval);
		return exec;
	}


	AStarDynamic::AStarDynamic(xhqm::size lay, xhqm::size row, xhqm::size col)
		: AStar(lay, row, col)
	{
	}
	AStarDynamic::place AStarDynamic::stop() const
	{
		{
			place stopPos = goalPos;
			do {
				if (std::rand() % 2)
					stopPos[0] = goalPos[0] + std::rand() % 2;
				else
					stopPos[0] = goalPos[0] - std::rand() % 2;
				if (std::rand() % 2)
					stopPos[1] = goalPos[1] + std::rand() % 2;
				else
					stopPos[1] = goalPos[1] - std::rand() % 2;
				if (std::rand() % 2)
					stopPos[2] = goalPos[2] + std::rand() % 2;
				else
					stopPos[2] = goalPos[2] - std::rand() % 2;
			} while (!check(stopPos));
			return stopPos;
		};
	}
	void AStarDynamic::init()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
		rootPtr = new xhqm::tree<state>(state{ 0.0, 0.0, currPos });
		currPtr = rootPtr;
		goalPtr = nullptr;
		currMap = mazeMap;
	}
	bool AStarDynamic::walk()
	{
		init();
		bool isFindEnd = false;//�ܷ��ߵ����յ�

		while (currPos != goalPos)
		{
			//��ǰ�����߹�������ʹ��
			currMap[currPos[0]][currPos[1]][currPos[2]] = false;

			state next; // ���չ���������һ��״̬ ���״̬����Լ������������
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					for (xhqm::size k = 0; k < action_num; ++k)
						if (Exec(next, currPtr->data, { action[i], action[j], action[k] }))
							currPtr->insert(new xhqm::tree<state>(next));

			//�����ܳɱ���С��������
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price() < second->data.price());
				});

			//�����߹��Ľڵ��Ƶ����
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* nodePtr)
				{
					return !(Check(nodePtr->data));
				});

			//�ƶ� 
			//���ܻ��������ͬ
			if (currPtr->empty()) break;
			currPtr = currPtr->child(0);
			currPos = currPtr->data.postion;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
			}
		}

		return isFindEnd;
	}
	bool AStarDynamic::next()
	{
		if (currPos != goalPos)
		{
			state next; // ���չ���������һ��״̬ ���״̬����Լ������������
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					for (xhqm::size k = 0; k < action_num; ++k)
						if (Exec(next, currPtr->data, { action[i], action[j], action[k] }))
							currPtr->insert(new xhqm::tree<state>(next));

			//�����ܳɱ���С��������
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price() < second->data.price());
				});

			//�����߹��Ľڵ��Ƶ����
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* nodePtr)
				{
					return !(Check(nodePtr->data));
				});

			//�ƶ� 
			//���ܻ��������ͬ
			if (currPtr->empty()) return true;
			currPtr = currPtr->child(0);
			currPos = currPtr->data.postion;
			if (currPos == goalPos) goalPtr = currPtr;
		}

		return (currPos == goalPos);
	}


	AStarDynMultiple::AStarDynMultiple(xhqm::size lay, xhqm::size row, xhqm::size col)
		: AStarDynamic(lay, row, col)
	{
	}
	AStarDynMultiple::place AStarDynMultiple::stop() const
	{
		place stopPos = goalPos;
		do {

		} while (!check(stopPos));
		return stopPos;
	}
	void AStarDynMultiple::init()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
		rootPtr = new xhqm::tree<state>(state{ 0.0, 0.0, currPos });
		currPtr = rootPtr;
		goalPtr = nullptr;
		currMap = mazeMap;
	}
	bool AStarDynMultiple::walk()
	{
		return false;
	}
	bool AStarDynMultiple::next()
	{
		return false;
	}
}