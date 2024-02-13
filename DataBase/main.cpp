#include "Student.h"
#include "Func.h"
#include "User.h"
#include <ctime>
#include <cstdlib>

/*
before before:

login ->reading data from file(unsfirt password) +
reg ->save users data to five(password shifr(ads == qwe (123))  -> fix bug with empty name or password +

before:
Create new file -> after (save file name in *userData.txt) +
Open file -> your files; (serch filename in *userData.txt) +
delete file -> enter file name(search file name in *userData.txt and after delete)  ->   create Usercatalog and save in Usercatalog new Userfile +
delete all files(delete all user files)+
exit +

After:
1:show data +
2:add data +
3:get data from file +
4:edit data +
5:remove data  +
6:save data +
7:remove data from buffer +
8:remove data from file +
9:sort -> sort by ID, sort by NAME, sort by SURNAME, sort by GROOP, sort by AGE, sort by GPA+
0:exit +

}*/

std::string current_file = "Data.txt";
std::string file_name;

/*

Перечитати весь код і нагатити коментарів 1 +-

Добавити email до User(зробити мінімальний розмір ніка, пароля і назви файлу) 2 +

Зробити всі приватні обєкти класа string і поміняти логіку 3

Зробити перевірки чи не пусті поля вводу(всюди) 4

Переробити sort 5

Додати move семантику до User і Student 6

поміняти логіку в User::save_data(щоб файл при створенні в масив зразу зразу зберігався у файл)
*/

bool fileIsOpen = false;

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	User obj;
	std::vector<Student> arr(1);
	int index = 1;

back:
	do {
		std::cout << "Welcome\n1)Login\n2)Register\n0)Close" << std::endl;
		std::cin >> index;
		switch (index) {
		case 0:
			return 0;
			break;
		case 1:
			UserData::Login(obj);
			break;
		case 2:
			UserData::Register(obj);
			break;
		default:
			break;
		}
	} while (!UserData::login_checker(obj));

	while (UserData::login_checker(obj)) {
		while (!fileIsOpen) {
			std::cout << "User:\t" << obj.getLogin() << "\nEmail:\t"  << obj.getEmail() <<
				"\n1)Create file\n2)Open file\n3)Show all files\n4)Delete File\n5)Delete User\n0)Exit" << std::endl;
			std::cin >> index;
			switch (index)
			{
			case 1:
				UserData::CreateFile(obj);
				break;
			case 2:
				UserData::openFile(obj, fileIsOpen, file_name);
				break;
			case 3:
				UserData::show_file_list(obj);
				break;
			case 4:
				UserData::delete_file(obj);
				break;
			case 5:
				UserData::delete_User(obj);
				obj.log_out_system();
				system("cls");
				goto back;
				break;
			case 0:
				UserData::log_out_system(obj);
				system("cls");
				goto back;
				break;
			default:

				break;
			}
		}

		while (index) {

			std::cout << "\tFile: " << file_name << std::endl;
			std::cout << "\tStudent Data Base" << std::endl;
			std::cout << "Select an action:" << std::endl;

			std::cout <<
				"1)Show Data\n" <<
				"2)Add Data\n" <<
				"3)Get data from file\n" <<
				"4)Edit Data\n" <<
				"5)Remove Data\n" <<
				"6)Save Data\n" <<
				"7)Sort\n" <<
				"8)Remove data from buffer\n" <<
				"9)Remove all data from file\n" <<
				"0)Exit(close file)" << std::endl;
			std::cin >> index;
	
			switch (index) {
			case 1:
				show_data(arr);
				waitButton();
				break;
			case 2:
				add_data(arr);
				break;
			case 3:
				get_data_from_file(arr);
				break;
			case 4:
				editData(arr);
				break;
			case 5:
				remove_student(arr);
				break;
			case 6:
				save_data(arr);
				break;
			case 7:
				sort(arr);
				break;
			case 8:
				remove_data_from_buffer(arr);
				break;
			case 9:
				remove_all_data_from_file();
				break;
			case 0:
				logOutFile(fileIsOpen);
				break;
			default:
				break;
			}
		}
		system("cls");
	}
	return 0;
}