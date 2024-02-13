#include "User.h"

static const std::string _USERFILE = "UsersData.txt";
//to create users files
static const std::string _FILE_POST_FIX = "File.txt";
//to create users files list
static const std::string USERS_FILES_DATA_FILE = "PersonalFilesLists/";
//to create users files in persnal catalog
static const std::string USERS_FILES_DIRECTORY = "PersonalsDataFiles/";

//class methods and operators
#pragma region Class
	
	User::User() {
		setLogin([]() -> std::string {
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			const std::string LOGINS[] = {
				"BlueSkyTraveler",
				"MusicLover23",
				"AdventureSeeker77",
				"TechGeek2020",
				"CoffeeAddict45",
				"FitnessFanatic88",
				"NatureExplorer12",
				"Bookworm2000",
				"FoodieDelight",
				"ArtisticSoul123"
			};
			return LOGINS[std::rand() % 9];
			}());

		setPassword([]() -> std::string {
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			std::string _password;
			const char CHARACTERS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
			for (short i = 0; i < 16; i++)
				_password += CHARACTERS[rand() % 62]; // змінено 63 на 62
			return _password;
			}());

		setEmail([]() -> std::string {
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			const std::string EMAILS[] = {
				"john.smith",
				"emily.davis",
				"michael.jones",
				"sarah.wilson",
				"david.brown",
				"laura.taylor",
				"james.jackson",
				"olivia.anderson",
				"robert.thomas",
				"emma.white"
			};
			return EMAILS[std::rand() % 9] + "@gmail.com"; // виправлено помилку
			}());
	}

	//User's setters and getters
#pragma region setters&getters
	inline void User::setLogin(const std::string& _login) { this->m_Login = _login; }
	inline void User::setEmail(const std::string& _email) { this->m_email = _email; }
	inline void User::setPassword(const std::string& _password) { this->m_Password = _password; }


	inline std::string User::getLogin() const { return this->m_Login; }
	inline std::string User::getEmail() const { return this->m_email; }
	inline std::string User::getPassword() const { return this->m_Password; }
	inline std::vector<std::string>& User::getFiles() { return this->m_files; }

#pragma endregion setters&getters

	User::User(const User& other) {
		this->m_Login = other.m_Login;
		this->m_email = other.m_email;
		this->m_Password = other.m_Password;
		this->m_files = other.m_files;
	}

	void User::log_out_system() {
		this->m_Login.clear();
		this->m_email.clear();
		this->m_Password.clear();
		this->m_files.clear();
	}

	//User's operator overloads
#pragma region operatorOverloads

	bool User::operator==(const User& other) const{
		return (other.m_Login == this->m_Login) && (other.m_email == this->m_email) && (other.m_Password == this->m_Password);
	}

	bool User::operator!=(const User& other) const { return !(*this == other); }

	std::ostream& operator<<(std::ostream& on, const User& obj) {
		return on << obj.m_Login << ' ' << obj.m_email << ' ' << obj.m_Password << std::endl;
	}
	std::istream& operator>>(std::istream& in, User& obj) {
		return in >> obj.m_Login >> obj.m_email >> obj.m_Password;
	}

	User& User::operator=(const User& other) {
		this->m_Login = other.m_Login;
		this->m_email = other.m_email;
		this->m_Password = other.m_Password;
		this->m_files = other.m_files;
		return *this;
	}
#pragma endregion operatorOverloads

	inline void User::addfile(const std::string& _fileName) { 
		this->m_files.push_back(_fileName);
	}
#pragma endregion Class


namespace UserData {

#pragma region LoginSystem

		bool UserData::login_checker(User& obj) {
			std::fstream file(_USERFILE, std::ios::in | std::ios::app);
			User temp;

			while (file >> temp)
				if (temp == obj) {
					file.close();
					return true;
				}
			file.close();
			return false;
		}

