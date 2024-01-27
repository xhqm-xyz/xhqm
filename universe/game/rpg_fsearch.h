#ifndef XHQM_RPGFIRSTSEARCH
#define XHQM_RPGFIRSTSEARCH
#include "rpg_path.h"
#include <queue>
#include <stack>


namespace xhqm::rpg
{
	//深度优先寻路
	//此类算法不支持动态目标
	//搜索路径非最短路径
	struct dfs : public xhqm::rpg::path::algorithm { };

	class dfs2d : public dfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //步数计数器
			xhqm::rpg::path::place_dis<2> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<2>;
		using space = xhqm::rpg::path::space_dis<2>;
	protected:
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//迷宫地图 true 可走
		space currMap = {};//实时迷宫 true 可走
		place starPos = {};//开始位置
		place currPos = {};//实时位置
		place goalPos = {};//目标位置

		std::stack<xhqm::tree<state>*> m_sdfs; // DFS 栈
		xhqm::tree<state>* rootPtr = nullptr;//路径树
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;
	public:
		dfs2d(xhqm::size row, xhqm::size col);
		virtual ~dfs2d();

		inline void walk(xhqm::size x, xhqm::size y, bool val) { mazeMap[x][y] = val; };
		inline bool walk(xhqm::size x, xhqm::size y) const { return mazeMap[x][y]; };

		inline void star(place pos) { starPos = pos; currPos = pos; };
		inline void stop(place pos) { goalPos = pos; };
		inline place star() const { return starPos; };
		inline place curr() const { return currPos; };
		inline place stop() const { return goalPos; };

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;

