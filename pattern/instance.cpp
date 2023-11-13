#include "instance.h"

namespace xhqm
{
    struct _instanceData {
        std::mutex m_instanceMutex;
        std::unordered_map<std::type_index, _instance*> m_instancesRegist;
        ~_instanceData() { for (auto& Regist : m_instancesRegist) xhqm_delete(Regist.second); }
    };

    //注册
    static _instanceData instanceData;
    _instance* _instance::regist(const std::type_index& typeIndex, 
        std::function<xhqm::anycase()> creat) {
        std::lock_guard<std::mutex> lock(instanceData.m_instanceMutex);
        std::unordered_map<std::type_index, _instance*>::iterator itr;
        itr = instanceData.m_instancesRegist.find(typeIndex);

        //如果未曾注册
        if (itr == instanceData.m_instancesRegist.end()) {
            std::pair<std::type_index, _instance*> typeHander(typeIndex, new _instance(creat()));
            itr = instanceData.m_instancesRegist.insert(typeHander).first;
        };

        return itr->second;
    }
}