#ifndef XHQM_TOOL_INSTANCE
#define XHQM_TOOL_INSTANCE
#include "../head.h"
#include <mutex>
#include <typeindex>
#include <functional>
#include <unordered_map>

namespace xhqm
{
    class xhqmclass _instance {
    public:
        std::mutex m_mutex;
        xhqm::anycase m_object;
    protected:
        _instance(xhqm::anycase object) { m_object = object; };
        static _instance* regist(const std::type_index& typeIndex, std::function<xhqm::anycase()> creat);
    };

    template<typename type>	
    class instance : public _instance {
        using ins_type = type;
        inline static ins_type m_instance;
        inline static _instance* m_instanceptr = nullptr;
        static xhqm::anycase creat() { 
            return reinterpret_cast<void*>(&reinterpret_cast<char&>(m_instance));
        }
    public:
        static ins_type& get() {
            if (!m_instanceptr) m_instanceptr = _instance::regist(typeid(ins_type), &instance::creat);
            return *reinterpret_cast<ins_type*>(m_instanceptr->m_object);
        }

        static std::mutex& mutex() {
            if (!m_instanceptr) m_instanceptr = _instance::regist(typeid(ins_type), &instance::creat);
            return m_instanceptr->m_mutex;
        }
	};

    template<typename type>
    inline type& Instance() {
        return xhqm::instance<type>::get();
    }

#define xhqminstance(type) xhqm::instance<type>::get();
};
#endif