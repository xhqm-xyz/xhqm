#pragma once
#ifndef XHQM_MATH_TREE
#define XHQM_MATH_TREE
#include "../head.h"
#include "../metaclass/template.h"

namespace xhqm
{
	//节点
	template<class type>
	struct node
	{
		type data;
		xhqm::string name;

		inline node(const type& data = type(), const xhqm::string& name = "")
		{
			this->data = data;
			this->name = name;
		}

		constexpr type& dataref() { return data; }
		constexpr const type& dataref() const { return data; }
		constexpr type* dataptr() { return &data; }
		constexpr const type* dataptr() const { return &data; }

		constexpr operator type& () { return this->data; }
		constexpr operator const type&() const { return this->data; }
	};



	//网
	template<class type, class meshType, template<class> class dockerType, class pathData>
	struct _mesh : public xhqm::node<type>
	{
		using meshPtr = meshType*;
		using meshRef = meshType&;
		using otherPtrs = dockerType<std::pair<meshPtr, pathData>>;
		using iterator = typename otherPtrs::iterator;
	protected:
		otherPtrs m_others;
	public:
		_mesh(const node<type>& node) :xhqm::node<type>(node.data, node.name) {};
		_mesh(const type& data = type(), xhqm::string name = "") :xhqm::node<type>(data, name) {};

		iterator begin() {
			return m_others.begin();
		}

		const iterator begin() const {
			return m_others.begin();
		}

		iterator end() {
			return m_others.end();
		}

		const iterator end() const {
			return m_others.end();
		}

		constexpr bool empty() const noexcept {
			return m_others.empty();
		}

		constexpr xhqm::size size() const noexcept {
			return m_others.size();
		}

		constexpr std::pair<meshPtr, pathData>& path(const xhqm::size& _Pos) {
			return m_others[_Pos];
		}

		constexpr const std::pair<meshPtr, pathData>& path(const xhqm::size& _Pos) const {
			return m_others[_Pos];
		}

		xhqm::size index(meshPtr ptr)
		{
			xhqm::size ind = 0;
			for (auto& child : m_others)
			{
				if ((child.first != ptr) || ptr == nullptr) ++ind;
				else return ind;
			}
			return ind;
		}

		bool notnull()
		{
			for (auto& child : m_others)
				if (child.first == nullptr) return false;
			return true;
		}

		bool inmesh(meshPtr ptr)
		{
			if (!ptr) return false;
			for (auto& child : m_others)
				if (child.first == ptr) return true;
			return false;
		}
	};

	template<class type, class meshType, template<class> class dockerType>
	struct _mesh<type, meshType, dockerType, void> : public xhqm::node<type>
	{
		using meshPtr = meshType*;
		using meshRef = meshType&;
		using otherPtrs = dockerType<meshPtr>;
		using iterator = typename otherPtrs::iterator;
	protected:
		otherPtrs m_others;
	public:
		_mesh(const node<type>& node) :xhqm::node<type>(node.data, node.name) {};
		_mesh(const type& data = type(), xhqm::string name = "") :xhqm::node<type>(data, name) {};

		iterator begin() {
			return m_others.begin();
		}

		const iterator begin() const {
			return m_others.begin();
		}

		iterator end() {
			return m_others.end();
		}

		const iterator end() const {
			return m_others.end();
		}

		constexpr bool empty() const noexcept {
			return m_others.empty();
		}

		constexpr xhqm::size size() const noexcept {
			return m_others.size();
		}

		constexpr meshPtr& operator[](const xhqm::size& _Pos) {
			return m_others[_Pos];
		}

		constexpr const meshPtr& operator[](const xhqm::size& _Pos) const {
			return m_others[_Pos];
		}

		xhqm::size index(meshPtr ptr)
		{
			xhqm::size ind = 0;
			for (auto& child : m_others)
			{
				if ((child != ptr) || ptr == nullptr) ++ind;
				else return ind;
			}
			return ind;
		}

		bool notnull()
		{
			for (auto& child : m_others)
				if (child == nullptr) return false;
			return true;
		}

		bool inmesh(meshPtr ptr)
		{
			if (!ptr) return false;
			for (auto& child : m_others)
				if (child == ptr) return true;
			return false;
		}
	};