		//міняв чат
		void UserData::Login(User& obj)	{
			system("cls");
			std::cin.ignore(32767, '\n');

			if (!login_checker(obj)) {
				std::string temp;

				std::cout << "---------------Login----------------" << std::endl;
				std::cout << "Enter Login: ";
				std::getline(std::cin, temp);
				obj.setLogin(myTrim::trim_copy(temp));

				std::cout << "Enter email(*@gmail.com): ";
				std::getline(std::cin, temp);
				obj.setEmail(myTrim::trim_copy(temp));

				std::cout << "Enter Password: ";
				std::getline(std::cin, temp);
				obj.setPassword(myTrim::trim_copy(temp));

				std::fstream file(_USERFILE, std::ios::in);
				User buffer;
				bool complete = false;
				while (file >> buffer && !complete) {
					if (buffer == obj)
						complete = true;
				}

				file.close();
				if (complete) {
					std::cout << "Congratulations, login successful!" << std::endl;

					std::string fpath = USERS_FILES_DATA_FILE + obj.getLogin() + _FILE_POST_FIX;
					file.open(fpath, std::ios::in);

					std::string name;
					while (file >> name)
						obj.addfile(name);

					file.close();
				}
				else
					std::cout << "User isn't found" << std::endl;
			}
			else
				std::cout << "Congratulations, login successful!" << std::endl;

			std::cin.ignore(32767, '\n');

			waitButton();
		}

		//міняв чат
		void UserData::Register(User& obj) {
			system("cls");
			std::cin.ignore(32767, '\n');

			bool ready = false;

			std::cout << "---------------Registration--------------" << std::endl;
			while (true) {
				User temp;
				for (std::string tLogin; tLogin.empty(); ) {
					bool isInvalible = false;
					std::cout << "Enter your Login(minimal length " + std::to_string(_MIN_LOGIN_LENGTH) + " characters): ";
					std::getline(std::cin, tLogin);

					myTrim::trim(tLogin);
					if (tLogin.empty() || tLogin.size() < _MIN_LOGIN_LENGTH) {
						std::cout << "Your name is empty or login too small!!!" << std::endl;
						tLogin.clear();
						continue;
					}

					std::fstream file(_USERFILE, std::iostream::in);
					User toCheck;
					while (file >> toCheck) {
						if (toCheck.getLogin() == tLogin) {
							std::cout << "Login is unavailable!!!" << std::endl;
							isInvalible = true;
							tLogin.clear();
							break;
						}
					}
					file.close();
					if (!isInvalible)
						temp.setLogin(tLogin);
				}

				for (std::string tEmail; tEmail.empty();) {
					std::cout << "Enter email(*@gmail.com): ";
					std::getline(std::cin, tEmail);
					myTrim::trim(tEmail);

					bool isInvalid = false;
					if (tEmail.empty()) {
						std::cout << "Email is empty!!!\tTry again!" << std::endl;
						tEmail.clear();
						continue;
					}
					else if (tEmail.find("@gmail.com") == std::string::npos) {
						std::cout << "It's not an email!" << std::endl;
						tEmail.clear();
						continue;
					}

					else {
						std::fstream file(_USERFILE, std::iostream::in);
						while (!file.eof() && !isInvalid) {
							User toCheck;
							file >> toCheck;
							if (tEmail == toCheck.getEmail()) {
								std::cout << "Email is invalible!" << std::endl;
								tEmail.clear();
								isInvalid = true;
								break;
							}
						}

						file.close();
						if (!isInvalid) {
							temp.setEmail(tEmail);
							break;
						}
					}

				}
				//start password getter
				for (std::string tPassword; tPassword.empty();) {
					std::cout << "Enter your Password(minimal length " + std::to_string(_MIN_PASSWORD_LENGTH) + " characters): ";
					std::getline(std::cin, tPassword);
					myTrim::trim(tPassword);

					if (tPassword.empty() || tPassword.size() < _MIN_PASSWORD_LENGTH) {
						std::cout << "Password is empty or too small!" << std::endl;
						tPassword.clear();
						continue;
					}
					else if (tPassword == temp.getLogin()) {
						std::cout << "Password isn't equal login" << std::endl;
						tPassword.clear();
						continue;
					}

					std::string passwordChecker;
					do {
						std::cout << "Confirm your password: ";
						std::getline(std::cin, passwordChecker);
						myTrim::trim(passwordChecker);

						if (passwordChecker != tPassword) {
							std::cout << "Password isn't equal to the confirmed password!!!" << std::endl;
							passwordChecker.clear();
						}
					} while (passwordChecker != tPassword);

					temp.setPassword(tPassword);
				}
				//end password getter


				system("cls");

				std::cout << "Your Login: \t" << temp.getLogin() << "\nYour email: \t" << temp.getEmail() << "\nYour password: \t" << temp.getPassword();
				std::cout << "\nDo You want to change data?\n1)Yes\n2)No" << std::endl;

				int index;
				std::cin >> index;
				if (index == 1) {
					std::cin.ignore(32767, '\n');

					ready = false;
					system("cls");
					continue; // Restart registration process
				}
				else {
					std::thread save([&temp]() {
						UserData::save_data(temp);

						std::string PersonalFile = USERS_FILES_DATA_FILE + temp.getLogin() + _FILE_POST_FIX;
						std::fstream file(PersonalFile, std::ios::out);
						std::filesystem::create_directory(USERS_FILES_DIRECTORY + temp.getLogin());
						});

					std::cin.ignore(32767, '\n');
					save.join();
					waitButton();
				}
				break; // Exit the loop if registration is successful
			}
		}

#pragma endregion LoginSystem

