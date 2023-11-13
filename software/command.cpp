#include "command.h"
namespace xhqm
{
	namespace software
	{
		command_group::command_group()
		{
		}
		command_group::~command_group()
		{
			for (auto& cptr : group) delete cptr;
		}
		void command_group::add_command(command* cptr)
		{
			group.push_back(cptr);
		}
		void command_group::sub_command()
		{
			group.pop_back();
		}
		void command_group::redo_comand()
		{
			xhqm::size size = group.size();
			for (xhqm::size s = 0; s < size; ++s)
				group[s]->redo_comand();
		}
		void command_group::undo_comand()
		{
			xhqm::size size = group.size();
			for (xhqm::size s = size; s > 0; --s)
				group[s - 1]->undo_comand();
		}

		void command_root::add_command(command* cptr)
		{
			if (location < group.size()) group.erase(group.begin() + location, group.end());
			command_group::add_command(cptr);
		}
		void command_root::sub_command()
		{
			command_group::sub_command();
			if (location > group.size()) location = group.size();
		}
		void command_root::redo_comand()
		{
			if (location == group.size()) return;
			group[location++]->redo_comand();
		}
		void command_root::undo_comand()
		{
			if (location == 0) return;
			group[--location]->undo_comand();
		}
		command_root* command_root::instance()
		{
			if (!xhqm::instance<command_root*>::get())
				xhqm::instance<command_root*>::get() = new command_root();
			return xhqm::instance<command_root*>::get();
		}
	}

}