	template<xhqm::size _N> struct fork_mesh_s
	{
		template <class type> using dockerType = std::array<type, _N>;
	};
	template<typename type, xhqm::size _N>
    class fork_mesh : public _mesh<type, fork_mesh<type, _N>, fork_mesh_s<_N>::template dockerType, void>
	{
	public:
        using _fork_mesh = _mesh<type, fork_mesh<type, _N>, fork_mesh_s<_N>::template dockerType, void>;
		using iterator = typename _fork_mesh::iterator;
		fork_mesh(const node<type>& node) : _fork_mesh(node) {
			this->m_others.fill(nullptr);
		}
		fork_mesh(const type& value = type()) : _fork_mesh(value) {
			this->m_others.fill(nullptr);
		}

		bool insert(fork_mesh* ptr)
		{
			if (ptr == this) return false;
			if (this->index(ptr) == this->size() && ptr)
			{
				if (this->notnull() || ptr->notnull())
					return false;//已满
				for (auto& child : this->m_others)
				{
					if (child == nullptr)
					{
						child = ptr;
						break;
					}
				}
				for (auto& child : ptr->m_others)
				{
					if (child == nullptr)
					{
						child = this;
						break;
					}
				}
				return true;
			}
			return false;//已存在或nullptr
		}
		fork_mesh* remove(const xhqm::size& pos)
		{
			fork_mesh* ptr = this->m_others[pos];
			xhqm::size ind = ptr->index(this);
			this->m_others[pos] = nullptr;
			ptr->m_others[ind] = nullptr;
			return ptr;
		}
	};

    template<typename type, class pathData = void, template<class> class dockerType = std::vector>
	class singly_mesh : public _mesh<type, singly_mesh<type, pathData, dockerType>, dockerType, pathData>
	{
	public:
		using _singly_mesh = _mesh<type, singly_mesh<type, pathData, dockerType>, dockerType, pathData>;
		using iterator = typename _singly_mesh::iterator;
		singly_mesh(const node<type>& node) : _singly_mesh(node) {}
		singly_mesh(const type& value = type()) : _singly_mesh(value) {}

		bool insert(singly_mesh* ptr, const pathData& data = pathData())
		{
			if (ptr == this) return false;
			if (this->index(ptr) == this->size() && ptr)
			{
				this->m_others.push_back({ ptr, data });
				return true;
			}
			return false;//已存在或nullptr
		}

		void remove(singly_mesh* ptr)
		{
			if (this->size())
				this->m_others.erase(this->m_others.begin() + this->index(ptr));
		}
	};

	template<typename type, template<class> class dockerType>
	class singly_mesh<type, void, dockerType> : public _mesh<type, singly_mesh<type, void, dockerType>, dockerType, void>
	{
	public:
		using _singly_mesh = _mesh<type, singly_mesh<type, void, dockerType>, dockerType, void>;
		using iterator = typename _singly_mesh::iterator;
		singly_mesh(const node<type>& node) : _singly_mesh(node) {}
		singly_mesh(const type& value = type()) : _singly_mesh(value) {}

		bool insert(singly_mesh* ptr)
		{
			if (ptr == this) return false;
			if (this->index(ptr) == this->size() && ptr)
			{
				this->m_others.push_back(ptr);
				return true;
			}
			return false;//已存在或nullptr
		}

		void remove(singly_mesh* ptr)
		{
			if (this->size())
				this->m_others.erase(this->m_others.begin() + this->index(ptr));
		}
	};

    template<typename type, class pathData = void, template<class> class dockerType = xtd::vector>
	class doubly_mesh : public _mesh<type, doubly_mesh<type, pathData, dockerType>, dockerType, pathData>
	{
	public:
		using _doubly_mesh = _mesh<type, doubly_mesh<type, pathData, dockerType>, dockerType, pathData>;
		using iterator = typename _doubly_mesh::iterator;
		doubly_mesh(const node<type>& node) : _doubly_mesh(node) {}
		doubly_mesh(const type& value = type()) : _doubly_mesh(value) {}