		//міняв чат
		void openFile(User& obj, bool& value, std::string& file_name) {
			system("cls");
			std::cin.ignore(32767, '\n');

			std::cout << "Your files list: " << std::endl;


			if (obj.getFiles().empty())
				std::cout << "You do not have any files!" << std::endl;
			else {
				int i = 1;
				int index = 0;
				std::vector<std::string> arr = obj.getFiles();

				for (const std::string& x : arr)
					std::cout << i++ << ')' << x << std::endl;
				std::cout << "Enter the file index that you want to open: ";

				while (true) {
					std::cin >> index;
					if (index > arr.size() || index <= 0) {
						std::cout << "Invalid index! Please try again: ";
						continue;
					}

					std::fstream file(USERS_FILES_DIRECTORY + obj.getLogin() + '/' + arr.at(index - 1), std::ios::out | std::ios::app);
					file.close();

					current_file = USERS_FILES_DIRECTORY + obj.getLogin() + '/' + arr.at(index - 1);
					file_name = arr.at(index - 1);
					std::cout << "File has been opened" << std::endl;

					std::cin.ignore(32767, '\n');
					value = true;
					break;
				}
			}
			waitButton();
		}

		void show_file_list(User& obj) {
			system("cls");
			std::cin.ignore(32767, '\n');
			std::cout << "Your files list: " << std::endl;
			if (obj.getFiles().empty())

				std::cout << "You are not have files!" << std::endl;
			else {
				int i = 1;
				std::vector<std::string> arr = obj.getFiles();
				for (const std::string& x : arr)
					std::cout << i++ << ')' << x << std::endl;

				std::cin.ignore(32767, '\n');
			}
			waitButton();
		}

		//міняв чат
		void CreateFile(User& obj) {
			system("cls");
			if (!login_checker(obj)) {
				std::cout << "User isn't found! Login or register in system :)" << std::endl;
				return;
			}

			//enter file name
			std::cin.ignore(32767, '\n');
			std::string file_name;

			while (file_name.empty() || (file_name.size() > _MIN_FILENAME_LENGTH))
			{
				std::cout << "Enter the file name that you want to set name the file(Minimal name length is " + std::to_string(_MIN_FILENAME_LENGTH) + " characters): ";
				std::getline(std::cin, file_name);
				myTrim::trim(file_name);
				if (file_name.empty() || (file_name.size() < _MIN_FILENAME_LENGTH))
				{
					std::cout << "File name is empty or too small" << std::endl;
					file_name.clear();
				}
			}

			//add file to vector filename
			obj.addfile(file_name += _FILE_POST_FIX);

			//create path to save data
			std::string filePath = USERS_FILES_DATA_FILE + obj.getLogin() + '/' + obj.getLogin() + _FILE_POST_FIX;

			//clear file
			std::fstream file(filePath, std::ios::trunc | std::ios::out);
			file.close();

			//save in the file a name list
			file.open(filePath, std::ios::app | std::ios::out);
			std::vector<std::string> arr(obj.getFiles());

			for (const std::string& x : arr)
				file << x;
			file.close();

			std::cout << "Your file has been created successful" << std::endl;

			std::cin.ignore(32767, '\n');
			waitButton();
		}

