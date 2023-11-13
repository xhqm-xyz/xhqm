#include "libmange.h"
#include "../pattern/instance.h"
namespace xhqm
{
    liblist::liblist() : std::vector<libid>() { }
    bool liblist::find(libid id)
    {
        if(!id) return false;
        for (auto& idit : (*this))
            if (id == idit)
                return true;
        return false;
    }



    libid libmange::loadlib(std::string libpath)
    {
        libid id = nullptr;
#ifdef _WIN32
        std::setlocale(LC_ALL, "chs"); //识别中文
        std::wstring wlibpath = std::filesystem::path(libpath).wstring();
        id = LoadLibrary(wlibpath.c_str());
#endif
#ifdef linux
        id = dlopen(libpath.c_str(), RTLD_LAZY);
#endif
        if (!xhqm::instance<xhqm::liblist>::get().find(id)) 
            xhqm::instance<xhqm::liblist>::get().push_back(id);
        return id;
    }

    void libmange::freelib(libid id)
    {
        if (!id) return;
        xhqm::liblist& liblist = xhqm::instance<xhqm::liblist>::get();
        for (auto iditer = liblist.begin(); iditer != liblist.end(); ++iditer)
        {
            if (id == (*iditer))
            {
                liblist.erase(iditer);
#ifdef _WIN32
                FreeLibrary((HINSTANCE)id);
                //FreeLibraryAndExitThread((HINSTANCE)id, 0);
                //该函数在kernel32.dll
#endif
#ifdef linux
                dlclose(id);
#endif
                return;
            }
        }
    }


    void libmange::freelibs()
    {
        xhqm::liblist liblist = xhqm::instance<xhqm::liblist>::get();
        std::size_t size = liblist.size();
        for (std::size_t s = 0; s < size; ++s)
            libmange::freelib(liblist[size - s - 1]);
    }


    xhqm::liblist libmange::liblist()
    {
        return xhqm::instance<xhqm::liblist>::get();
    }


    libfunptr libmange::getfunptr(libid id, std::string funname)
    {
#ifdef _WIN32
        return (void*)GetProcAddress((HINSTANCE)id, funname.c_str());
#endif
#ifdef linux
        return dlsym(id, funname.c_str());
#endif
    }

    void libmange::setdependpath(std::string dirpath)
    {
#ifdef _WIN32
        setlocale(LC_ALL, "chs"); //识别中文
        std::wstring wlibpath = std::filesystem::path(dirpath).wstring();
        SetDllDirectory(wlibpath.c_str());
#endif
#ifdef linux
        dirpath = dirpath.size() ? dirpath : dirpath;
#endif
    }


    liberror libmange::error()
    {
#ifdef _WIN32
        return GetLastError();
#endif
#ifdef linux
        return dlerror();
#endif
    }

}