		bool insert(doubly_mesh* ptr, const pathData& data = pathData())
		{
			if (ptr == this) return false;
			if (this->index(ptr) == this->size() && ptr)
			{
				this->m_others.push_back({ ptr, data });
				ptr->m_others.push_back({ this, data });
				return true;
			}
			return false;//已存在或nullptr
		}
		void remove(doubly_mesh* ptr)
		{
			if (this->size() && ptr->size()) 
			{
				xhqm::size ind = ptr->index(this);
				xhqm::size pos = this->index(ptr);
				ptr->m_others.erase(ptr->m_others.begin() + ind);
				this->m_others.erase(this->m_others.begin() + pos);
			}
		}
	};

	template<typename type, template<class> class dockerType>
	class doubly_mesh<type, void, dockerType> : public _mesh<type, doubly_mesh<type, void, dockerType>, dockerType, void>
	{
	public:
		using _doubly_mesh = _mesh<type, doubly_mesh<type, void, dockerType>, dockerType, void>;
		using iterator = typename _doubly_mesh::iterator;
		doubly_mesh(const node<type>& node) : _doubly_mesh(node) {}
		doubly_mesh(const type& value = type()) : _doubly_mesh(value) {}

		bool insert(doubly_mesh* ptr)
		{
			if (ptr == this) return false;
			if (this->index(ptr) == this->size() && ptr)
			{
				this->m_others.push_back(ptr);
				ptr->m_others.push_back(this);
				return true;
			}
			return false;//已存在或nullptr
		}
		void remove(doubly_mesh* ptr)
		{
			if (this->size() && ptr->size())
			{
				xhqm::size ind = ptr->index(this);
				xhqm::size pos = this->index(ptr);
				ptr->m_others.erase(ptr->m_others.begin() + ind);
				this->m_others.erase(this->m_others.begin() + pos);
			}
		}
	};


	template<typename type, class pathData>
    class singly_mesh<type, pathData, xtd::list> : public _mesh<type, singly_mesh<type, pathData, xtd::list>, xtd::list, pathData>
	{
	public:
        using _singly_mesh = _mesh<type, singly_mesh<type, pathData, xtd::list>, xtd::list, pathData>;
		using iterator = typename _singly_mesh::iterator;
		singly_mesh(const node<type>& node) : _singly_mesh(node) {}
		singly_mesh(const type& value = type()) : _singly_mesh(value) {}

		//bool insert(singly_mesh* ptr, const pathData& data = pathData())
		//{
		//	if (this->index(ptr) == this->size() && ptr)
		//	{
		//		this->m_others.push_back({ ptr, data });
		//		return true;
		//	}
		//	return false;//已存在或nullptr
		//}

		//void remove(singly_mesh* ptr)
		//{
		//	this->m_others.erase(this->m_others.begin() + this->index(ptr));
		//}
	};

	template<typename type>
    class singly_mesh<type, void, xtd::list> : public _mesh<type, singly_mesh<type, void, xtd::list>, xtd::list, void>
	{
	public:
        using _singly_mesh = _mesh<type, singly_mesh<type, void, xtd::list>, xtd::list, void>;
		using iterator = typename _singly_mesh::iterator;
		singly_mesh(const node<type>& node) : _singly_mesh(node) {}
		singly_mesh(const type& value = type()) : _singly_mesh(value) {}

		//bool insert(singly_mesh* ptr)
		//{
		//	if (this->index(ptr) == this->size() && ptr)
		//	{
		//		this->m_others.push_back(ptr);
		//		return true;
		//	}
		//	return false;//已存在或nullptr
		//}

		//void remove(singly_mesh* ptr)
		//{
		//	this->m_others.erase(this->m_others.begin() + this->index(ptr));
		//}
	};

	template<typename type, class pathData>
    class doubly_mesh<type, pathData, xtd::list> : public _mesh<type, doubly_mesh<type, pathData, xtd::list>, xtd::list, pathData>
	{
	public:
        using _doubly_mesh = _mesh<type, doubly_mesh<type, pathData, xtd::list>, xtd::list, pathData>;
		using iterator = typename _doubly_mesh::iterator;
		doubly_mesh(const node<type>& node) : _doubly_mesh(node) {}
		doubly_mesh(const type& value = type()) : _doubly_mesh(value) {}

