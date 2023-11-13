#ifndef XHQM_ALGOR_ANALYSIS
#define XHQM_ALGOR_ANALYSIS
#include "../../../head.h"
#include <functional>
namespace xhqm
{
	namespace analysis
	{
        //容器类型 方法
        template<class type>
        struct infomation {
            using size = xhqm::size;
            type value;
            size index;
            size count;
        };

        //获取值出现次数
        //返回首一个下标
        template<class type, template<class> class docker>
        infomation<type> count(const type& value, const docker<type>& values, std::function<bool(const type&, const type&)> fun = nullptr)
        {
            xhqm::size ind = 0;
            infomation<type> info{ value, xhqm::npos, 0 };
            for (auto& in_value : values)
                if (fun ? fun(in_value, info.value) : (in_value == info.value)) {
                    info.value = (info.index == xhqm::npos ? in_value : info.value);
                    info.index = (info.index == xhqm::npos ? ind++ : info.index);
                    info.count += 1;
                } else ind++;
            return info;
        }
        //获取最值
        // '<'或'>' 返回首一个下标
        //'<='或'>='返回末一个下标
        template<class type, template<class> class docker>
        static infomation<type> most(const docker<type>& values, std::function<bool(const type&, const type&)> fun)
        {
            if (values.empty()) return infomation<type>{ type(), xhqm::npos, 0 };
            xhqm::size ind = 0;
            infomation<type> info{ values.front(), ind, 0 };
            for (auto& value : values)
                if (fun(value, info.value))
                    info = { value, ind++, 0 };
                else ind++;
            info.count = xhqm::analysis::count<type, docker>(info.value, values).count;
            return info;
        }
        //获取极值
        // '<'或'>' 返回首一个下标
        //'<='或'>='返回末一个下标
        template<class type, template<class> class docker>
        static docker<infomation<type>> pole(const docker<type>& values, std::function<bool(const type&, const type&)> fun)
        {
            docker<infomation<type>> infolist;
            docker<type> polevalues;
            if (values.size() > 2)
            {
                xhqm::size lastindex = values.size() - 1;
                for (xhqm::size index = 1; index != lastindex; ++index)
                    if (fun(*(values.begin() + index - 1), *(values.begin() + index)) &&
                        !fun(*(values.begin() + index), *(values.begin() + index + 1))) {
                        infolist.push_back({ *(values.begin() + index), index, 0 });
                        polevalues.push_back(*(values.begin() + index));
                    }
                for (auto& info : infolist)
                    info.count = xhqm::analysis::count<type, docker>(info.value, polevalues).count;
            }
            return infolist;
        }
        //获取值出现次数最多的数值
        //返回首一个下标
        template<class type, template<class> class docker>
        infomation<type> size_count(const docker<type>& values, std::function<bool(const type&, const type&)> fun = nullptr)
        {
            docker<infomation<type>> infolist;
            for (auto& value : values)
                infolist.push_back(xhqm::analysis::count<type, docker>(value, values));

            infomation<type> info{ type(), xhqm::npos, 0 };
            for (auto& in_info : infolist)
                if (in_info.count > info.count)
                    info = in_info;
            return info;
        }


        template<class type, template<class> class docker>
        inline static infomation<type> most_min(const docker<type>& values) { return xhqm::analysis::most<type, docker>(values, std::less<type>()); }
        template<class type, template<class> class docker>
        inline static infomation<type> most_max(const docker<type>& values) { return xhqm::analysis::most<type, docker>(values, std::greater<type>()); }
        template<class type, template<class> class docker>
        inline static docker<infomation<type>> pole_min(const docker<type>& values) { return xhqm::analysis::pole<type, docker>(values, std::greater<type>()); }
        template<class type, template<class> class docker>
        inline static docker<infomation<type>> pole_max(const docker<type>& values) { return xhqm::analysis::pole<type, docker>(values, std::less<type>()); }
	}
}
#endif