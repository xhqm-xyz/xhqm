#include "filesys.h"
namespace xhqm
{
	bool filesys::is_dir(const std::string& strpath)
    {
        std::filesystem::path path = strpath;
        if (std::filesystem::exists(path))
        {
            return std::filesystem::is_directory(path);
        }
        return false;
    }    
    bool filesys::is_file(const std::string& strpath)
    {
        std::filesystem::path path = strpath;
        if (std::filesystem::exists(path))
        {
            return !std::filesystem::is_directory(path);
        }
        return false;
    }
    bool filesys::is_exists(const std::string& strpath)
    {
        return std::filesystem::exists(strpath);
    }
    std::vector<std::string> filesys::dir_list(const std::string& strdirpath)
    {
        std::vector<std::string> list;
        if (is_dir(strdirpath))
        {
            std::filesystem::directory_iterator dirite(strdirpath);
            for (auto& ite : dirite)
                if (ite.status().type() == std::filesystem::file_type::directory) //is dir
                    list.push_back(ite.path().string());
        }
        return list;
    }
    std::vector<std::string> filesys::file_list(const std::string& strdirpath)
    {
        std::vector<std::string> list;
        if (is_dir(strdirpath))
        {
            std::filesystem::directory_iterator dirite(strdirpath);
            for (auto& ite : dirite)
                if (ite.status().type() == std::filesystem::file_type::regular) //is file
                    list.push_back(ite.path().filename().string());
        }
        return list;
    }
    std::vector<std::string> filesys::path_list(const std::string& strdirpath)
    {
        std::vector<std::string> list;
        std::vector<std::string> temp;
        temp = dir_list(strdirpath);
        list.insert(list.end(), temp.begin(), temp.end());
        temp = file_list(strdirpath);
        list.insert(list.end(), temp.begin(), temp.end());
        return list;
    }
    bool filesys::rename(const std::string& oldpath, const std::string& newpath)
    {
        if (std::filesystem::exists(oldpath) && !std::filesystem::exists(newpath))
        {
            std::filesystem::rename(oldpath, newpath);
            return true;
        }
        return false;
    }
    bool filesys::move_dir(const std::string& oldpath, const std::string& newpath)
    {
        if (is_dir(oldpath) && !std::filesystem::exists(newpath))
        {
            std::filesystem::rename(oldpath, newpath);
            return true;
        }
        return false;
    }
    bool filesys::move_file(const std::string& oldpath, const std::string& newpath)
    {
        if (is_file(oldpath) && !std::filesystem::exists(newpath))
        {
            std::filesystem::rename(oldpath, newpath);
            return true;
        }
        return false;
    }
    bool filesys::copy_dir(const std::string& oldpath, const std::string& newpath)
    {
        if (is_dir(oldpath) && !std::filesystem::exists(newpath))
        {
            std::filesystem::copy(oldpath, newpath);
            return true;
        }
        return false;
    }
    bool filesys::copy_file(const std::string& oldpath, const std::string& newpath)
    {
        if (is_file(oldpath) && !std::filesystem::exists(newpath))
        {
            return std::filesystem::copy_file(oldpath, newpath);
        }
        return false;
    }
    bool filesys::creat_dir(const std::string& strpath)
    {
        std::filesystem::path path = strpath;
        if (!std::filesystem::exists(path))
        {
            return std::filesystem::create_directory(path);
        }
        return false;
    }
    bool filesys::creat_file(const std::string& strpath)
    {
        std::filesystem::path path = strpath;
        if (!std::filesystem::exists(path))
        {
            std::fstream file(path, std::ios::binary);
            file.close();
            return true;
        }
        return false;
    }
    bool filesys::delete_dir(const std::string& strpath)
    {
        if (is_dir(strpath))
        {
            std::filesystem::remove_all(strpath);
            return true;
        }
        return false;
    }
    bool filesys::delete_file(const std::string& strpath)
    {
        if (is_file(strpath))
        {
            std::filesystem::remove(strpath);
            return true;
        }
        return false;
    }
    std::string filesys::current_path()
    {
        return std::filesystem::current_path().string();
    }
}