		//bool insert(doubly_mesh* ptr, const pathData& data = pathData())
		//{
		//	if (this->index(ptr) == this->size() && ptr)
		//	{
		//		this->m_others.push_back({ ptr, data });
		//		ptr->m_others.push_back({ this, data });
		//		return true;
		//	}
		//	return false;//已存在或nullptr
		//}
		//void remove(doubly_mesh* ptr)
		//{
		//	xhqm::size ind = ptr->index(this);
		//	xhqm::size pos = this->index(ptr);
		//	ptr->m_others.erase(ptr->m_others.begin() + ind);
		//	this->m_others.erase(this->m_others.begin() + pos);
		//}
	};

	template<typename type>
    class doubly_mesh<type, void, xtd::list> : public _mesh<type, doubly_mesh<type, void, xtd::list>, xtd::list, void>
	{
	public:
        using _doubly_mesh = _mesh<type, doubly_mesh<type, void, xtd::list>, xtd::list, void>;
		using iterator = typename _doubly_mesh::iterator;
		doubly_mesh(const node<type>& node) : _doubly_mesh(node) {}
		doubly_mesh(const type& value = type()) : _doubly_mesh(value) {}

		//bool insert(doubly_mesh* ptr)
		//{
		//	if (this->index(ptr) == this->size() && ptr)
		//	{
		//		this->m_others.push_back(ptr);
		//		ptr->m_others.push_back(this);
		//		return true;
		//	}
		//	return false;//已存在或nullptr
		//}
		//void remove(doubly_mesh* ptr)
		//{
		//	xhqm::size ind = ptr->index(this);
		//	xhqm::size pos = this->index(ptr);
		//	ptr->m_others.erase(ptr->m_others.begin() + ind);
		//	this->m_others.erase(this->m_others.begin() + pos);
		//}
	};


    template<typename type, bool isdou = true, class pathData = void, template<class> class dockerType = xtd::vector>
	using mesh = xhqm::select_if_type<isdou, doubly_mesh<type, pathData, dockerType>, singly_mesh<type, pathData, dockerType>>;

	//继承用网类型
	struct derive_mesh_s { virtual ~derive_mesh_s() {}; virtual void forbid_use() = 0; };

	template<class derive_data_type, template<class> class derive_mesh_type>
	struct derive_mesh_t : public xhqm::derive_mesh_s, protected xhqm::doubly_mesh<xhqm::derive_mesh_s*>
	{
		using mesh_type = xhqm::doubly_mesh<xhqm::derive_mesh_s*>;
		using mesh_ptr = derive_data_type*;

		void insert(mesh_ptr ptr)
		{
			mesh_type::insert(ptr);
		}
		void remove(mesh_ptr ptr)
		{
			mesh_type::remove(ptr);
		}
		mesh_ptr derive_node_this() { return static_cast<mesh_ptr>(this); }
	};

	template<typename derive_data>
	struct derive_mesh : public xhqm::derive_mesh_t<derive_data, derive_mesh>
	{
		virtual void forbid_use() {};
	};



	//树
	template<class type, class treeType, class childPtrs>
	struct _tree : public xhqm::node<type>
	{
		using treePtr = treeType*;
		using treeRef = treeType&;
		using iterator = typename childPtrs::iterator;
	protected:
		treePtr m_parent = nullptr;
		childPtrs m_childs;
	public:
		_tree(const node<type>& node) :xhqm::node<type>(node.data, node.name) {};
		_tree(const type& data = type(), xhqm::string name = "") :xhqm::node<type>(data, name) { };

		iterator begin()
		{
			return m_childs.begin();
		}

		const iterator begin() const
		{
			return m_childs.begin();
		}

		iterator end()
		{
			return m_childs.end();
		}

		const iterator end() const
		{
			return m_childs.end();
		}

		constexpr xhqm::size size() const noexcept {
			return m_childs.size();
		}

		constexpr xhqm::size max_size() const noexcept {
			return m_childs.max_size();
		}

		constexpr bool empty() const noexcept {
			return m_childs.empty();
		}

