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

        //返回容器的和值 infomation.count!=0时有效
        template<class type, template<class> class docker>
        infomation<type> sum_values(const docker<type>& values)
        {
            infomation<type> sum{ type(), xhqm::npos, values.size() };
            for (auto& value : values) sum.value = sum.value + value;
            return sum;
        }

        //返回容器的均值 infomation.count!=0时有效
        template<class type, template<class> class docker>
        infomation<type> mean_values(const docker<type>& values)
        {
            infomation<type> mean = xhqm::analysis::sum_values<type, docker>(values);
            if (mean.count) mean.value = mean.value / static_cast<type>(mean.count);
            return mean;
        }

        //返回容器的标准差 infomation.count!=0时有效
        template<class type, template<class> class docker>
        infomation<type> standard_values(const docker<type>& values, std::function<type(const type&)> sqrtfun)
        {
            infomation<type> mean = xhqm::analysis::mean_values<type, docker>(values);
            infomation<type> variance = { type(), xhqm::npos, values.size() };
            if (variance.count)
            {
                for (auto& value : values)
                    variance.value = variance.value + (value - mean.value) * (value - mean.value);
                variance.value = sqrtfun(variance.value / static_cast<type>(variance.count));
            }
            return variance;
        }

        //返回容器的方差 infomation.count!=0时有效
        template<class type, template<class> class docker>
        infomation<type> variance_values(const docker<type>& values)
        {
            infomation<type> mean = xhqm::analysis::mean_values<type, docker>(values);
            infomation<type> variance = { type(), xhqm::npos, values.size() };
            if (variance.count)
            {
                for (auto& value : values)
                    variance.value = variance.value + (value - mean.value) * (value - mean.value);
                variance.value = variance.value / static_cast<type>(variance.count);
            }
            return variance;
        }

        template<class type>//返回容器的自协方差 infomation.count>infomation.index时有效
        infomation<type> self_covariance(const std::vector<type>& values, const xhqm::size& subk)
        {
            infomation<type> mean = xhqm::analysis::mean_values<type, std::vector>(values);
            infomation<type> variance = { type(), subk, values.size() };
            if (variance.count > variance.index)
            {
                xhqm::size count = variance.count - variance.index;
                for (xhqm::size i = 0; i < count; ++i)
                    variance.value = variance.value + (values[i] - mean.value) * (values[i + subk] - mean.value);
                variance.value = variance.value / static_cast<type>(variance.count);
            }
            return variance;
        }

        template<class type>//返回容器的自协方差 infomation.count>infomation.index时有效
        infomation<type> self_covariance_adjusted(const std::vector<type>& values, const xhqm::size& subk)
        {
            infomation<type> mean = xhqm::analysis::mean_values<type, std::vector>(values);
            infomation<type> variance = { type(), subk, values.size() };
            if (variance.count > variance.index)
            {
                xhqm::size count = variance.count - variance.index;
                for (xhqm::size i = 0; i < count; ++i)
                    variance.value = variance.value + (values[i] - mean.value) * (values[i + subk] - mean.value);
                variance.value = variance.value / static_cast<type>(count);
            }
            return variance;
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