		//міняв чат
		void delete_file(User& obj)
		{
			system("cls");
			std::cin.ignore(32767, '\n');
			std::cout << "Your files list: " << std::endl;

			if (obj.getFiles().empty())
				std::cout << "You do not have any files!" << std::endl;

			else {
				std::vector<std::string> arr = obj.getFiles();
				int index = 0;

				for (size_t i = 0; i < arr.size(); ++i)
					std::cout << i + 1 << ") " << arr[i] << std::endl;

				std::cout << "Enter the file index that you want to delete (Press 0 to exit): ";

				while (true) {
					std::cin >> index;
					if (index)
						break;

					else if (index > arr.size() || index < 0) {
						std::cout << "Invalid index! Please try again: ";
						continue;
					}

					index--;
					std::string temp = USERS_FILES_DIRECTORY + obj.getLogin() + '/' + arr[index];
					std::remove(temp.c_str());

					obj.getFiles().erase(obj.getFiles().begin() + index);

					// Create path to save data
					std::string filePath = USERS_FILES_DATA_FILE + obj.getLogin() + _FILE_POST_FIX;

					// Clear file
					std::fstream file(filePath, std::ios::trunc | std::ios::out);
					file.close();

					// Save the updated file list
					file.open(filePath, std::ios::app | std::ios::out);
					for (const std::string& x : obj.getFiles())
						file << x;
					file.close();

					std::cout << "Your file has been deleted." << std::endl;
					break;
				}
			}

			waitButton();
		}

		//міняв чат
		void delete_User(User& obj) {
			system("cls");
			std::cout << "Are you sure?\n1)Yes\n2)No" << std::endl;
			int index = 0;
			std::cin >> index;

			if (index == 1) {
				std::fstream file(_USERFILE, std::ios::in | std::ios::app);
				User temp;
				bool UserHasCreated = false;

				// Check if the user exists
				while (file >> temp && !UserHasCreated)
					if (temp == obj)
						UserHasCreated = true;

				file.close();

				if (!UserHasCreated)
					std::cout << "User not found (not registered or you are not logged in)." << std::endl;
				else {

					//переглянути ще раз

					// Delete all files from the user's directory
					std::vector<std::string> toDelete = obj.getFiles();
					for (const std::string& fileName : toDelete)
						std::remove((USERS_FILES_DIRECTORY + obj.getLogin() + '/' + fileName).c_str());

					// Delete the user's directory
					std::filesystem::remove(USERS_FILES_DIRECTORY + obj.getLogin());

					// Clear the user's files list
					obj.getFiles().clear();

					// Delete the user's file list file
					std::remove((USERS_FILES_DATA_FILE + obj.getLogin() + _FILE_POST_FIX).c_str());

					// Rewrite the user file without the deleted user
					std::vector<User> arr;
					file.open(_USERFILE, std::ios::in | std::ios::app);
					while (file >> temp)
						if (temp != obj)
							arr.push_back(temp);

					file.close();

					// Clear the user file
					file.open(_USERFILE, std::ios::out | std::ios::trunc);
					file.close();

					// Save the updated user list
					file.open(_USERFILE, std::ios::out | std::ios::app);
					for (const User& user : arr)
						file << user;
					file.close();

					std::cout << "User has been deleted successfully!" << std::endl;
				}
			}

			std::cin.ignore(32767, '\n');
			waitButton();
		}

		void log_out_system(User& obj) {
			std::fstream file(USERS_FILES_DATA_FILE + obj.getLogin() + _FILE_POST_FIX, std::ios::trunc | std::ios::out);
			file.close();

			file.open(USERS_FILES_DATA_FILE + obj.getLogin() + _FILE_POST_FIX, std::ios::app | std::ios::out);
			std::vector<std::string> arr = obj.getFiles();

			for (const std::string& x : arr)
				file << x << std::endl;
			file.close();

			obj.log_out_system();
		}

		void save_data(User& object) {
			std::fstream file(_USERFILE, std::ios::app | std::iostream::out);
			file << object;
		}
}