		constexpr treePtr& operator[](const xhqm::size& _Pos) {
			return m_childs[_Pos];
		}

		constexpr const treePtr& operator[](const xhqm::size& _Pos) const {
			return m_childs[_Pos];
		}

		constexpr treePtr root() {
			treePtr rootptr = (treePtr)this;
			while (rootptr->m_parent)
				rootptr = rootptr->m_parent;
			return rootptr;
		}

		constexpr const treePtr root() const {
			treePtr rootptr = (treePtr)this;
			while (rootptr->m_parent)
				rootptr = rootptr->m_parent;
			return rootptr;
		}

		constexpr treePtr parent() {
			return m_parent;
		}

		constexpr const treePtr parent() const {
			return m_parent;
		}

		constexpr treePtr child(const xhqm::size& _Pos) {
			return m_childs[_Pos];
		}

		constexpr const treePtr child(const xhqm::size& _Pos) const {
			return m_childs[_Pos];
		}
		constexpr childPtrs& childs() {
			return m_childs;
		}
		constexpr const childPtrs& childs() const {
			return m_childs;
		}

		bool isbrother(treePtr ptr)
		{
			if (!ptr) return false;
			return (this->m_parent == ptr->m_parent);
		}

		bool isparent(treePtr ptr)
		{
			if (!ptr) return false;
			return (this->m_parent == ptr);
		}

		bool ischild(treePtr ptr)
		{
			if (!ptr) return false;
			for (auto& child : m_childs)
				if (child == ptr) return true;
		}

		bool isroot()
		{
			return !(m_parent);
		}

		bool notnull()
		{
			for (auto& child : m_childs)
				if (child == nullptr) return false;
			return true;
		}

		xhqm::size index(treePtr ptr)
		{
			xhqm::size ind = 0;
			for (auto& child : m_childs)
			{
				if ((child != ptr) || ptr == nullptr) ++ind;
				else return ind;
			}
			return ind;
		}
	};
	
	template<typename type, xhqm::size _N>
	class fork_tree : public _tree<type, fork_tree<type, _N>, xhqm::hyper<fork_tree<type, _N>*, _N>>
	{
	public:
		using _fork_tree = _tree<type, fork_tree<type, _N>, xhqm::hyper<fork_tree<type, _N>*, _N>>;
		using iterator = typename xhqm::hyper<fork_tree<type, _N>*, _N>::iterator;
		fork_tree(const node<type>& node) : _fork_tree(node) {
			this->m_childs.fill(nullptr);
		}
		fork_tree(const type& value = type()) : _fork_tree(value) {
			this->m_childs.fill(nullptr);
		}

		void insert(fork_tree* ptr, const xhqm::size& pos)
		{
			if (ptr == this) return;
			if (this->index(ptr) == this->size() && ptr)
			{
				if (ptr->m_parent)
				{
					ptr->m_parent->m_childs[ptr->m_parent->index(ptr)] = nullptr;
				}
				this->m_childs[pos] = ptr;
				ptr->m_parent = this;
			}
		}
		bool insert(fork_tree* ptr)
		{
			if (ptr == this) return false;
			if (this->index(ptr) == this->size() && ptr)
			{
				if (this->notnull() || ptr->notnull())
					return false;//已满
				if (ptr->m_parent)
				{
					ptr->m_parent->m_childs[ptr->m_parent->index(ptr)] = nullptr;
				}
				for (auto& child : this->m_childs)
				{
					if (child == nullptr)
					{
						child = ptr;
						ptr->m_parent = this;
						return true;
					}
				}
			}
			return false;//已存在或nullptr
		}
		fork_tree* remove(const xhqm::size& pos)
		{
			fork_tree* ptr = this->m_childs[pos];
			this->m_childs[pos] = nullptr;
			return ptr;
		}
	};

    template<typename type, template<typename> class dockerType = xtd::vector>
	class docker_tree : public _tree<type, docker_tree<type, dockerType>, dockerType<docker_tree<type, dockerType>*>>
	{
	public:
		using _docker_tree = _tree<type, docker_tree<type, dockerType>, dockerType<docker_tree<type, dockerType>*>>;
		using iterator = typename _docker_tree::iterator;
		docker_tree(const node<type>& node) : _docker_tree(node) { }
		docker_tree(const type& value = type()) : _docker_tree(value) { }

