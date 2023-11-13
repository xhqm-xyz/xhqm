#ifndef XHQM_SOFTWARE_COMMAND
#define XHQM_SOFTWARE_COMMAND
#include "../head.h"
#include "../pattern/instance.h"
namespace xhqm
{
	namespace software
	{
		class xhqmclass command
		{
		public:
			command() {};
			virtual ~command() {};

			virtual void redo_comand() = 0;
			virtual void undo_comand() = 0;
		};

		class xhqmclass command_group : public command
		{
		protected:
			std::vector<command*> group;
		public:
			command_group();
			virtual ~command_group();

			virtual void add_command(command* cptr);
			virtual void sub_command();

			virtual void redo_comand();
			virtual void undo_comand();
		};

		class xhqmclass command_root : public command_group
		{
		protected:
			xhqm::size location = 0;
			command_root() {};
		public:
			virtual void add_command(command* cptr);
			virtual void sub_command();

			virtual void redo_comand();
			virtual void undo_comand();

			static command_root* instance();
		};
	}
}

#endif

