#include "xuser.h"
namespace xhqm
{
	bool xdatabase::CreatNewDataBase(xuser admin, std::string path, Encrypt encrypt)
	{
		bool isCreat = false;
		byte password[128];
		memset(password, 0, sizeof(byte) * 128);
		memcpy(password, admin.passWord, 128);
		std::string PassWord = admin.PassWord();
		if (encrypt) encrypt(password, 128, &PassWord);
		FILE* dataBaseFile = fopen(path.c_str(), "wb");
		if (dataBaseFile)
		{
			integer size = 0;
			fwrite(&size, 8, 1, dataBaseFile);//数量
			fwrite(admin.userName, 128, 1, dataBaseFile);//管理
			fwrite(password, 128, 1, dataBaseFile);//密码
			fwrite(admin.noteData, 256, 1, dataBaseFile);//注释

			isCreat = true;
			fclose(dataBaseFile);//关闭文件
		}
		return isCreat;
	}

	void xdatabase::read()
	{
		dataBase.clear();
		natural len = 8 + 128 + 128 + 256;
		FILE* dataBaseFile = fopen(dataPath.c_str(), "rb");
		if (dataBaseFile)
		{
			xuser admin;
			fread(&admin, len, 1, dataBaseFile);
			integer size = admin.m_id;
			admin.m_id = 0;
			dataBase.push_back(admin);
			for (integer i = 0; i < size; i++)
			{
				xuser user;
				fread(&user, len, 1, dataBaseFile);
				dataBase.push_back(user);
			}
			fclose(dataBaseFile);
		}
	}

	void xdatabase::write()
	{
		natural len = 8 + 128 + 128 + 256;
		dataBase[0].m_id = dataBase.size() - 1;
		FILE* dataBaseFile = fopen(dataPath.c_str(), "wb");
		for (natural i = 0; i < dataBase.size(); i++)
		{
			xuser user = dataBase[i];
			fwrite(&user, len, 1, dataBaseFile);
		}
		fclose(dataBaseFile);
		dataBase.clear();
	}

	bool xdatabase::is_admin()
	{
		return m_id == 0;
		//m_id;		  //其他用户
		//m_id == 0;  //管理员
		//m_id == -1; //匿名
		//m_id == -2; //匿名

		//if (dataBase.size())
		//{
		//	byte password[128];
		//	memset(password, 0, sizeof(byte) * 128);
		//	memcpy(password, passWord, 128);
		//	std::string PassWord = this->PassWord();
		//	if (m_encrypt) m_encrypt(password, 128, &PassWord);

		//	bool isuser = ((std::string)(char*)userName) == ((std::string)(char*)dataBase[0].userName);
		//	bool ispass = ((std::string)(char*)password) == ((std::string)(char*)dataBase[0].passWord);
		//	return isuser && ispass;
		//}
		//return false;	
	}

	std::vector<std::string> xdatabase::listuser()
	{
		std::vector<std::string> users;
		for (natural i = 0; i < dataBase.size(); i++)
		{
			users.push_back(dataBase[i].UserName());
		}
		return users;
	}

	xuser xdatabase::loginuser(std::string name, std::string pass)
	{
		inte len = 128;
		byte data[128] = {0};
		xuser user(name, pass);
		user.m_id = -1;//没有此用户
		for (natural i = 0; i < dataBase.size(); i++)
		{
			if (user.UserName() == dataBase[i].UserName())
			{
				user.m_id = -2;//密码错误
				memcpy(data, user.passWord, 128);
				if (m_encrypt) m_encrypt(data, len, &pass);
				if (((std::string)(char*)data) == dataBase[i].PassWord())
				{
					user.m_id = dataBase[i].m_id;
					user.NoteData(dataBase[i].NoteData());
					break;
				}
			}
		}
		return user;
	}

	bool xdatabase::adduser(xuser user)
	{
		if (is_admin())
		{
			xuser find = loginuser(user.UserName(), user.PassWord());
			if (find.m_id == -1)//不会有重复用户
			{
				find.m_id = dataBase[dataBase.size() - 1].m_id + 1;
				std::string PassWord = find.PassWord();
				if (m_encrypt) m_encrypt(find.passWord, 128, &PassWord);
				find.NoteData(user.NoteData());
				dataBase.push_back(find);
				return true;
			}
		}
		return false;
	}

    bool xdatabase::subuser(natural n)
	{
		if (is_admin() && 0 < n && n < dataBase.size())
		{
			auto it = dataBase.begin() + n;
			dataBase.erase(it);
			return true;
		}
		return false;
	}

	bool xdatabase::upuser(xuser olduser, xuser newuser)
	{
		xuser user = loginuser(olduser.UserName(), olduser.PassWord());
		xuser find = loginuser(newuser.UserName(), newuser.PassWord());
		if (
			(user.m_id != -1 && user.m_id != -2) &&								//验证成功且
			(find.m_id == -1 || newuser.UserName() == olduser.UserName()))		//无重名用户
		{
			for (natural i = 0; i < dataBase.size(); i++)
			{
				if (user.m_id == dataBase[i].m_id)
				{
					newuser.m_id = user.m_id;
					dataBase[i] = newuser;
					std::string PassWord = dataBase[i].PassWord();
					if (m_encrypt) m_encrypt(dataBase[i].passWord, 128, &PassWord);
					return true;
				}
			}
		}
		return false;
	}
}
