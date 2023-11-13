#ifndef XHQM_TOOL_LIBMANGE
#define XHQM_TOOL_LIBMANGE
#include "../head.h"
#include "filesys.h"
#ifdef _WIN32
#include <Windows.h>
#define ACTIONTAGE "xhqmAction"
#define LIBTAGE ".dll"
#define MAINPAGE "mainPage.dll"
#endif
#ifdef linux
#include<dlfcn.h>
#define ACTIONTAGE "libxhqmAction"
#define LIBTAGE ".so"
#define MAINPAGE "libmainPage.so"
#endif

namespace xhqm
{
    typedef void* libid;
    typedef void* libfunptr;
#ifdef _WIN32
        typedef DWORD  liberror;
#else
//#endif
//#ifdef linux
        typedef const char* liberror;
#endif

        class xhqmclass liblist
            : public std::vector<libid> 
        { 
        public:
            liblist();
            bool find(libid id);
        };

        class xhqmclass libmange
        {
        public:
            static libid loadlib(std::string libpath);
            static void freelib(libid id);
            static void freelibs();

            static xhqm::liblist liblist();
            static libfunptr getfunptr(libid id, std::string funname);
            static void setdependpath(std::string dirpath);
            static liberror error();

            template<class iffun> //bool iffun(std::string name)
            static xhqm::liblist loadlibs(std::string dirpath, iffun fun)
            {
                auto namelist = xhqm::filesys::file_list(dirpath);
                std::vector<std::string> select;
                for (auto& libname : namelist)
                    if(fun(libname)) select.push_back(dirpath + "/" + libname);
                for (auto& libpath : select) 
                    libmange::loadlib(libpath);
                return libmange::liblist();
            }
        };
}
#endif
