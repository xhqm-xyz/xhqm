#ifndef XHQM_ALGOR_RANSAC
#define XHQM_ALGOR_RANSAC
#include "../../../head.h"
#include "geometry.h"
namespace xhqm
{
	namespace ransac
	{
		template<class element, xhqm::natural _dim>
		class model
		{
			const xhqm::natural m_dim;
			std::vector<element> m_describe;
		public:
			inline model(std::vector<element> elements) : m_dim(_dim) {

				for (xhqm::natural i = 0; i < m_dim; i++)
				{
					if (i < elements.size())
						m_describe.push_back(elements[i]);
					else
						m_describe.push_back(element());
				}
			}
			inline model() : m_dim(_dim) {
				for (xhqm::natural i = 0; i < m_dim; i++)
					m_describe.push_back(element());
			}
			inline std::vector<element> describe() const { return m_describe; };

			inline model operator= (const model& mod) { m_describe = mod.describe(); return *this; }

			static std::vector<xhqm::natural> randindex(const xhqm::natural& count)
			{
				std::vector<xhqm::natural> index;
				while (index.size() < _dim)
				{
					bool usind = true;
					xhqm::natural ind = std::rand() % count;
					for (auto& idx : index)
					{
						if (ind == idx)
						{
							usind = false;
							break;
						}
					}
					if (usind) index.push_back(ind);
				}
				return index;
			}
		};

		

		//elements 元素集合
		//maxiter 最大运行步数
		//minsize 最小元素个数
		//similar 限制值
		//besteleind 符合最佳模型的元素集合
		// //bool similarityfun(const model &mod, const element &ele, const measure &sim)
		// //mod 描述模型 
		// //ele 计算元素
		// //sim 限制值
		//返回值 最佳模型
		template<class element, xhqm::natural _dim, class similarityfun>
		xhqm::ransac::model<element, _dim> ransac(std::vector<element> elements,
			xhqm::natural maxiter, xhqm::natural minsize, xhqm::measure similar,
			std::vector<xhqm::natural>& besteleind,
			similarityfun fun) 
		{
			//用RANSAC方法获取最佳模型
			xhqm::ransac::model<element, _dim> bestModel;		//最佳模型
			std::vector<xhqm::natural> indexList;		//模型的包含元素
			xhqm::natural bestInliersCount = 0;			//最佳模型的包含元素数目
			besteleind.clear();
			if (!elements.size())
			{
				return bestModel;
			}

			for (xhqm::natural iter = 0; iter < maxiter; iter++)
			{
				indexList.clear();
				xhqm::natural inliersCount = 0;
				std::vector<xhqm::natural> idxlist = xhqm::ransac::model<element, _dim>::randindex(elements.size());
				std::vector<element> eles;
				for (auto& idx : idxlist)
				{
					eles.push_back(elements[idx]);
				}

				xhqm::ransac::model<element, _dim> mod(eles);
				for (xhqm::natural i = 0; i < elements.size(); i++)
				{
					if (fun(mod, elements[i], similar))
					{
						inliersCount++;
						indexList.push_back(i);
					}
				}

				if (inliersCount >= minsize)
				{
					if (inliersCount > bestInliersCount)
					{
						bestModel = mod;
						besteleind = indexList;
						bestInliersCount = inliersCount;
					}
				}
			}
			return bestModel;
		};

		//拟合点
		//std::vector<xhqm::natu> bestpoints;
		//std::vector<xhqm::pot3> pointcloud;
		//xhqm::ransac::model<xhqm::pot3, 1> poit = xhqm::ransac::ransac<xhqm::pot3, 1>(pointcloud, 20, 15, 0.01, bestpoints, xhqm::ransac::Pot_similarityfun);
		bool xhqmclass Pot_similarityfun(const xhqm::ransac::model<xhqm::pot3, 1>& poit, const xhqm::pot3& mespot, const xhqm::measure& maxdis);
		//拟合直线
		//std::vector<xhqm::natu> bestpoints;
		//std::vector<xhqm::pot3> pointcloud;
		//xhqm::ransac::model<xhqm::pot3, 2> line = xhqm::ransac::ransac<xhqm::pot3, 2>(pointcloud, 20, 15, 0.01, bestpoints, xhqm::ransac::Wire_similarityfun);
		bool xhqmclass Wire_similarityfun(const xhqm::ransac::model<xhqm::pot3, 2>& line, const xhqm::pot3& pot, const xhqm::measure& maxdis);
		//拟合平面
		//std::vector<xhqm::natu> bestpoints;
		//std::vector<xhqm::pot3> pointcloud;
		//xhqm::ransac::model<xhqm::pot3, 3> face = xhqm::ransac::ransac<xhqm::pot3, 3>(pointcloud, 20, 15, 0.01, bestpoints, xhqm::ransac::Patch_similarityfun);
		bool xhqmclass Patch_similarityfun(const xhqm::ransac::model<xhqm::pot3, 3>& face, const xhqm::pot3& pot, const xhqm::measure& maxdis);
		//拟合球
		//std::vector<xhqm::natu> bestpoints;
		//std::vector<xhqm::pot3> pointcloud;
		//xhqm::ransac::model<xhqm::pot3, 4> ball = xhqm::ransac::ransac<xhqm::pot3, 4>(pointcloud, 20, 15, 0.01, bestpoints, xhqm::ransac::Ball_similarityfun);
		bool xhqmclass Ball_similarityfun(const xhqm::ransac::model<xhqm::pot3, 4>& ball, const xhqm::pot3& pot, const xhqm::measure& maxdis);

	};
}
#endif