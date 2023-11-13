#pragma once
#ifndef XHQM_SOFTWARE_USER
#define XHQM_SOFTWARE_USER
#include "../head.h"
namespace xhqm
{
	//需加密的数据 需加密的数据长度 加密后的数据 加密后的数据长度 加密时额外需求的数据
	typedef void (*Encrypt)(byte*, inte, void*);

	//数据库结构
	// 
	// 数据量+明文管理+暗文密码+明文注释
	// 用户ID+明文用户+暗文密码+明文注释
	// 用户ID+明文用户+暗文密码+明文注释
	// 用户ID+明文用户+暗文密码+明文注释
	// 。。。
	//-----------------
	//| 8+128+128+256 |
	//| 8+128+128+256 |
	//| 8+128+128+256 |
	//| 8+128+128+256 |
	//|      ...      |
	//-----------------

	class xdatabase;

	struct xhqmclass xuser
	{
	protected:
		integer m_id = 0;
		byte userName[128];	//明文用户
		byte passWord[128];	//明文密码
		byte noteData[256];	//明文注释
		friend xdatabase;
	public:
		xuser()
		{
			m_id = 0;
			memset(noteData, 0, sizeof(byte) * 256);
			memset(passWord, 0, sizeof(byte) * 128);
			memset(userName, 0, sizeof(byte) * 128);
		}
		xuser(std::string name, std::string pass)
		{
			m_id = 0;
			memset(noteData, 0, sizeof(byte) * 256);
			memset(passWord, 0, sizeof(byte) * 128);
			memset(userName, 0, sizeof(byte) * 128);
			memcpy(passWord, pass.c_str(), pass.size());
			memcpy(userName, name.c_str(), name.size());
		}

		std::string UserName()
		{
			return (char*)userName;
		}
		std::string PassWord()
		{
			return (char*)passWord;
		}
		std::string NoteData()
		{
			return (char*)noteData;
		}

		void UserName(std::string name)
		{
			memcpy(userName, name.c_str(), name.size());
		}
		void PassWord(std::string pass)
		{
			memcpy(passWord, pass.c_str(), pass.size());
		}
		void NoteData(std::string note)
		{
			memcpy(noteData, note.c_str(), note.size());
		}
		integer GetID()
		{
			return m_id;
		}
	};

	class xhqmclass xdatabase
		: public xuser
	{
	public:
		xdatabase(std::string name, std::string pass, std::string path, Encrypt encrypt = nullptr)
		{
			dataPath = path;
			m_encrypt = encrypt;
			read();

			xuser admin = loginuser(name, pass);
			memcpy(noteData, admin.noteData, 256);
			memcpy(passWord, admin.passWord, 128);
			memcpy(userName, admin.userName, 128);
			m_id = admin.m_id;
		}
		xdatabase(xuser user, std::string path, Encrypt encrypt = nullptr)
		{
			dataPath = path;
			m_encrypt = encrypt;
			read();

			xuser admin = loginuser(user.UserName(), user.PassWord());
			memcpy(noteData, admin.noteData, 256);
			memcpy(passWord, admin.passWord, 128);
			memcpy(userName, admin.userName, 128);
			m_id = admin.m_id;
		}
		~xdatabase()
		{
			write();
			m_encrypt = nullptr;
		}
		void read();		//读取用户
		void write();		//更新用户

		bool is_admin();
		std::vector<std::string> listuser();//数据库数据
		xuser loginuser(std::string name, std::string pass);	//用户密码错误则查询失败

		bool adduser(xuser user);							//管理密码错误或已有此用户则增加失败
        bool subuser(natural n);								//管理密码错误或没有此用户则删除失败
		bool upuser(xuser olduser, xuser newuser);			//用户密码错误或没有此用户则更新失败

		static bool CreatNewDataBase(xuser admin, std::string path, Encrypt encrypt = nullptr);
	protected:
		std::string dataPath;//数据库位置
		std::vector<xuser> dataBase;//数据库数据
		Encrypt m_encrypt = nullptr;//加密函数
	};
}
#endif