		void insert(docker_tree* ptr, const xhqm::size& pos)
		{
			if (ptr == this) return;
			if (this->index(ptr) == this->size() && ptr)
			{
				if (ptr->m_parent)
				{
					ptr->m_parent->m_childs.erase(ptr->m_parent->begin() + ptr->m_parent->index(ptr));
				}
				this->m_childs.insert(this->m_childs.begin() + pos, ptr);
				ptr->m_parent = this;
			}
		}
		void insert(docker_tree* ptr)
		{
			if (ptr == this) return;
			if (this->index(ptr) == this->size() && ptr)
			{
				if (ptr->m_parent)
				{
					ptr->m_parent->m_childs.erase(ptr->m_parent->begin() + ptr->m_parent->index(ptr));
				}
				this->m_childs.push_back(ptr);
				ptr->m_parent = this;
			}
		}
		docker_tree* remove(const xhqm::size& pos)
		{
			docker_tree* ptr = this->m_childs[pos];
			if (pos < this->size() && ptr)
			{
				ptr->m_parent = nullptr;
				this->m_childs.erase(this->begin() + pos);
			}
			return ptr;
		}
	};

	template<typename type>
    class docker_tree<type, xtd::list> : public _tree<type, docker_tree<type, xtd::list>, xtd::list<docker_tree<type, xtd::list>*>>
	{
	public:
        using _docker_tree = _tree<type, docker_tree<type, xtd::list>, xtd::list<docker_tree<type, xtd::list>*>>;
		using iterator = typename _docker_tree::iterator;
		docker_tree(const node<type>& node) : _docker_tree(node) { }
		docker_tree(const type& value = type()) : _docker_tree(value) { }

		void insert(docker_tree* ptr, bool infront = false)
		{
			if (ptr == this) return;
			if (this->index(ptr) == this->size() && ptr)
			{
				if (ptr->m_parent)
				{
					auto item = ptr->m_parent->begin();
					xhqm::size ind = ptr->m_parent->index(ptr);
					while (0 != ind--) item++;
					ptr->m_parent->m_childs.erase(item);
				}
				if(infront) this->m_childs.push_front(ptr);
				else this->m_childs.push_back(ptr);
				ptr->m_parent = this;
			}
		}
		docker_tree* remove(const xhqm::size& pos)
		{
			auto item = this->m_childs.begin();
			xhqm::size ind = pos;
			while (0 != ind--) item++;
			docker_tree* ptr = *item;
			ptr->m_parent = nullptr;
			this->m_childs.erase(item);
			return ptr;
		}
	};


    template<typename type, template<class> class dockerType = xtd::vector>
	using tree = docker_tree<type, dockerType>;

	//继承用树类型
	struct derive_tree_s { virtual ~derive_tree_s() {}; virtual void forbid_use() = 0; };

	template<class derive_data_type, template<class> class derive_tree_type>
	struct derive_tree_t : public xhqm::derive_tree_s, protected xhqm::docker_tree<xhqm::derive_tree_s*>
	{
		using tree_type = xhqm::docker_tree<xhqm::derive_tree_s*>;
		using tree_ptr = derive_data_type*;

		void insert(tree_ptr ptr)
		{
			tree_type::insert(ptr);
		}
		tree_ptr remove(const xhqm::size& pos)
		{
			return static_cast<tree_ptr>(tree_type::remove(pos));
		}
		tree_ptr derive_node_this() { return static_cast<tree_ptr>(this); }
		tree_ptr derive_node_root() { return static_cast<tree_ptr>(tree_type::root()); }
		tree_ptr derive_node_parent() { return static_cast<tree_ptr>(tree_type::parent()); }
		tree_ptr derive_node_child(xhqm::size pos) { return static_cast<tree_ptr>(tree_type::child(pos)); }
		std::vector<tree_ptr> object_tree_childs()
		{
			std::vector<tree_ptr> derive_tree_childs;
			std::vector<tree_type*> tree_childs = tree_type::childs();
			for (auto& ptr : tree_childs) derive_tree_childs.push_back(static_cast<tree_ptr>(ptr));
			return derive_tree_childs;
		}
	};

