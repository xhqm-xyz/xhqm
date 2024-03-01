#ifndef XHQM_OBJECT
#define XHQM_OBJECT
#include "../head.h"
#include "../conception/struct.h"
#include "../metaclass/template.h"
#include "../pattern/instance.h"
namespace xhqm 
{
	struct object_count
	{
	protected:
		xhqm::size count = 0;
		object_count() : count(0) {};
		object_count(const object_count&) {};
		friend xhqm::instance<xhqm::object_count>;
	public:
		static xhqm::size size()
		{
			return xhqm::instance<xhqm::object_count>::get().count;
		}
		static xhqm::size next_id()
		{
			xhqm::instance<xhqm::object_count>::get().count++;
			return xhqm::instance<xhqm::object_count>::get().count;
		}
	};

	template<typename object_type>
	struct object_info
	{
	private:
		inline static xhqm::size _this_id = xhqm::object_count::next_id();
	public:
		inline static xhqm::size this_id() { return _this_id; };
		inline static xhqm::size type_id() { return object_type::type_id(); };
		inline static xhqm::string type_name() { return object_type::type_name(); };
		inline static xhqm::size type_count() { return xhqm::object_count::size(); };
		inline static bool is_object() { return this_id() == type_id(); };
		inline static bool object_run_warning()
		{
			bool is_object_v = is_object();
			if (!is_object_v) std::cout << "warning : object_type is not " << type_name() << std::endl;
			return is_object_v;
		};
	};

	template<typename object_type>
	class object
	{
	protected:
		using child_type = object_type;
	protected:

	private:
		virtual bool init_object() = 0;//使xhqm::object<type>不可直接使用
	public:
		inline static xhqm::size type_id() { return xhqm::object_info<object_type>::this_id(); };
		inline static xhqm::string type_name() { return XHQMTOSTR(xhqm::object); };
		inline static xhqm::size type_count() { return xhqm::object_count::size(); };
	};

#define xhqm_object(object_type)		\
	public:								\
		inline static xhqm::size type_id() { return this_id;  };						\
		inline static xhqm::string type_name() { return this_name; };					\
	private:							\
		virtual bool init_object() override	{ return true; };							\
	protected:							\
		inline static xhqm::size this_id = xhqm::object_info<object_type>::this_id();	\
		inline static xhqm::string this_name = XHQMTOSTR(object_type);					\
	static_assert(xhqm::is_same<child_type, object_type>, "xhqm::object<object_type> need xhqm_object(object_type)!!!");
}

#endif