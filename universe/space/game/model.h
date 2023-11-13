#ifndef XHQM_GAME_MODEL
#define XHQM_GAME_MODEL
#include "data.h"
#include "../math/tree.h"
#include "../game/exist.h"
namespace xhqm
{
	namespace game
	{
		template<class type>
		class model : public xhqm::game::exist<xhqm::math::tree<xhqm::game::data<type>>>
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
			template<class runfun> // void runfun(model*)
			static void traversebefore(model* modptr, runfun fun)
			{
				fun(modptr);
				for (auto& child : modptr->childlist())
				{
					model::traversebefore<runfun>((model*)child, fun);
				}
			}
			template<class runfun> // void runfun(model*)
			static void traverseafter(model* modptr, runfun fun)
			{
				for (auto& child : modptr->childlist())
				{
					model::traverseafter<runfun>((model*)child, fun);
				}
				fun(modptr);
			}

			static void deletemodels(model* root)
			{
				root->stop();
				auto list = root->childlist();
				for (auto& child : list)
					model::deletemodels((model*)child);
				delete root;
			}

			static void mic2mic(
				xhqm::math::tree<xhqm::game::data<type>>* nowmodptr,
				xhqm::math::tree<xhqm::game::data<type>>* newparent,
				xhqm::game::mat<type>& micfrom, xhqm::game::vec<type>& micmove)
			{
				if (!nowmodptr && !newparent) return;
				if (!nowmodptr) nowmodptr = newparent->root();
				if (!newparent) newparent = nowmodptr->root();

				std::size_t cout = 0;
				std::vector<xhqm::math::tree<xhqm::game::data<type>>*> parlist;
				xhqm::game::sys<type> sys = nowmodptr->data;
				sys.getmic(micfrom, micmove);
				
				parlist = nowmodptr->parentlist();
				cout = parlist.size();
				for (std::size_t i = 0; i < cout; i++)
				{
					sys = parlist[i]->data;
					xhqm::game::mat<type> parfrom;
					xhqm::game::vec<type> parmove;
					sys.getmic(parfrom, parmove);
					xhqm::game::sys<type>::mic2mac(micfrom, micmove, parfrom, parmove, micfrom, micmove);
				}

				parlist = newparent->parentlist();
				parlist.insert(parlist.begin(), newparent);
				cout = parlist.size();
				for (std::size_t i = 1; i <= cout; i++)
				{
					sys = parlist[cout - i]->data;
					xhqm::game::mat<type> parfrom;
					xhqm::game::vec<type> parmove;
					sys.getmic(parfrom, parmove);
					xhqm::game::sys<type>::mac2mic(micfrom, micmove, parfrom, parmove, micfrom, micmove);
				}
			}

			void setmic(xhqm::game::mat<type> from, xhqm::game::vec<type> move)
			{
				this->data.setmic(from, move);
			}
			void getmic(xhqm::game::mat<type>&from, xhqm::game::vec<type>&move)
			{
				this->data.getmic(from, move);
			}
			void setmac(xhqm::game::mat<type> from, xhqm::game::vec<type> move)
			{
				std::vector<xhqm::math::tree<xhqm::game::data<type>>*> parents = this->parentlist();
				std::size_t cout = parents.size();
				for (std::size_t i = 1; i <= cout; i++)
				{
					xhqm::game::sys<type> sys = parents[cout - i]->data;
					xhqm::game::mat<type> parfrom;
					xhqm::game::vec<type> parmove;
					sys.getmic(parfrom, parmove);
					xhqm::game::sys<type>::mac2mic(from, move, parfrom, parmove, from, move);
				}

				this->data.setmic(from, move);
			}
			void getmac(xhqm::game::mat<type>&from, xhqm::game::vec<type>&move)
			{
				this->data.getmic(from, move);

				std::vector<xhqm::math::tree<xhqm::game::data<type>>*> parents = this->parentlist();
				std::size_t cout = parents.size();
				for (std::size_t i = 0; i < cout; i++)
				{
					xhqm::game::sys<type> sys = parents[i]->data;
					xhqm::game::mat<type> parfrom;
					xhqm::game::vec<type> parmove;
					sys.getmic(parfrom, parmove);
					xhqm::game::sys<type>::mic2mac(from, move, parfrom, parmove, from, move);
				}
			}

			friend void operator * (model<type>& mod, const xhqm::game::mat<type>& mat) { mod.data.m_mat = mod.data.m_mat * mat; };
			friend void operator * (const xhqm::game::mat<type>& mat, model<type>& mod) { mod.data.m_mat = mat * mod.data.m_mat; };
			friend void operator + (model<type>& mod, const xhqm::game::vec<type>& vec) { mod.data.m_vec = mod.data.m_vec + vec; };
			friend void operator - (model<type>& mod, const xhqm::game::vec<type>& vec) { mod.data.m_vec = mod.data.m_vec - vec; };
			friend void operator * (model<type>& mod, const xhqm::game::vec<type>& vec) {
				mod.data.m_mat[0][0] *= vec.val(0);
				mod.data.m_mat[1][1] *= vec.val(1);
				mod.data.m_mat[2][2] *= vec.val(2);
			};

			virtual void dynamicmodel(model<type>* model) 		//交互模型 传入同一世界的模型
			{
				if (model == this) return;
			};
			virtual void dynamicworld(model<type>* world)		//操作自己 传入自己所处的世界
			{
				if (world != this)
					dynamicmodel(world);
				for (auto& modptr : world->childlist())
					dynamicworld((model<type>*)modptr);
			};
			virtual void dynamic()
			{
				dynamicworld((model<type>*)this->root());
			};
		public:
			xhqmtype(gamemodel)
			virtual void creat() = 0;//创建模型
            virtual ~model() {};
			model()
			{ 
				this->name = "new model"; 
			}
		};
	}
}

#endif 