	template<typename derive_data>
	struct derive_tree : public xhqm::derive_tree_t<derive_data, derive_tree>
	{
		virtual void forbid_use() {};
	};



	//链
	template<class type, class listType>
	struct _list : public xhqm::node<type>
	{
		using listPtr = listType*;
		using listRef = listType&;
	protected:
		listPtr m_last = nullptr;
		listPtr m_next = nullptr;
	public:
		_list(const node<type>& node) :xhqm::node<type>(node.data, node.name) {};
		_list(const type& data = type(), xhqm::string name = "") :xhqm::node<type>(data, name) {};


		class iterator {
			listPtr m_list = nullptr;
			listPtr m_node = nullptr;
		public:
			using value_type = type;

			constexpr iterator(listPtr listptr, xhqm::size pos) noexcept {
				m_list = listptr;
				if (m_list)
				{
					if (pos == 0) m_node = m_list->m_last;
					if (pos == 1) m_node = m_list;
					if (pos == 2) m_node = m_list->m_next;
				}
			}

			constexpr listRef operator*() const noexcept {
				return const_cast<listRef>(*m_node);
			}

			constexpr listPtr operator->() const noexcept {
				return const_cast<listPtr>(m_node);
			}

			constexpr iterator& operator++() noexcept {
				if (m_node == nullptr) m_node = m_list->m_last;
				else if (m_node == m_list->m_last) m_node = m_list;
				else if (m_node == m_list) m_node = m_list->m_next;
				else if (m_node == m_list->m_next) m_node = nullptr;
				return *this;
			}

			constexpr iterator& operator++(int) noexcept {
				iterator _Tmp = *this;
				if (m_node == nullptr) m_node = m_list->m_last;
				else if (m_node == m_list->m_last) m_node = m_list;
				else if (m_node == m_list) m_node = m_list->m_next;
				else if (m_node == m_list->m_next) m_node = nullptr;
				return _Tmp;
			}

			constexpr iterator& operator--() noexcept {
				if (m_node == nullptr) m_node = m_list->m_next;
				else if (m_node == m_list->m_next) m_node = m_list;
				else if (m_node == m_list) m_node = m_list->m_last;
				else if (m_node == m_list->m_last) m_node = nullptr;
				return *this;
			}

			constexpr iterator& operator--(int) noexcept {
				iterator _Tmp = *this;
				if (m_node == nullptr) m_node = m_list->m_next;
				else if (m_node == m_list->m_next) m_node = m_list;
				else if (m_node == m_list) m_node = m_list->m_last;
				else if (m_node == m_list->m_last) m_node = nullptr;
				return _Tmp;
			}

			constexpr iterator& operator+=(xhqm::size _Off) noexcept {
				_Off = _Off % 4;
				if (_Off == 0)
				{
				}
				else if (_Off == 1)
				{
					operator++();
				}
				else if (_Off == 2)
				{
					operator++();
					operator++();
				}
				else if (_Off == 3)
				{
					operator++();
					operator++();
					operator++();
				}
				return *this;
			}

			constexpr iterator operator+(const xhqm::size& _Off) const noexcept {
				iterator _Tmp = *this;
				_Tmp += _Off;
				return _Tmp;
			}

			constexpr iterator& operator-=(xhqm::size _Off) noexcept {
				_Off = _Off % 4;
				if (_Off == 0)
				{
				}
				else if (_Off == 1)
				{
					operator--();
				}
				else if (_Off == 2)
				{
					operator--();
					operator--();
				}
				else if (_Off == 3)
				{
					operator--();
					operator--();
					operator--();
				}
				return *this;
			}

			constexpr iterator operator-(const xhqm::size& _Off) const noexcept {
				iterator _Tmp = *this;
				_Tmp -= _Off;
				return _Tmp;
			}

			constexpr bool operator==(const iterator& right) const noexcept {
				return (m_list == right.m_list && m_node == right.m_node);
			}

