#ifndef XHQM_SPACE_SYSTEM
#define XHQM_SPACE_SYSTEM
#include "../head.h"
#include "../math/vector.h"
#include "../math/matrix.h"
namespace xhqm
{
	namespace space
	{
		using xpot = xhqm::math::vector<xhqm::measure>;
		using xvec = xhqm::math::vector<xhqm::measure>;
		using xmat = xhqm::math::matrix<xhqm::measure>;

		class xhqmclass system :public xhqm::space::xmat, public xhqm::space::xvec
		{
		public:
			system();
			system(const system& sys);
			xhqm::space::xmat& m_matrix;
			xhqm::space::xvec& m_vector;

			system& operator = (const system& sys) { m_matrix = sys; m_vector = sys; return (*this); };

			//先姿态，后位置
			//先矩阵，后向量
			//矩阵 变换 模型
			//模型 进入 参考系
			void SetMicro(xhqm::space::xmat from, xhqm::space::xvec move) { m_matrix = from; m_vector = move; }
			void GetMicro(xhqm::space::xmat&from, xhqm::space::xvec&move) { from = m_matrix; move = m_vector; }
			static void MacroGetMicro(xmat macfrom, xvec macmove, xmat parfrom, xvec parmove, xmat& micfrom, xvec& micmove);
			static void MicroGetMacro(xmat micfrom, xvec micmove, xmat parfrom, xvec parmove, xmat& macfrom, xvec& macmove);

			static xhqm::space::xvec veco(xhqm::natural n);//零向量
			static xhqm::space::xvec veci(xhqm::natural n, xhqm::natural i);//基向量
			static xhqm::space::xmat mato(xhqm::natural n);//零矩阵
			static xhqm::space::xmat mati(xhqm::natural n);//单位矩阵
			static xhqm::space::xmat rotate(std::vector<bool> vi, xhqm::measure var);//旋变矩阵
			static xhqm::space::xmat flexible(std::vector<bool> vi, xhqm::measure var);//抻变矩阵
			static xhqm::space::xmat matdim(xhqm::space::xmat mat, xhqm::natural dim);//缩扩矩阵
		};

	}
}
#endif
