#ifndef XHQM_RPGPATHFINDING
#define XHQM_RPGPATHFINDING
#include "rpg_game.h"

namespace xhqm::rpg::path
{
	template<xhqm::size dim>
	using place_dis = xhqm::hyper<xhqm::size, dim>;

	template<xhqm::size dim>
	using space_dis = xhqm::docker<bool, dim>;

	enum actions
	{
		forward, stoped, backward
	};

	struct algorithm
	{
		constexpr static xhqm::size action_num = 3;
		const actions action[action_num] = { forward, stoped, backward };
		virtual void init() = 0;//初始化开始状态
		virtual bool walk() = 0;//true成功找到路径
		virtual bool next() = 0;//true成功找到终点
	};

	template<xhqm::size dim>
	bool execAction(xhqm::size d, xhqm::size space_limt, place_dis<dim>& next, const place_dis<dim>& curr, const xhqm::rpg::path::actions& action)
	{
		next = curr;
		switch (action)
		{
		case xhqm::rpg::path::actions::forward:
			next[d] = curr[d] + 1;
			if (next[d] >= space_limt) return false;
			break;
		case xhqm::rpg::path::actions::stoped:
			next[d] = curr[d];
			break;
		case xhqm::rpg::path::actions::backward:
			if (curr[d] == 0) return false;
			next[d] = curr[d] - 1;
			break;
		default:
			break;
		}
		return true;
	}

	template<class treeType>
	void deleteTree(treeType* root)
	{
		xhqm::forNode(root, [](treeType* node) { delete node; });
	}
}

#endif