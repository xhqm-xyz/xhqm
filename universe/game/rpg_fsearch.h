#ifndef XHQM_RPGFIRSTSEARCH
#define XHQM_RPGFIRSTSEARCH
#include "rpg_path.h"
#include <queue>
#include <stack>


namespace xhqm::rpg
{
	//�������Ѱ·
	//�����㷨��֧�ֶ�̬Ŀ��
	//����·�������·��
	struct dfs : public xhqm::rpg::path::algorithm { };

	class dfs2d : public dfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //����������
			xhqm::rpg::path::place_dis<2> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<2>;
		using space = xhqm::rpg::path::space_dis<2>;
	protected:
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//�Թ���ͼ true ����
		space currMap = {};//ʵʱ�Թ� true ����
		place starPos = {};//��ʼλ��
		place currPos = {};//ʵʱλ��
		place goalPos = {};//Ŀ��λ��

		std::stack<xhqm::tree<state>*> m_sdfs; // DFS ջ
		xhqm::tree<state>* rootPtr = nullptr;//·����
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
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};

	class dfs3d : public dfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //����������
			xhqm::rpg::path::place_dis<3> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
	protected:
		const xhqm::size space_lay = 0;
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//�Թ���ͼ true ����
		space currMap = {};//ʵʱ�Թ� true ����
		place starPos = {};//��ʼλ��
		place currPos = {};//ʵʱλ��
		place goalPos = {};//Ŀ��λ��

		std::stack<xhqm::tree<state>*> m_sdfs; // DFS ջ
		xhqm::tree<state>* rootPtr = nullptr;//·����
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
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec3(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};


	//�������Ѱ·
	//�����㷨��֧�ֶ�̬Ŀ��
	//����·��Ϊ���·��
	//���ǲ�����·��
	struct bfs : public xhqm::rpg::path::algorithm { };

	class bfs2d : public bfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //����������
			xhqm::rpg::path::place_dis<2> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<2>;
		using space = xhqm::rpg::path::space_dis<2>;
	protected:
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//�Թ���ͼ true ����
		space currMap = {};//ʵʱ�Թ� true ����
		place starPos = {};//��ʼλ��
		place currPos = {};//ʵʱλ��
		place goalPos = {};//Ŀ��λ��

		std::queue<xhqm::tree<state>*> m_qbfs; // BFS ��
		xhqm::tree<state>* rootPtr = nullptr;//·����
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
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};

	class bfs3d : public bfs
	{
	public:
		struct state
		{
			xhqm::size stepCount = 0; //����������
			xhqm::rpg::path::place_dis<3> postion{0, 0, 0};
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
	protected:
		const xhqm::size space_lay = 0;
		const xhqm::size space_row = 0;
		const xhqm::size space_col = 0;

		space mazeMap = {};//�Թ���ͼ true ����
		space currMap = {};//ʵʱ�Թ� true ����
		place starPos = {};//��ʼλ��
		place currPos = {};//ʵʱλ��
		place goalPos = {};//Ŀ��λ��

		std::queue<xhqm::tree<state>*> m_qbfs; // BFS ��
		xhqm::tree<state>* rootPtr = nullptr;//·����
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
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec1(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec2(state& next, const state& curr, const xhqm::rpg::path::actions& action);
		virtual bool Exec3(state& next, const state& curr, const xhqm::rpg::path::actions& action);
	};

	//����ʽ�������Ѱ·
	//�����㷨�Ǳ���ʽ�㷨
	//���޸�Ϊ��̬Ŀ��
	//����·��δ��Ϊ���·��
	//Ĭ����������Ϊ�����پ���
	//���޸�Ϊŷ�Ͼ���
	struct gbfs : public xhqm::rpg::path::algorithm { };

	class gbfs2d : public xhqm::rpg::gbfs
	{
	public:
		struct state
		{
			xhqm::measure price = 0.0; //�ɱ�
			xhqm::rpg::path::place_dis<2> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<2>;
		using space = xhqm::rpg::path::space_dis<2>;
		using function = std::function<xhqm::measure(const state&)>;
	protected:
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

		function funGreedy = nullptr; //����ʽ����
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
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions);
	};

	class gbfs3d : public xhqm::rpg::gbfs
	{
	public:
		struct state
		{
			xhqm::measure price = 0.0; //�ɱ�
			xhqm::rpg::path::place_dis<3> postion{0, 0};
		};
		using place = xhqm::rpg::path::place_dis<3>;
		using space = xhqm::rpg::path::space_dis<3>;
		using function = std::function<xhqm::measure(const state&)>;
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

		function funGreedy = nullptr; //����ʽ����
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
		virtual bool Check(const state& now); // Լ����������
		virtual bool Exec(state& next, const state& curr, const std::vector<xhqm::rpg::path::actions>& actions);
	};
}

#endif