		std::vector<place> path();
		void show(place showPos);
	protected:
		virtual bool Check(const state& now); // 约束条件检验
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};

	class dfs3d : public dfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //步数计数器
			xhqm::rpg::path::place_dis<3> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
	protected:
		const xhqm::size space_lay = 0;
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//迷宫地图 true 可走
		space currMap = {};//实时迷宫 true 可走
		place starPos = {};//开始位置
		place currPos = {};//实时位置
		place goalPos = {};//目标位置

		std::stack<xhqm::tree<state>*> m_sdfs; // DFS 栈
		xhqm::tree<state>* rootPtr = nullptr;//路径树
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;
	public:
		dfs3d(xhqm::size lay, xhqm::size row, xhqm::size col);
		virtual ~dfs3d();

		inline void walk(xhqm::size x, xhqm::size y, xhqm::size z, bool val) { mazeMap[x][y][z] = val; };
		inline bool walk(xhqm::size x, xhqm::size y, xhqm::size z) const { return mazeMap[x][y][z]; };

		inline void star(place pos) { starPos = pos; currPos = pos; };
		inline void stop(place pos) { goalPos = pos; };
		inline place star() const { return starPos; };
		inline place curr() const { return currPos; };
		inline place stop() const { return goalPos; };

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;

		std::vector<place> path();
		void show(place showPos);
	protected:
		virtual bool Check(const state& now); // 约束条件检验
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec3(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};


	//广度优先寻路
	//此类算法不支持动态目标
	//搜索路径为最短路径
	//除非不存在路径
	struct bfs : public xhqm::rpg::path::algorithm { };

	class bfs2d : public bfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //步数计数器
			xhqm::rpg::path::place_dis<2> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<2>;
		using space = xhqm::rpg::path::space_dis<2>;
	protected:
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//迷宫地图 true 可走
		space currMap = {};//实时迷宫 true 可走
		place starPos = {};//开始位置
		place currPos = {};//实时位置
		place goalPos = {};//目标位置

		std::queue<xhqm::tree<state>*> m_qbfs; // BFS 队
		xhqm::tree<state>* rootPtr = nullptr;//路径树
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;
	public:
		bfs2d(xhqm::size row, xhqm::size col);
		virtual ~bfs2d();

		inline void walk(xhqm::size x, xhqm::size y, bool val) { mazeMap[x][y] = val; };
		inline bool walk(xhqm::size x, xhqm::size y) const { return mazeMap[x][y]; };

		inline void star(place pos) { starPos = pos; currPos = pos; };
		inline void stop(place pos) { goalPos = pos; };
		inline place star() const { return starPos; };
		inline place curr() const { return currPos; };
		inline place stop() const { return goalPos; };

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;

		std::vector<place> path();
		void show(place showPos);
	protected:
		virtual bool Check(const state& now); // 约束条件检验
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};

	class bfs3d : public bfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //步数计数器
			xhqm::rpg::path::place_dis<3> postion{0, 0, 0};
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
	protected:
		const xhqm::size space_lay = 0;
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//迷宫地图 true 可走
		space currMap = {};//实时迷宫 true 可走
		place starPos = {};//开始位置
		place currPos = {};//实时位置
		place goalPos = {};//目标位置

		std::queue<xhqm::tree<state>*> m_qbfs; // BFS 队
		xhqm::tree<state>* rootPtr = nullptr;//路径树
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;
	public:
		bfs3d(xhqm::size lay, xhqm::size row, xhqm::size col);
		virtual ~bfs3d();

		inline void walk(xhqm::size x, xhqm::size y, xhqm::size z, bool val) { mazeMap[x][y][z] = val; };
		inline bool walk(xhqm::size x, xhqm::size y, xhqm::size z) const { return mazeMap[x][y][z]; };

		inline void star(place pos) { starPos = pos; currPos = pos; };
		inline void stop(place pos) { goalPos = pos; };
		inline place star() const { return starPos; };
		inline place curr() const { return currPos; };
		inline place stop() const { return goalPos; };

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;

		std::vector<place> path();
		void show(place showPos);
	protected:
		virtual bool Check(const state& now); // 约束条件检验
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec3(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};

	//启发式广度优先寻路
	//此类算法非遍历式算法
	//可修改为动态目标
	//搜索路径未必为最短路径
	//默认启发函数为曼哈顿距离
	//可修改为欧氏距离
	struct gbfs : public xhqm::rpg::path::algorithm { };

	class gbfs2d : public xhqm::rpg::gbfs
	{
	public:
		struct state
		{
			xhqm::measure price = 0.0; //成本
			xhqm::rpg::path::place_dis<2> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<2>;
		using space = xhqm::rpg::path::space_dis<2>;
		using function = std::function<xhqm::measure(const state&)>;
	protected:
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//迷宫地图 true 可走
		space currMap = {};//实时迷宫 true 可走
		place starPos = {};//开始位置
		place currPos = {};//实时位置
		place goalPos = {};//目标位置

		xhqm::tree<state>* rootPtr = nullptr;//路径树
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;

		function funGreedy = nullptr; //启发式函数
	public:
		gbfs2d(xhqm::size row, xhqm::size col);
		virtual ~gbfs2d();

		inline void greedy(function fun) { funGreedy = fun; }
		inline void walk(xhqm::size x, xhqm::size y, bool val) { mazeMap[x][y] = val; };
		inline bool walk(xhqm::size x, xhqm::size y) const { return mazeMap[x][y]; };

		inline void star(place pos) { starPos = pos; currPos = pos; };
		inline void stop(place pos) { goalPos = pos; };
		inline place star() const { return starPos; };
		inline place curr() const { return currPos; };
		inline place stop() const { return goalPos; };

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;

		std::vector<place> path();
		void show(place showPos);
	protected:
		virtual bool Check(const state& now); // 约束条件检验
		virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions);
	};

	class gbfs3d : public xhqm::rpg::gbfs
	{
	public:
		struct state
		{
			xhqm::measure price = 0.0; //成本
			xhqm::rpg::path::place_dis<3> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
		using function = std::function<xhqm::measure(const state&)>;
	protected:
		const xhqm::size space_lay = 0;
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//迷宫地图 true 可走
		space currMap = {};//实时迷宫 true 可走
		place starPos = {};//开始位置
		place currPos = {};//实时位置
		place goalPos = {};//目标位置

		xhqm::tree<state>* rootPtr = nullptr;//路径树
		xhqm::tree<state>* currPtr = nullptr;
		xhqm::tree<state>* nextPtr = nullptr;
		xhqm::tree<state>* goalPtr = nullptr;

		function funGreedy = nullptr; //启发式函数
	public:
		gbfs3d(xhqm::size lay, xhqm::size row, xhqm::size col);
		virtual ~gbfs3d();

		inline void greedy(function fun) { funGreedy = fun; }
		inline void walk(xhqm::size x, xhqm::size y, xhqm::size z, bool val) { mazeMap[x][y][z] = val; };
		inline bool walk(xhqm::size x, xhqm::size y, xhqm::size z) const { return mazeMap[x][y][z]; };

		inline void star(place pos) { starPos = pos; currPos = pos; };
		inline void stop(place pos) { goalPos = pos; };
		inline place star() const { return starPos; };
		inline place curr() const { return currPos; };
		inline place stop() const { return goalPos; };

		virtual void init() override;
		virtual bool walk() override;
		virtual bool next() override;

		std::vector<place> path();
		void show(place showPos);
	protected:
		virtual bool Check(const state& now); // 约束条件检验
		virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions);
	};
}

#endif