			constexpr bool operator!=(const iterator& right) const noexcept {
				return (m_list != right.m_list || m_node != right.m_node);
			}
		};

		iterator begin()
		{
			return iterator(static_cast<listPtr>(this), 0);
		}

		const iterator begin() const
		{
			return iterator(static_cast<listPtr>(this), 0);
		}

		iterator end()
		{
			return iterator(static_cast<listPtr>(this), 3);
		}

		const iterator end() const
		{
			return iterator(static_cast<listPtr>(this), 3);
		}

		constexpr xhqm::size size() const noexcept {
			return 3;
		}

		constexpr xhqm::size max_size() const noexcept {
			return 3;
		}

		constexpr bool empty() const noexcept {
			return false;
		}

		constexpr listPtr lastptr() const {
			return m_last;
		}
		constexpr listPtr nextptr() const {
			return m_next;
		}
		constexpr listRef lastref() const {
			return const_cast<listRef>(*m_last);
		}
		constexpr listRef nextref() const {
			return const_cast<listRef>(*m_next);
		}

		constexpr bool isthis(listPtr ptr) const {
			return (this == ptr);
		}
		constexpr bool islast(listPtr ptr) const {
			return (m_last == ptr);
		}
		constexpr bool isnext(listPtr ptr) const {
			return (m_next == ptr);
		}
	};

	template<typename type>
	class singly_list : public _list<type, singly_list<type>>
	{
	public:
		using iterator = typename _list<type, singly_list<type>>::iterator;
		singly_list(const node<type>& node) : _list<type, singly_list<type>>(node) { }
		singly_list(const type& value = type()) : _list<type, singly_list<type>>(value) { }

		constexpr void setnext(singly_list* next) {
			this->m_next = next;
		}

		constexpr singly_list* offptr(const xhqm::size& _Off) const {
			singly_list* offset = this;
			for (xhqm::size i = 0; i < _Off; ++i)
				offset = offset->m_next;
			return offset;
		}
		constexpr singly_list& offref(const xhqm::size& _Off) const {
			singly_list* offset = this;
			for (xhqm::size i = 0; i < _Off; ++i)
				offset = offset->m_next;
			return const_cast<singly_list&>(*offset);
		}
	};
	
	template<typename type>
	class doubly_list : public _list<type, doubly_list<type>>
	{
	public:
		using iterator = typename _list<type, doubly_list<type>>::iterator;
		doubly_list(const node<type>& node) : _list<type, doubly_list<type>>(node) { }
		doubly_list(const type& value = type()) : _list<type, doubly_list<type>>(value) { }

		constexpr void setlast(doubly_list* last) {
			this->m_last = last;
			if (this->m_last) {
				if (this->m_last->m_next)
					this->m_last->m_next->m_last = nullptr;
				this->m_last->m_next = this;
			}
		}
		constexpr void setnext(doubly_list* next) {
			this->m_next = next;
			if (this->m_next) {
				if (this->m_next->m_last)
					this->m_next->m_last->m_next = nullptr;
				this->m_next->m_last = this;
			}
		}

		constexpr doubly_list* offptr(const xhqm::size& _Off) const {
			doubly_list* offset = this;
			for (xhqm::size i = 0; i < _Off; ++i)
				offset = offset->m_next;
			return offset;
		}
		constexpr doubly_list& offref(const xhqm::size& _Off) const {
			doubly_list* offset = this;
			for (xhqm::size i = 0; i < _Off; ++i)
				offset = offset->m_next;
			return const_cast<doubly_list&>(*offset);
		}
	};


	template<typename type, bool isdou = true>
	using list = xhqm::select_if_type<isdou, doubly_list<type>, singly_list<type>>;



	template<typename nodeType, typename funType>
	void forNode(nodeType*& nodeptr, funType fun) {
		if (nodeptr) {
			for (auto& node : (*nodeptr))
				forNode(node, fun);
			fun(nodeptr);		}
	}
	template<typename nodeType, typename funType>
	void backNode(nodeType*& nodeptr, funType fun) {
		if (nodeptr) {
			fun(nodeptr);
			for (auto& node : (*nodeptr))
				backNode(node, fun);
		}
	}
}
#endif
