#ifndef XHQM_ALGOR_RANSAC
#define XHQM_ALGOR_RANSAC
#include "../../../head.h"
#include "geometry.h"
namespace xhqm
{
    template<class type>
    class StatisticValues
    {
    public:
        //0:value1 == value2
        //+1:value1 > value2
        //-1:value1 < value2
        //xhqm::sign res = comparefun(type value1, type value2)
        std::function<xhqm::sign(type, type)> compare;
        StatisticValues() {
            compare = [](type v1, type v2) ->xhqm::sign {
                if (v1 == v2) return 0;
                if (v1 > v2) return +1;
                if (v1 < v2) return -1;
            };
        };
        StatisticValues(std::function<xhqm::sign(type, type)> fun) {
            compare = fun;
        };

        std::vector<xhqm::size> max_list(const std::vector<type>& listData)//获取极大值
        {
            std::vector<xhqm::size> maxlist;
            if (listData.size() == 0) {

            }
            else if (listData.size() == 1)
            {
                maxlist.push_back(listData[0]);
            }
            else if (listData.size() == 2)
            {
                xhqm::sign res = compare(listData[0], listData[1]);
                maxlist.push_back(res >= 0 ? listData[0] : listData[1]);
            }
            else
            {
                xhqm::size lastindex = listData.size() - 1;
                for (xhqm::size index = 1; index < lastindex; ++index)
                    if ((compare(listData[index - 1], listData[index]) < 0) &&
                        (compare(listData[index], listData[index + 1]) >= 0))
                        maxlist.push_back(index);
            }
            return maxlist;
        }

        std::vector<xhqm::size> min_list(const std::vector<type>& listData)//获取极小值
        {
            std::vector<xhqm::size> minlist;
            if (listData.size() == 0) {

            }
            else if (listData.size() == 1)
            {
                minlist.push_back(listData[0]);
            }
            else if (listData.size() == 2)
            {
                xhqm::sign res = compare(listData[0], listData[1]);
                minlist.push_back(res <= 0 ? listData[0] : listData[1]);
            }
            else
            {
                xhqm::size lastindex = listData.size() - 1;
                for (xhqm::size index = 1; index < lastindex; ++index)
                    if ((compare(listData[index - 1], listData[index]) > 0) &&
                        (compare(listData[index], listData[index + 1]) <= 0))
                        minlist.push_back(index);
            }
            return minlist;
        }

        std::pair<type, type> operator()(const std::vector<type>& listData)//获取平均周期与平均幅值
        {
            std::vector<xhqm::size> maxlist = max_list(listData);
            std::vector<xhqm::size> minlist = min_list(listData);
            xhqm::size size = std::min(maxlist.size(), minlist.size());

            type maxtime = 0.0;
            type mintime = 0.0;
            type max_min = 0.0;
            for (xhqm::size i = 1; i < size; ++i)
            {
                maxtime = maxtime + maxlist[i] - maxlist[i - 1];
                mintime = mintime + minlist[i] - minlist[i - 1];
                max_min = max_min + listData[maxlist[i]] - listData[minlist[i]];
            }

            type characteristicperiod = (maxtime + mintime) / (2.0 * (size - 1));//获取平均周期
            type significantvalve = max_min / (size - 1.0);//获取平均幅值
            return std::pair<type, type>(characteristicperiod, significantvalve);
        }
    };

}
#endif
