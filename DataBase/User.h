#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "Student.h"
#include "func.h"
#include "trim.h"

extern std::string current_file;
const size_t _MIN_LOGIN_LENGTH = 8U;
const size_t _MIN_PASSWORD_LENGTH = 8U;
const size_t _MIN_FILENAME_LENGTH = 8U;

#pragma warning(disable: 26495)

class User
{
private:
	std::string m_Login;
	std::string m_email;
	std::string m_Password;
	std::vector<std::string> m_files;

public:
	User();
	User(const std::string& _Login, const std::string& _Password, const std::string & _email) : m_Login(_Login), m_Password(_Password), m_email(_email) {};

	inline void setLogin(const std::string& _login);
	inline void setPassword(const std::string& _password);
	inline void setEmail(const std::string& _email);
	inline void addfile(const std::string& _fileName);

	inline std::string getLogin() const;
	inline std::string getPassword() const;
	inline std::vector<std::string>& getFiles();
	inline std::string getEmail() const;
	void log_out_system();

	User(const User& other);

	~User() = default;

public:
	friend std::ostream& operator<<(std::ostream& on, const User& obj);
	friend std::istream& operator>>(std::istream& in, User& obj);
	User& operator=(const User& other);

	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;
};

namespace UserData {
	//first setings
	void Login(User& obj);
	void Register(User& obj);

	//second setings
	void openFile(User& obj, bool& value, std::string &file_name);
	void show_file_list(User& obj);
	void CreateFile(User& obj);
	void delete_file(User& obj);
	void delete_User(User& obj);
	void save_data(User& obj);
	void log_out_system(User& obj);
	bool login_checker(User& obj);
}