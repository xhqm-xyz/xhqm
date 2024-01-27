#include "rpg_fsearch.h"

namespace xhqm::rpg
{
	dfs2d::dfs2d(xhqm::size row, xhqm::size col)
		: space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0 };
		this->goalPos = place{ 0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true));
	}
	dfs2d::~dfs2d()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void dfs2d::init()
	{
		currMap = mazeMap;
		currMap[currPos[0]][currPos[1]] = false;

		xhqm::rpg::path::deleteTree(rootPtr);
		rootPtr = new xhqm::tree<state>(state{ 0, currPos });

		m_sdfs = std::stack<xhqm::tree<state>*>();
		m_sdfs.push(rootPtr);

		goalPtr = nullptr;
	}
	bool dfs2d::walk()
	{
		init();
		bool isFindEnd = false;

		while (!m_sdfs.empty())
		{
			currPos = m_sdfs.top()->data.postion; //移动
			currPtr = m_sdfs.top(); //深入
			m_sdfs.pop(); // 栈顶元素出栈

			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}


			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					state temp, next;
					bool canExec = true;
					// 按照规则生成下一个状态 如果状态满足约束条件则入栈
					if (canExec) canExec &= Exec1(temp, currPtr->data, action[i]);
					if (canExec) canExec &= Exec2(next, temp, action[j]);
					if (canExec) canExec &= Check(next);
					if (canExec) {
						currMap[next.postion[0]][next.postion[1]] = false; // 访问标记
						next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
						nextPtr = new xhqm::tree<state>(next);
						currPtr->insert(nextPtr); // 记录元素关系
						m_sdfs.push(nextPtr); // 栈顶元素入栈
					}
				}
			}
		}

		return isFindEnd;
	}
	bool dfs2d::next()
	{
		if (!m_sdfs.empty())
		{
			currPos = m_sdfs.top()->data.postion; //移动
			currPtr = m_sdfs.top(); //深入
			m_sdfs.pop(); // 栈顶元素出栈

			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					state temp, next;
					bool canExec = true;
					// 按照规则生成下一个状态 如果状态满足约束条件则入栈
					if (canExec) canExec &= Exec1(temp, currPtr->data, action[i]);
					if (canExec) canExec &= Exec2(next, temp, action[j]);
					if (canExec) canExec &= Check(next);
					if (canExec) {
						currMap[next.postion[0]][next.postion[1]] = false; // 访问标记
						next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
						nextPtr = new xhqm::tree<state>(next);
						currPtr->insert(nextPtr); // 记录元素关系
						m_sdfs.push(nextPtr); // 栈顶元素入栈
					}
				}
			}
		}
		return false;
	}
	std::vector<dfs2d::place> dfs2d::path()
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
	void dfs2d::show(place showPos)
	{
		std::cout << "\033c";
		for (xhqm::size i = 0; i < space_row; ++i) {
			for (xhqm::size j = 0; j < space_col; ++j) {
				const place Pos{ i, j };
				if (Pos != showPos && Pos != goalPos)
					std::cout << (mazeMap[i][j] ? "\033[0;37;47m  \033[0m" : "\033[0;31;41m  \033[0m");
				else if (Pos == showPos)
					std::cout << "\033[0;32;42m  \033[0m";
				else if (Pos == goalPos)
					std::cout << "\033[0;34;44m  \033[0m";
			}
			std::cout << i + 1 << std::endl;
		}
	}
	bool dfs2d::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]];
	}
	bool dfs2d::Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next = curr;
		switch (action)
		{
		case xhqm::rpg::path::actions::forward:
			next.postion[0] = curr.postion[0] + 1;
			if (next.postion[0] >= space_row) return false;
			break;
		case xhqm::rpg::path::actions::stoped:
			next.postion[0] = curr.postion[0];
			break;
		case xhqm::rpg::path::actions::backward:
			if (curr.postion[0] == 0) return false;
			next.postion[0] = curr.postion[0] - 1;
			break;
		default:
			break;
		}
		return true;
	}
	bool dfs2d::Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next = curr;
		switch (action)
		{
		case xhqm::rpg::path::actions::forward:
			next.postion[1] = curr.postion[1] + 1;
			if (next.postion[1] >= space_col) return false;
			break;
		case xhqm::rpg::path::actions::stoped:
			next.postion[1] = curr.postion[1];
			break;
		case xhqm::rpg::path::actions::backward:
			if (curr.postion[1] == 0) return false;
			next.postion[1] = curr.postion[1] - 1;
			break;
		default:
			break;
		}
		return true;
	}


	dfs3d::dfs3d(xhqm::size lay, xhqm::size row, xhqm::size col)
		: space_lay(lay), space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0,0 };
		this->goalPos = place{ 0,0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<3>(lay, xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true)));
	}
	dfs3d::~dfs3d()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void dfs3d::init()
	{
		currMap = mazeMap;
		currMap[currPos[0]][currPos[1]][currPos[2]] = false;

		xhqm::rpg::path::deleteTree(rootPtr);
		rootPtr = new xhqm::tree<state>(state{ 0, currPos });

		m_sdfs = std::stack<xhqm::tree<state>*>();
		m_sdfs.push(rootPtr);

		goalPtr = nullptr;
	}
	bool dfs3d::walk()
	{
		init();
		bool isFindEnd = false;

		while (!m_sdfs.empty())
		{
			currPos = m_sdfs.top()->data.postion; //移动
			currPtr = m_sdfs.top(); //深入
			m_sdfs.pop(); // 栈顶元素出栈

			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					for (xhqm::size k = 0; k < action_num; ++k)
					{
						state temp1, temp2, next;
						bool canExec = true;
						// 按照规则生成下一个状态 如果状态满足约束条件则入栈
						if (canExec) canExec &= Exec1(temp1, currPtr->data, action[i]);
						if (canExec) canExec &= Exec2(temp2, temp1, action[j]);
						if (canExec) canExec &= Exec2(next, temp2, action[k]);
						if (canExec) canExec &= Check(next);
						if (canExec) {
							currMap[next.postion[0]][next.postion[1]][next.postion[2]] = false; // 访问标记
							next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
							nextPtr = new xhqm::tree<state>(next);
							currPtr->insert(nextPtr); // 记录元素关系
							m_sdfs.push(nextPtr); // 栈顶元素入栈
						}
					}
				}
			}
		}

		return isFindEnd;
	}
	bool dfs3d::next()
	{
		if (!m_sdfs.empty())
		{
			currPos = m_sdfs.top()->data.postion; //移动
			currPtr = m_sdfs.top(); //深入
			m_sdfs.pop(); // 栈顶元素出栈

			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					for (xhqm::size k = 0; k < action_num; ++k)
					{
						state temp1, temp2, next;
						bool canExec = true;
						// 按照规则生成下一个状态 如果状态满足约束条件则入栈
						if (canExec) canExec &= Exec1(temp1, currPtr->data, action[i]);
						if (canExec) canExec &= Exec2(temp2, temp1, action[j]);
						if (canExec) canExec &= Exec2(next, temp2, action[k]);
						if (canExec) canExec &= Check(next);
						if (canExec) {
							currMap[next.postion[0]][next.postion[1]][next.postion[2]] = false; // 访问标记
							next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
							nextPtr = new xhqm::tree<state>(next);
							currPtr->insert(nextPtr); // 记录元素关系
							m_sdfs.push(nextPtr); // 栈顶元素入栈
						}
					}
				}
			}
		}
		return false;
	}
	std::vector<dfs3d::place> dfs3d::path()
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
	void dfs3d::show(place showPos)
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
	bool dfs3d::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]][now.postion[2]];
	}
	bool dfs3d::Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next = curr;
		switch (action)
		{
		case xhqm::rpg::path::actions::forward:
			next.postion[0] = curr.postion[0] + 1;
			if (next.postion[0] >= space_lay) return false;
			break;
		case xhqm::rpg::path::actions::stoped:
			next.postion[0] = curr.postion[0];
			break;
		case xhqm::rpg::path::actions::backward:
			if (curr.postion[0] == 0) return false;
			next.postion[0] = curr.postion[0] - 1;
			break;
		default:
			break;
		}
		return true;
	}
	bool dfs3d::Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next = curr;
		switch (action)
		{
		case xhqm::rpg::path::actions::forward:
			next.postion[1] = curr.postion[1] + 1;
			if (next.postion[1] >= space_row) return false;
			break;
		case xhqm::rpg::path::actions::stoped:
			next.postion[1] = curr.postion[1];
			break;
		case xhqm::rpg::path::actions::backward:
			if (curr.postion[1] == 0) return false;
			next.postion[1] = curr.postion[1] - 1;
			break;
		default:
			break;
		}
		return true;
	}
	bool dfs3d::Exec3(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next = curr;
		switch (action)
		{
		case xhqm::rpg::path::actions::forward:
			next.postion[2] = curr.postion[2] + 1;
			if (next.postion[2] >= space_col) return false;
			break;
		case xhqm::rpg::path::actions::stoped:
			next.postion[2] = curr.postion[2];
			break;
		case xhqm::rpg::path::actions::backward:
			if (curr.postion[2] == 0) return false;
			next.postion[2] = curr.postion[2] - 1;
			break;
		default:
			break;
		}
		return true;
	}



	bfs2d::bfs2d(xhqm::size row, xhqm::size col)
		: space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0 };
		this->goalPos = place{ 0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true));
	}
	bfs2d::~bfs2d()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void bfs2d::init()
	{
		currMap = mazeMap;
		currMap[currPos[0]][currPos[1]] = false;

		xhqm::rpg::path::deleteTree(rootPtr);
		rootPtr = new xhqm::tree<state>(state{ 0, currPos });

		m_qbfs = std::queue<xhqm::tree<state>*>();
		m_qbfs.push(rootPtr);

		goalPtr = nullptr;
	}
	bool bfs2d::walk()
	{
		init();
		bool isFindEnd = false;

		while (!m_qbfs.empty())
		{
			currPtr = m_qbfs.front(); //扩展
			currPos = currPtr->data.postion; //移动
			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					state temp, next;
					bool canExec = true;
					// 按照规则生成下一个状态 如果状态满足约束条件则入队
					if (canExec) canExec &= Exec1(temp, currPtr->data, action[i]);
					if (canExec) canExec &= Exec2(next, temp, action[j]);
					if (canExec) canExec &= Check(next);
					if (canExec) {
						currMap[next.postion[0]][next.postion[1]] = false; // 访问标记
						next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
						nextPtr = new xhqm::tree<state>(next);
						currPtr->insert(nextPtr); // 记录元素关系
						m_qbfs.push(nextPtr); // 队尾元素入队
					}
				}
			}
			m_qbfs.pop(); // 队首元素出队
		}

		return isFindEnd;
	}
	bool bfs2d::next()
	{
		if (!m_qbfs.empty())
		{
			currPtr = m_qbfs.front(); //扩展
			currPos = currPtr->data.postion; //移动
			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					state temp, next;
					bool canExec = true;
					// 按照规则生成下一个状态 如果状态满足约束条件则入队
					if (canExec) canExec &= Exec1(temp, currPtr->data, action[i]);
					if (canExec) canExec &= Exec2(next, temp, action[j]);
					if (canExec) canExec &= Check(next);
					if (canExec) {
						currMap[next.postion[0]][next.postion[1]] = false; // 访问标记
						next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
						nextPtr = new xhqm::tree<state>(next);
						currPtr->insert(nextPtr); // 记录元素关系
						m_qbfs.push(nextPtr); // 队尾元素入队
					}
				}
			}
			m_qbfs.pop(); // 队首元素出队
		}
		return false;
	}
	std::vector<bfs2d::place> bfs2d::path()
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
	void bfs2d::show(place showPos)
	{
		std::cout << "\033c";
		for (xhqm::size i = 0; i < space_row; ++i) {
			for (xhqm::size j = 0; j < space_col; ++j) {
				const place Pos{ i, j };
				if (Pos != showPos && Pos != goalPos)
					std::cout << (mazeMap[i][j] ? "\033[0;37;47m  \033[0m" : "\033[0;31;41m  \033[0m");
				else if (Pos == showPos)
					std::cout << "\033[0;32;42m  \033[0m";
				else if (Pos == goalPos)
					std::cout << "\033[0;34;44m  \033[0m";
			}
			std::cout << i + 1 << std::endl;
		}
	}
	bool bfs2d::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]];
	}
	bool bfs2d::Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next.stepCount = curr.stepCount;
		return xhqm::rpg::path::execAction<2>(0, space_row, next.postion, curr.postion, action);
	}
	bool bfs2d::Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next.stepCount = curr.stepCount;
		return xhqm::rpg::path::execAction<2>(1, space_col, next.postion, curr.postion, action);
	}


	bfs3d::bfs3d(xhqm::size lay, xhqm::size row, xhqm::size col)
		: space_lay(lay), space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0,0 };
		this->goalPos = place{ 0,0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<3>(lay, xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true)));
	}
	bfs3d::~bfs3d()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void bfs3d::init()
	{
		currMap = mazeMap;
		currMap[currPos[0]][currPos[1]][currPos[2]] = false;

		xhqm::rpg::path::deleteTree(rootPtr);
		rootPtr = new xhqm::tree<state>(state{ 0, currPos });

		m_qbfs = std::queue<xhqm::tree<state>*>();
		m_qbfs.push(rootPtr);

		goalPtr = nullptr;
	}
	bool bfs3d::walk()
	{
		init();
		bool isFindEnd = false;

		while (!m_qbfs.empty())
		{
			currPtr = m_qbfs.front(); //扩展
			currPos = currPtr->data.postion; //移动
			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					for (xhqm::size k = 0; k < action_num; ++k)
					{
						state temp1, temp2, next;
						bool canExec = true;
						// 按照规则生成下一个状态 如果状态满足约束条件则入队
						if (canExec) canExec &= Exec1(temp1, currPtr->data, action[i]);
						if (canExec) canExec &= Exec2(temp2, temp1, action[j]);
						if (canExec) canExec &= Exec3(next, temp2, action[k]);
						if (canExec) canExec &= Check(next);
						if (canExec) {
							currMap[next.postion[0]][next.postion[1]][next.postion[2]] = false; // 访问标记
							next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
							nextPtr = new xhqm::tree<state>(next);
							currPtr->insert(nextPtr); // 记录元素关系
							m_qbfs.push(nextPtr); // 队尾元素入队
						}
					}
				}
			}
			m_qbfs.pop(); // 队首元素出队
		}

		return isFindEnd;
	}
	bool bfs3d::next()
	{
		if (!m_qbfs.empty())
		{
			currPtr = m_qbfs.front(); //扩展
			currPos = currPtr->data.postion; //移动
			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			for (xhqm::size i = 0; i < action_num; ++i)
			{
				for (xhqm::size j = 0; j < action_num; ++j)
				{
					for (xhqm::size k = 0; k < action_num; ++k)
					{
						state temp1, temp2, next;
						bool canExec = true;
						// 按照规则生成下一个状态 如果状态满足约束条件则入队
						if (canExec) canExec &= Exec1(temp1, currPtr->data, action[i]);
						if (canExec) canExec &= Exec2(temp2, temp1, action[j]);
						if (canExec) canExec &= Exec3(next, temp2, action[k]);
						if (canExec) canExec &= Check(next);
						if (canExec) {
							currMap[next.postion[0]][next.postion[1]][next.postion[2]] = false; // 访问标记
							next.stepCount = currPtr->data.stepCount + 1; // 计数器加1
							nextPtr = new xhqm::tree<state>(next);
							currPtr->insert(nextPtr); // 记录元素关系
							m_qbfs.push(nextPtr); // 队尾元素入队
						}
					}
				}
			}
			m_qbfs.pop(); // 队首元素出队
		}
		return false;
	}
	std::vector<bfs3d::place> bfs3d::path()
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
	void bfs3d::show(place showPos)
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
	bool bfs3d::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]][now.postion[2]];
	}
	bool bfs3d::Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next.stepCount = curr.stepCount;
		return xhqm::rpg::path::execAction<3>(0, space_lay, next.postion, curr.postion, action);
	}
	bool bfs3d::Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next.stepCount = curr.stepCount;
		return xhqm::rpg::path::execAction<3>(1, space_row, next.postion, curr.postion, action);
	}
	bool bfs3d::Exec3(state& next, const state& curr, const xhqm::rpg::path::actions& action)
	{
		next.stepCount = curr.stepCount;
		return xhqm::rpg::path::execAction<3>(2, space_col, next.postion, curr.postion, action);
	}



	gbfs2d::gbfs2d(xhqm::size row, xhqm::size col)
		: space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0 };
		this->goalPos = place{ 0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true));

		////曼哈顿距离
		//greedy([this](const state& node) {
		//	xhqm::size len10 = xhqm_abs(node.postion[0], goalPos[0]);
		//	xhqm::size len11 = xhqm_abs(node.postion[1], goalPos[1]);
		//	return static_cast<xhqm::measure>(len10 + len11);
		//	});
		//欧氏距离
		greedy([this](const state& node) {
			xhqm::size len10 = xhqm_abs(node.postion[0], goalPos[0]);
			xhqm::size len11 = xhqm_abs(node.postion[1], goalPos[1]);
			return static_cast<xhqm::measure>(len10 * len10 + len11 * len11);
			});
	}
	gbfs2d::~gbfs2d()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void gbfs2d::init()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
		nextPtr = new xhqm::tree<state>(state{ 0, currPos });
		rootPtr = new xhqm::tree<state>();
		rootPtr->insert(nextPtr);
		currPtr = rootPtr;
		goalPtr = nullptr;
		currMap = mazeMap;
	}
	bool gbfs2d::walk()
	{
		init();
		bool isFindEnd = false;

		while (!currPtr->empty())
		{
			//按照成本排序，获取最小成本
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price < second->data.price);
				});

			//将已走过的点移到最后方
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* node)
				{
					return !(Check(node->data));
				});

			//移动 //可能会进入死胡同
			nextPtr = currPtr->child(0);
			if (Check(nextPtr->data))
				currPtr = nextPtr;
			else //死胡同
				break;

			//标记
			currPos = currPtr->data.postion;
			currMap[currPos[0]][currPos[1]] = false;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}

			state next; // 按照规则生成下一个状态 如果状态满足约束条件则入树
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					if (Exec(next, currPtr->data, { action[i], action[j] })) 
						currPtr->insert(new xhqm::tree<state>(next));
		}

		return isFindEnd;
	}
	bool gbfs2d::next()
	{
		if (!currPtr->empty())
		{
			//按照成本排序，获取最小成本
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price < second->data.price);
				});

			//将已走过的点移到最后方
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* node)
				{
					return !(Check(node->data));
				});

			//移动 //可能会进入死胡同
			nextPtr = currPtr->child(0);
			if (Check(nextPtr->data))
				currPtr = nextPtr;
			else //死胡同
				return false;

			//标记
			currPos = currPtr->data.postion;
			currMap[currPos[0]][currPos[1]] = false;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			state next; // 按照规则生成下一个状态 如果状态满足约束条件则入树
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					if (Exec(next, currPtr->data, { action[i], action[j] }))
						currPtr->insert(new xhqm::tree<state>(next));
		}
		return false;
	}
	std::vector<gbfs2d::place> gbfs2d::path()
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
	void gbfs2d::show(place showPos)
	{
		std::cout << "\033c";
		for (xhqm::size i = 0; i < space_row; ++i) {
			for (xhqm::size j = 0; j < space_col; ++j) {
				const place Pos{ i, j };
				if (Pos != showPos && Pos != goalPos)
					std::cout << (mazeMap[i][j] ? "\033[0;37;47m  \033[0m" : "\033[0;31;41m  \033[0m");
				else if (Pos == showPos)
					std::cout << "\033[0;32;42m  \033[0m";
				else if (Pos == goalPos)
					std::cout << "\033[0;34;44m  \033[0m";
			}
			std::cout << i + 1 << std::endl;
		}
	}
	bool gbfs2d::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]];
	}
	bool gbfs2d::Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions)
	{
		bool exec = true; state temp;
		//获取新位置
		if (exec) exec &= xhqm::rpg::path::execAction<2>(0, space_row, temp.postion, curr.postion, actions[0]);
		if (exec) exec &= xhqm::rpg::path::execAction<2>(1, space_col, next.postion, temp.postion, actions[1]);
		if (exec) exec &= currMap[next.postion[0]][next.postion[1]];
		//计算成本
		if (exec) next.price = funGreedy(next);
		return exec;
	}


	gbfs3d::gbfs3d(xhqm::size lay, xhqm::size row, xhqm::size col)
		: space_lay(lay), space_row(row), space_col(col)
	{
		this->currPos = place{ 0,0,0 };
		this->goalPos = place{ 0,0,0 };
		this->rootPtr = new xhqm::tree<state>();
		this->mazeMap = xhqm::rpg::path::space_dis<3>(lay, xhqm::rpg::path::space_dis<2>(row, xhqm::rpg::path::space_dis<1>(col, true)));

		//曼哈顿距离
		greedy([this](const state& node) {
			xhqm::size len10 = xhqm_abs(node.postion[0], goalPos[0]);
			xhqm::size len11 = xhqm_abs(node.postion[1], goalPos[1]);
			xhqm::size len12 = xhqm_abs(node.postion[2], goalPos[2]);
			return static_cast<xhqm::measure>(len10 + len11 + len12);
			});
		//欧氏距离
		greedy([this](const state& node) {
			xhqm::size len10 = xhqm_abs(node.postion[0], goalPos[0]);
			xhqm::size len11 = xhqm_abs(node.postion[1], goalPos[1]);
			xhqm::size len12 = xhqm_abs(node.postion[2], goalPos[2]);
			return static_cast<xhqm::measure>(len10 * len10 + len11 * len11 + len12 * len12);
			});
	}
	gbfs3d::~gbfs3d()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
	}
	void gbfs3d::init()
	{
		xhqm::rpg::path::deleteTree(rootPtr);
		nextPtr = new xhqm::tree<state>(state{ 0, currPos });
		rootPtr = new xhqm::tree<state>();
		rootPtr->insert(nextPtr);
		currPtr = rootPtr;
		goalPtr = nullptr;
		currMap = mazeMap;
	}
	bool gbfs3d::walk()
	{
		init();
		bool isFindEnd = false;

		while (!currPtr->empty())
		{
			//按照成本排序，获取最小成本
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price < second->data.price);
				});

			//将已走过的点移到最后方
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* node)
				{
					return !(Check(node->data));
				});

			//移动 //可能会进入死胡同
			nextPtr = currPtr->child(0);
			if (Check(nextPtr->data))
				currPtr = nextPtr;
			else //死胡同
				break;

			//标记
			currPos = currPtr->data.postion;
			currMap[currPos[0]][currPos[1]][currPos[2]] = false;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				isFindEnd = true;
				break;
			}

			state next; // 按照规则生成下一个状态 如果状态满足约束条件则入树
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					for (xhqm::size k = 0; k < action_num; ++k)
						if (Exec(next, currPtr->data, { action[i], action[j], action[k] }))
							currPtr->insert(new xhqm::tree<state>(next));
		}

		return isFindEnd;
	}
	bool gbfs3d::next()
	{
		if (!currPtr->empty())
		{
			//按照成本排序，获取最小成本
			std::sort(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* first, xhqm::tree<state>* second)
				{
					return (first->data.price < second->data.price);
				});

			//将已走过的点移到最后方
			std::remove_if(currPtr->begin(), currPtr->end(), [this](xhqm::tree<state>* node)
				{
					return !(Check(node->data));
				});

			//移动 //可能会进入死胡同
			nextPtr = currPtr->child(0);
			if (Check(nextPtr->data))
				currPtr = nextPtr;
			else //死胡同
				return false;

			//标记
			currPos = currPtr->data.postion;
			currMap[currPos[0]][currPos[1]][currPos[2]] = false;
			if (currPos == goalPos) {
				goalPtr = currPtr;
				return true;
			}

			state next; // 按照规则生成下一个状态 如果状态满足约束条件则入树
			for (xhqm::size i = 0; i < action_num; ++i)
				for (xhqm::size j = 0; j < action_num; ++j)
					for (xhqm::size k = 0; k < action_num; ++k)
						if (Exec(next, currPtr->data, { action[i], action[j], action[k] }))
							currPtr->insert(new xhqm::tree<state>(next));
		}
		return false;
	}
	std::vector<gbfs3d::place> gbfs3d::path()
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
	void gbfs3d::show(place showPos)
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
	bool gbfs3d::Check(const state& now)
	{
		return currMap[now.postion[0]][now.postion[1]][now.postion[2]];
	}
	bool gbfs3d::Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions)
	{
		bool exec = true; state temp1, temp2;
		//获取新位置
		if (exec) exec &= xhqm::rpg::path::execAction<3>(0, space_lay, temp1.postion, curr.postion, actions[0]);
		if (exec) exec &= xhqm::rpg::path::execAction<3>(1, space_row, temp2.postion, temp1.postion, actions[1]);
		if (exec) exec &= xhqm::rpg::path::execAction<3>(2, space_col, next.postion, temp2.postion, actions[3]);
		if (exec) exec &= currMap[next.postion[0]][next.postion[1]][next.postion[2]];
		//计算成本
		if (exec) next.price = funGreedy(next);
		return exec;
	}
}