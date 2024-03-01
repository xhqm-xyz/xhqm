#ifndef XHQM_FUNCTIONAL
#define XHQM_FUNCTIONAL
#include "../head.h"
#include "template.h"
#include "symbols_has.h"
#include <functional>

namespace xhqm 
{
    //函数封装
    template <class _return_type, class... _args_type>
    struct _ret_function_args {
        using std_tuple = std::tuple<_args_type...>;
        virtual _return_type call(_args_type&& ...) const = 0;
        _return_type operator()(_args_type ...values) const { return call(std::forward<_args_type>(values)...); };
    };

    //函数解析
    template <class type>
    struct ret_function_args {
        static_assert(xhqm::always_false<type>, "that is not function.");
    };

    template <class _return_type, class... _args_type>
    struct ret_function_args<_return_type(_args_type...)>
        : public xhqm::_ret_function_args<_return_type, _args_type...>
    {
        using class_type = void;
        using return_type = _return_type;
        using function_ptr = _return_type(*)(_args_type...);
        using function_std = std::function<_return_type(_args_type...)>;
        using function_type = function_ptr;

        constexpr static bool is_const = false;
        constexpr static bool is_normal = true;
        constexpr static bool is_member = !is_normal;

        virtual _return_type call(_args_type&& ...values) const override
        {
            return _function_type_ptr(std::forward<_args_type>(values)...);
        }
    protected:
        function_type _function_type_ptr = nullptr;
    };

    template <class _return_type, class... _args_type>
    struct ret_function_args<_return_type(*)(_args_type...)>
        : public xhqm::_ret_function_args<_return_type, _args_type...>
    {
        using class_type = void;
        using return_type = _return_type;
        using function_ptr = _return_type(*)(_args_type...);
        using function_std = std::function<_return_type(_args_type...)>;
        using function_type = function_ptr;

        constexpr static bool is_const = false;
        constexpr static bool is_normal = true;
        constexpr static bool is_member = !is_normal;

        virtual _return_type call(_args_type&& ...values) const override
        {
            return _function_type_ptr(std::forward<_args_type>(values)...);
        }
    protected:
        function_type _function_type_ptr = nullptr;
    };

    template <class _class_type, class _return_type, class... _args_type>
    struct ret_function_args<_return_type(_class_type::*)(_args_type...)>
        : public xhqm::_ret_function_args<_return_type, _class_type*, _args_type...>
    {
        using class_type = _class_type;
        using return_type = _return_type;
        using function_ptr = _return_type(_class_type::*)(_args_type...);
        using function_std = std::function<_return_type(_class_type*, _args_type...)>;
        using function_type = function_ptr;

        constexpr static bool is_const = false;
        constexpr static bool is_normal = false;
        constexpr static bool is_member = !is_normal;

        virtual _return_type call(_class_type*&& object_ptr, _args_type&& ...values) const override
        {
            return (object_ptr->*_function_type_ptr)(std::forward<_args_type>(values)...);
        }
    protected:
        function_type _function_type_ptr = nullptr;
    };

    template <class _class_type, class _return_type, class... _args_type>
    struct ret_function_args<_return_type(_class_type::*)(_args_type...) const>
        : public xhqm::_ret_function_args<_return_type, _class_type*, _args_type...>
    {
        using class_type = _class_type;
        using return_type = _return_type;
        using function_ptr = _return_type(_class_type::*)(_args_type...) const;
        using function_std = std::function<_return_type(_class_type*, _args_type...)>;
        using function_type = function_ptr;

        constexpr static bool is_const = true;
        constexpr static bool is_normal = false;
        constexpr static bool is_member = !is_normal;

        virtual _return_type call(_class_type*&& object_ptr, _args_type&& ...values) const override
        {
            return (object_ptr->*_function_type_ptr)(std::forward<_args_type>(values)...);
        }
    protected:
        function_type _function_type_ptr = nullptr;
    };


    //函数接口
    template <class func_type>
    class function : public xhqm::ret_function_args<func_type>
    {
    public:
        using class_type = typename xhqm::ret_function_args<func_type>::class_type;
        using return_type = typename xhqm::ret_function_args<func_type>::return_type;
        using function_ptr = typename xhqm::ret_function_args<func_type>::function_ptr;
        using function_std = typename xhqm::ret_function_args<func_type>::function_std;
        using function_type = typename xhqm::ret_function_args<func_type>::function_type;
        operator bool() { return xhqm::ret_function_args<func_type>::_function_ptr; };
        //function(function&& function) = default;
        //function(const function&) noexcept = default;
        function(const function_ptr& function_type_ptr = nullptr) noexcept
        {
            this->_function_type_ptr = function_type_ptr;
        }
        template <class class_function> function(const class_function&) noexcept
        {
            this->_function_type_ptr = &class_function::operator();
        }
    };

    //推导指引
    template <typename type, typename is_void = void> struct function_type_s
    {
        using function_type = type; function_type_s() = delete;
    };
    template <typename type> struct function_type_s<type, std::void_t<decltype(&type::operator())>>
    {
        using function_type = decltype(&type::operator()); function_type_s() = delete;
    };
    template <class type> function(type) -> function<typename xhqm::function_type_s<type>::function_type>;
}
#endif
