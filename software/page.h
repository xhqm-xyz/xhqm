#ifndef XHQM_SOFTWARE_PAGE
#define XHQM_SOFTWARE_PAGE
#include "action.h"
namespace xhqm
{
    namespace software
    {
        class xhqmclass page : public xhqm::software::action
        {
        public:
            xhqm::pluginlist<xhqm::software::action> m_pluginlist;
            page(std::string name, std::string icon, std::string type);
            virtual ~page();
        public:
            virtual void moveplugin();
            virtual void loadplugin(std::string type);
            virtual void except_event(xhqm::event* e);//广播事件

            template<typename type>
            xhqm::software::contextptr context(type* text, xhqm::software::window wind)
            {
                std::lock_guard<std::mutex> lock(xhqm::software::context::get()->m_mutex);
                xhqm::software::contextptr cptr = xhqm::software::context::get();
                cptr->m_context = text;
                cptr->m_window = wind;
                return cptr;
            }
        };
    }
}
#define resigtpage(classname) static xhqm::plugin<xhqm::software::page> page##classname(new classname());
#endif
