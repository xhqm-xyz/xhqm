#ifndef XHQM_SPACE_XCUBE
#define XHQM_SPACE_XCUBE
#include "xpoit.h"
namespace xhqm
{
	namespace space
	{
		class xhqmclass xcube :public xpoints //n维空间对象（n个点）
		{
		public:
			inline xcube(xpoit p1) :xpoints(1)
			{
				(*this)[0] = p1;
			};
			inline xcube(xpoit p1, xpoit p2) :xpoints(2)
			{
				(*this)[0] = p1; (*this)[1] = p2;
			};
			inline xcube(xpoit p1, xpoit p2, xpoit p3) :xpoints(3)
			{
				(*this)[0] = p1; (*this)[1] = p2; (*this)[2] = p3;
			};
			inline xcube(xpoit p1, xpoit p2, xpoit p3, xpoit p4) :xpoints(4)
			{
				(*this)[0] = p1; (*this)[1] = p2; (*this)[2] = p3; (*this)[3] = p4;
			};
			inline xcube(xpoints poits) :xpoints(poits) {};
			inline xcube(const xvec::size_type& dim = 0) :xpoints(dim) {};
			inline xcube(std::initializer_list<xpoit> list) : xpoints(list) {};

			inline xcube operator += (const xvec& vec);
			inline xcube operator -= (const xvec& vec);
			inline xcube operator *= (const xvec& vec);
			inline xcube operator *= (const xmat& mat);
			inline friend xcube operator + (const xcube& cube, const xvec& vec);
			inline friend xcube operator - (const xcube& cube, const xvec& vec);
			inline friend xcube operator * (const xcube& cube, const xvec& vec);
			inline friend xcube operator * (const xcube& cube, const xmat& mat);
			inline friend xcube operator * (const xmat& mat, const xcube& cub);
		};

#define spacepoit(p1) xcube(p1)
#define spaceline(p1,p2) xcube(p1,p2)
#define spaceface(p1,p2,p3) xcube(p1,p2,p3)

		class xhqmclass xdimcube//同维度空间对象集合
		{
		public:
			std::vector<xcube> cubes;
			const natural dim;
		public:
            xdimcube(const xdimcube& copy);
			xdimcube(const natural& d);
			bool push_back(const xcube& cube);
			size_t size() const;
			void pop_back();
			void clear();
		public:
			xdimcube operator= (const xdimcube& cubes);

			inline friend xdimcube operator+= (xdimcube& cubes, const xvec& vec);
			inline friend xdimcube operator-= (xdimcube& cubes, const xvec& vec);
			inline friend xdimcube operator*= (xdimcube& cubes, const xvec& vec);
			inline friend xdimcube operator*= (xdimcube& cubes, const xmat& mat);
			inline friend xdimcube operator + (const xdimcube& cubes, const xvec& vec);
			inline friend xdimcube operator - (const xdimcube& cubes, const xvec& vec);
			inline friend xdimcube operator * (const xdimcube& cubes, const xvec& vec);
			inline friend xdimcube operator * (const xdimcube& cubes, const xmat& mat);
			inline friend xdimcube operator * (const xmat& mat, const xdimcube& cubes);
		};

		typedef std::vector<xdimcube> xcubedata;
	}
}

#endif // !UNIVERSE_SPACE_XCUBE
