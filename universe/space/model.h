#ifndef XHQM_SPACE_MODEL
#define XHQM_SPACE_MODEL
#include "exist.h"
#include "modeldata.h"
#include "../math/tree.h"
namespace xhqm
{
	namespace space
	{
		template<class datatype>
		class model : public xhqm::space::exist<xhqm::math::tree<xhqm::space::modeldata<datatype>>>
		{
		public:
			template<class modetype>
			static std::vector<modetype*> findmodels(model* modptr)
			{
				std::vector<modetype*> typechilds;
				if (dynamic_cast<modetype*>(modptr))
					typechilds.push_back((modetype*)modptr);
				for (auto& child : modptr->childlist())
				{
					std::vector<modetype*> tmplist = model::findmodels<modetype>((model*)child);
					typechilds.insert(typechilds.end(), tmplist.begin(), tmplist.end());
				}
				return typechilds;
			}
			template<class iffun>// bool iffun(model*)
			static std::vector<model*> findmodelsif(model* modptr, iffun fun)
			{
				std::vector<model*> childs;
				if (fun(modptr))
					childs.push_back(modptr);
				for (auto& child : modptr->childlist())
				{
					std::vector<model*> tmplist = model::findmodelsif<iffun>((model*)child, fun);
					childs.insert(childs.end(), tmplist.begin(), tmplist.end());
				}
				return childs;
			}
			template<class runfun> // void runfun(xmodel*)
			static void traversebefore(model* modptr, runfun fun)
			{
				fun(modptr);
				for (auto& child : modptr->childlist())
				{
					model::traversebefore<runfun>((model*)child, fun);
				}
			}
			template<class runfun> // void runfun(xmodel*)
			static void traverseafter(model* modptr, runfun fun)
			{
				for (auto& child : modptr->childlist())
				{
					model::traverseafter<runfun>((model*)child, fun);
				}
				fun(modptr);
			}

			static void MicroToMicro(
				xhqm::math::tree<xhqm::space::modeldata<datatype>>* nowmod, 
				xhqm::math::tree<xhqm::space::modeldata<datatype>>* newparent, 
				xmat& micfrom, xvec& micmove)
			{
				if (!nowmod && !newparent) return;
				if (!nowmod) nowmod = newparent->root();
				if (!newparent) newparent = nowmod->root();

				std::size_t cout = 0;
				std::vector<xhqm::math::tree<xhqm::space::modeldata<datatype>>*> parlist;
				xhqm::space::system sys = nowmod->data;
				sys.GetMicro(micfrom, micmove);
				
				parlist = nowmod->parentlist();
				cout = parlist.size();
				for (std::size_t i = 0; i < cout; i++)
				{
					sys = parlist[i]->data;
					xhqm::space::xmat parfrom;
					xhqm::space::xvec parmove;
					sys.GetMicro(parfrom, parmove);
					xhqm::space::system::MicroGetMacro(micfrom, micmove, parfrom, parmove, micfrom, micmove);
				}

				parlist = newparent->parentlist();
				parlist.insert(parlist.begin(), newparent);
				cout = parlist.size();
				for (std::size_t i = 1; i <= cout; i++)
				{
					sys = parlist[cout - i]->data;
					xhqm::space::xmat parfrom;
					xhqm::space::xvec parmove;
					sys.GetMicro(parfrom, parmove);
					xhqm::space::system::MacroGetMicro(micfrom, micmove, parfrom, parmove, micfrom, micmove);
				}
			}

			void SetMicroPosition(xhqm::space::xmat from, xhqm::space::xvec move)
			{
				this->data.SetMicro(from, move);
			}
			void GetMicroPosition(xhqm::space::xmat& from, xhqm::space::xvec& move)
			{
				this->data.GetMicro(from, move);
			}
			void SetMacroPosition(xhqm::space::xmat from, xhqm::space::xvec move)
			{
				std::vector<xhqm::math::tree<xhqm::space::modeldata<datatype>>*> parents = this->parentlist();
				std::size_t cout = parents.size();
				for (std::size_t i = 1; i <= cout; i++)
				{
					xhqm::space::system sys = parents[cout - i]->data;
					xhqm::space::xmat parfrom;
					xhqm::space::xvec parmove;
					sys.GetMicro(parfrom, parmove);
					xhqm::space::system::MacroGetMicro(from, move, parfrom, parmove, from, move);
				}

				this->data.SetMicro(from, move);
			}
			void GetMacroPosition(xhqm::space::xmat& from, xhqm::space::xvec& move)
			{
				this->data.GetMicro(from, move);

				std::vector<xhqm::math::tree<xhqm::space::modeldata<datatype>>*> parents = this->parentlist();
				std::size_t cout = parents.size();
				for (std::size_t i = 0; i < cout; i++)
				{
					xhqm::space::system sys = parents[i]->data;
					xhqm::space::xmat parfrom;
					xhqm::space::xvec parmove;
					sys.GetMicro(parfrom, parmove);
					xhqm::space::system::MicroGetMacro(from, move, parfrom, parmove, from, move);
				}
			}

			friend void operator * (model& mod, const xhqm::space::xmat& mat) { mod.data.m_matrix = mod.data.m_matrix * mat; };
			friend void operator * (const xhqm::space::xmat& mat, model& mod) { mod.data.m_matrix = mat * mod.data.m_matrix; };
			friend void operator + (model& mod, const xhqm::space::xvec& vec) { mod.data.m_vector = mod.data.m_vector + vec; };
			friend void operator - (model& mod, const xhqm::space::xvec& vec) { mod.data.m_vector = mod.data.m_vector - vec; };
			friend void operator * (model& mod, const xhqm::space::xvec& vec) { 
				for (std::size_t i = 0; i < mod.dim; i++) mod.data.m_matrix[i][i] *=  i < vec.size() ? vec[i] : 0.0;
			};

			virtual void dynamicmodel(model* model) 		//交互模型 传入同一世界的模型
			{
				if (model == this) return;
			};
			virtual void dynamicworld(model* world)		//操作自己 传入自己所处的世界
			{
				if (world != this)
					dynamicmodel(world);
				for (auto& modptr : world->childlist())
					dynamicworld((model*)modptr);
			};
			virtual void dynamic()
			{
				dynamicworld((model*)this->root());
			};
		public:
			virtual xhqm::space::modeldata<datatype>* modeldata() { return &this->data; }
			xhqmtype(spacemodel) 
			virtual void creat() = 0;//创建模型
			virtual ~model() {};
			const xhqm::natural dim;
			model(xhqm::natural d) : dim(d)
			{ 
				this->name = "new model"; 
				this->data.m_matrix = xhqm::space::system::mati(d);
				this->data.m_vector = xhqm::space::system::veco(d);
			}
		};
	}
}

#endif 
