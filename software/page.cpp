#include "page.h"
namespace xhqm
{
    namespace software
    {
        page::page(std::string name, std::string icon, std::string type)
            : xhqm::software::action(name, icon, type)
        {
        }
        page::~page()
        {

        }

        void page::moveplugin()
        {
            for (auto& plugin : m_pluginlist)
            {
                plugin->action->leave();
                plugin->action->delewind();
            }
            m_pluginlist.clear();
        }
        void page::loadplugin(std::string type)
        {
            m_pluginlist.clear();
            auto plugins = xhqm::plugin<xhqm::software::action>::plugins();
            for (auto& plugin : plugins)
            {
                if (plugin->action->type() == type)
                {
                    m_pluginlist.push_back(plugin);
                    plugin->action->initwind();
                    if (plugin->action->need() || plugin->action->first())
                        plugin->action->enter();
                }
            }
        }
        void page::except_event(xhqm::event* e)
        {
            except_mousekey_events::except_event(e);
            for (auto& plugin : m_pluginlist)
            {
                if (plugin->action->is_enter())
                {
                    plugin->action->ins_event(static_cast<xhqm::software::keyevent*>(e->copy()));
                }
            }
        }
    }
}