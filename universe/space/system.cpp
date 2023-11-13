#include "system.h"
//先姿态，后位置
//先矩阵，后向量
//矩阵 变换 模型
//模型 进入 参考系

namespace xhqm
{
	namespace space
	{
		system::system()
			: m_matrix(*this)
			, m_vector(*this)
		{

		}

		system::system(const system& sys)
			: xhqm::space::xmat(sys)
			, xhqm::space::xvec(sys)
			, m_matrix(*this)
			, m_vector(*this) 
		{

		}

		void system::MacroGetMicro(xmat macfrom, xvec macmove, xmat parfrom, xvec parmove, xmat& micfrom, xvec& micmove)
		{
			////向一线性子空间的投影矩阵 A * (A^t * A)^-1 * A^t ;
			//parfrom = parfrom * (parfrom.tramat() * parfrom).invmat() * parfrom.tramat();

			std::size_t rowsize;
			std::size_t colsize;
			parfrom.dimension(rowsize, colsize);
			parfrom = parfrom + mati(xmax(rowsize, colsize)) - mati(xmin(rowsize, colsize));

			xhqm::space::xmat parinv = parfrom.invmat();
			micfrom = macfrom * parinv;
			micmove = (macmove - parmove) * parinv;
		}

		void system::MicroGetMacro(xmat micfrom, xvec micmove, xmat parfrom, xvec parmove, xmat& macfrom, xvec& macmove)
		{
			macfrom = micfrom * parfrom;
			macmove = micmove * parfrom + parmove;
		}


		xhqm::space::xvec system::veco(xhqm::natural n)
		{
			xhqm::space::xvec vo(n);
			return vo;
		}
		xhqm::space::xvec system::veci(xhqm::natural n, xhqm::natural i)
		{
			xhqm::space::xvec vi(n);
			vi[i] = 1.0;
			return vi;
		}
		xhqm::space::xmat system::mato(xhqm::natural n)
		{
			xhqm::space::xmat mi(n, n);
			return mi;
		}
		xhqm::space::xmat system::mati(xhqm::natural n)
		{
			xhqm::space::xmat mi(n, n);
			for (xhqm::natural i = 0; i < n; i++)
				mi[i][i] = 1.0;
			return mi;
		}
		xhqm::space::xmat system::rotate(std::vector<bool> vi, xhqm::measure var)
		{
			std::size_t i = 0;
			std::size_t j = 0;
			std::size_t size = vi.size();
			xhqm::space::xmat matr = mati(size);
			for (std::size_t n = 0; n < size; n++)
			{
				if (!vi[n] && i != 0) j = n;
				if (!vi[n] && i == 0) i = n;
			}

			xhqm::space::xmat rote
			{
				{std::cos(var),-std::sin(var)},
				{std::sin(var), std::cos(var)},
			};

			matr[i][i] = rote[0][0];
			matr[i][j] = rote[0][1];
			matr[j][i] = rote[1][0];
			matr[j][j] = rote[1][1];
			return matr;
		}
		xhqm::space::xmat system::flexible(std::vector<bool> vi, xhqm::measure var)
		{
			std::size_t size = vi.size();
			xhqm::space::xmat matf = mati(size);
			for (std::size_t n = 0; n < size; n++)
			{
				matf[n][n] = vi[n] ? var : 1.0;
			}
			return matf;
		}
		xhqm::space::xmat system::matdim(xhqm::space::xmat mat, xhqm::natural dim)
		{
			std::size_t rowsize;
			std::size_t colsize;
			mat.dimension(rowsize, colsize);
			xhqm::space::xmat mate = mati(dim);
			rowsize = xmin(rowsize, dim);
			colsize = xmin(colsize, dim);
			for (std::size_t row = 0; row < rowsize; row++)
				for (std::size_t col = 0; col < colsize; col++)
					mate[row][col] = mat[row][col];

			return mate;
		}
	}
}

