#include "xcube.h"

namespace xhqm
{
    namespace space
    {

        xcube xcube::operator+=(const xvec& vec)
        {
            for (auto& pt : *this)
                pt += vec;
            return *this;
        }

        xcube xcube::operator-=(const xvec& vec)
        {
            for (auto& pt : *this)
                pt -= vec;
            return *this;
        }

        xcube xcube::operator*=(const xvec& vec)
        {
            for (auto& pt : *this)
                pt *= vec;
            return *this;
        }

        xcube xcube::operator*=(const xmat& mat)
        {
            for (auto& pt : *this)
                pt *= mat;
            return *this;
        }

        xcube operator+(const xcube& cube, const xvec& vec)
        {
            xcube res = cube;
            for (auto& pt : res)
                pt += vec;
            return res;
        }

        xcube operator-(const xcube& cube, const xvec& vec)
        {
            xcube res = cube;
            for (auto& pt : res)
                pt -= vec;
            return res;
        }

        xcube operator*(const xcube& cube, const xvec& vec)
        {
            xcube res = cube;
            for (auto& pt : res)
                pt *= vec;
            return res;
        }

        xcube operator*(const xcube& cube, const xmat& mat)
        {
            xcube res = cube;
            for (auto& pt : res)
                pt = pt * mat;
            return res;
        }

        xcube operator*(const xmat& mat, const xcube& cube)
        {
            xcube res = cube;
            for (auto& pt : res)
                pt = mat * pt;
            return res;
        }



        xdimcube xdimcube::operator=(const xdimcube& cubes)
        {
            if (dim == cubes.dim)
            {
                this->cubes = cubes.cubes;
            }
            return cubes;// xdimcube(0);
        }


        xdimcube operator+=(xdimcube& cubes, const xvec& vec)
        {
            for (auto& xcube : cubes.cubes)
                xcube += vec;
            return cubes;
        }

        xdimcube operator-=(xdimcube& cubes, const xvec& vec)
        {
            for (auto& xcube : cubes.cubes)
                xcube -= vec;
            return cubes;
        }

        xdimcube operator*=(xdimcube& cubes, const xvec& vec)
        {
            for (auto& xcube : cubes.cubes)
                xcube *= vec;
            return cubes;
        }

        xdimcube operator*=(xdimcube& cubes, const xmat& mat)
        {
            for (auto& xcube : cubes.cubes)
                xcube *= mat;
            return cubes;
        }

        xdimcube operator+(const xdimcube& cubes, const xvec& vec)
        {
            xdimcube cubesCopy(cubes.dim);
            for (auto& xcube : cubes.cubes)
                cubesCopy.push_back(xcube + vec);
            return cubesCopy;
        }

        xdimcube operator-(const xdimcube& cubes, const xvec& vec)
        {
            xdimcube cubesCopy(cubes.dim);
            for (auto& xcube : cubes.cubes)
                cubesCopy.push_back(xcube - vec);
            return cubesCopy;
        }

        xdimcube operator*(const xdimcube& cubes, const xvec& vec)
        {
            xdimcube cubesCopy(cubes.dim);
            for (auto& xcube : cubes.cubes)
                cubesCopy.push_back(xcube * vec);
            return cubesCopy;
        }

        xdimcube operator*(const xdimcube& cubes, const xmat& mat)
        {
            xdimcube cubesCopy(cubes.dim);
            for (auto& xcube : cubes.cubes)
                cubesCopy.push_back(xcube * mat);
            return cubesCopy;
        }

        xdimcube operator*(const xmat& mat, const xdimcube& cubes)
        {
            xdimcube cubesCopy(cubes.dim);
            for (auto& xcube : cubes.cubes)
                cubesCopy.push_back(mat * xcube);
            return cubesCopy;
        }

        xdimcube::xdimcube(const xdimcube& copy) :dim(copy.dim)
        {
            this->cubes = copy.cubes;
        }

        xdimcube::xdimcube(const natural& d) :dim(d) { }

        size_t xdimcube::size() const
        {
            return cubes.size();
        }

        bool xdimcube::push_back(const xcube& cube)
        {
            if (cube.size() == dim)
            {
                cubes.push_back(cube);
                return true;
            }
            return false;
        }
        void xdimcube::pop_back()
        {
            cubes.pop_back();
        }
        void xdimcube::clear()
        {
            cubes.clear();
        }

    }
}
