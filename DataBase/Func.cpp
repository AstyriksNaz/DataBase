#include "Func.h"

static class Timer {
public:
	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> durations = end - start;
		std::cout << "Duration\t" << durations.count() << " s";
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};


void save_data(std::vector<Student>& arr) {
	system("cls");
	std::cin.ignore(32767, '\n');

	std::thread t([&arr]() {	
		std::ofstream file(current_file, std::ios::out | std::ios::app);
	for (const Student& x : arr)
		file << x;
	file.close(); });

	std::cout << "\tAll data has been saved to the file" << std::endl;
	t.join();
	waitButton();
}

void file_clear() {
	std::ofstream file(current_file, std::ios::out | std::ios::trunc);
}

//show all data
void show_data(const std::vector<Student>& arr) {
	system("cls");
	std::cin.ignore(32767, '\n');

	if (arr.empty())
		std::cout << "Data base is empty." << std::endl;

	else {
		std::cout << std::left << std::setw(1) << '|' << std::setw(6) << "ID" << '|'
			<< std::setw(20) << "Name" << '|'
			<< std::setw(20) << "surname" << '|'
			<< std::setw(10) << "Groop" << '|'
			<< std::setw(5) << "Age" << '|'
			<< std::setw(5) << "GPA" << std::setw(5) << "|" << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;

		for (const auto& x : arr)
			show_data(x);
	}
}

//show only 1 student
void show_data(const Student& x) {
	std::cout.precision(3);
	std::cout << std::left << std::setw(1) << '|' << std::setw(6) << x.m_studentID << '|'
		<< std::setw(20) << x.m_name << '|'
		<< std::setw(20) << x.m_surname << '|'
		<< std::setw(10) << x.m_groop << '|'
		<< std::setw(5) << x.m_age << '|'
		<< std::setw(5) << x.m_GPA << '|' << std::endl;
}

void get_data_from_file(std::vector<Student>& arr) {
	system("cls");
	std::cin.ignore(32767, '\n');

	std::ifstream file(current_file, std::ios::in);
	if (file.peek() == std::ifstream::traits_type::eof()) 
		std::cout << current_file + " is empty!" << std::endl;
	else {
		Student temp;
		while (file >> temp) {
			bool exists = false;

			for (int i = 0; i < arr.size(); i++) {
				if (temp == arr[i]) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				arr.push_back(temp);
				++temp;
			}
		}

		file.close();
		std::cout << "Students:" << std::endl;
		show_data(arr);

	}
	waitButton();
}

void remove_all_data_from_file() {
	system("cls");
	std::cin.ignore(32767, '\n');

	file_clear();

	std::cout << "Data from file has been deleted." << std::endl;
	waitButton();
}

void remove_student(std::vector<Student>& arr) {
	system("cls");

	show_data(arr);

	int index;
	std::cout << "Enter student index needed to remove: " << std::endl;
	std::cin >> index;
	std::cin.ignore(32767, '\n');

	if (arr.size() == 1 || index == 1)
		arr.clear();
	else {
		if (index > arr.size() || index == 0) {
			std::cout << "Not have Student with this index" << std::endl;
			return;
		}

		std::vector<Student>::iterator it = arr.begin() + index - 1;
		arr.erase(it);

		arr[index - 1].EditID(index);		

		for (int i = index; i < arr.size(); ++i)
			arr[i].EditID(i + 1);

		arr.shrink_to_fit();
	}
	system("cls");
	std::cout << "Student's data base after remove student with ID: " << index << std::endl;

	show_data(arr);

	waitButton();
}

void add_data(std::vector<Student>& arr) {
	system("cls");
	std::cin.ignore(32767, '\n');
	std::string name;
	std::string surname;
	std::string groop;
	int age;
	float GPA;

	std::cout << "Enter student name: ";
	std::getline(std::cin, name);

	std::cout << "Enter student surname: ";
	std::getline(std::cin, surname);

	std::cout << "Enter student groop: ";
	std::getline(std::cin, groop);

	std::cout << "Enter student age: ";
	std::cin >> age;

	std::cout << "Enter student GPA: ";
	std::cin >> GPA;

	std::cin.ignore(32767, '\n');
	system("cls");

	arr.push_back(Student::Student(name, surname, groop, static_cast<size_t>(age), static_cast<float>(GPA)));
	std::cout << "\t\tAdded student: " << std::endl;

	show_data(arr.back());

	waitButton();
}

void remove_data_from_buffer(std::vector<Student>& arr) {
	system("cls");
	std::cin.ignore(32767, '\n');

	arr.clear();
	std::cout << "Your buffer is clear." << std::endl;

	waitButton();
}

//міняти
void editData(std::vector<Student>& arr) {
	system("cls");

	show_data(arr);

	std::cout << "\nEnter the student index whose data you want to correct: " << std::endl;
	int index;
	std::cin >> index;

	if (index < 0 || index > arr.size()) {
		std::cout << "EROOR: Index == 0 or Index > MaxIndex" << std::endl;
		return;
	}
	index--;
	std::cin.ignore(32767, '\n');

	std::cout << "What are you need to edit?\n1)Name\n2)surname\n3)Groop\n4)Year\n5)GPA\n6)All Data\n0)Exit" << std::endl;
	int value;
	std::cin >> value;
	std::cin.ignore(32767, '\n');
	system("cls");

	//buffers to new data
	std::string test;
	int newYear;
	float newGPA;

	//system of choose 
	switch (value) {
	case 0:
		return;
		break;
		//Name
	case 1:
		std::cout << "Enter new student name: " << std::endl;
		std::getline(std::cin, test);
		arr[index].EditName(test);
		std::cout << std::endl;
		break;
		//surname
	case 2:
		std::cout << "Enter new student surname: " << std::endl;
		std::getline(std::cin, test);
		arr[index].EditSurname(test);
		std::cout << std::endl;
		break;
		//Groop
	case 3:
		std::cout << "Enter new groop: " << std::endl;
		std::getline(std::cin, test);
		arr[index].EditGroop(test);
		std::cout << std::endl;
		break;
		//age
	case 4:
		std::cout << "Enter new student age: " << std::endl;
		std::cin >> newYear;
		std::cin.ignore(32767, '\n');
		arr[index].EditYear(newYear);
		std::cout << std::endl;;
		break;
		//GPA
	case 5:
		std::cout << "Enter new student name: " << std::endl;
		std::cin >> newGPA;
		std::cin.ignore(32767, '\n');
		arr[index].EditGPA(newGPA);
		std::cout << std::endl;
		break;
		//AllData
	case 6: 
		std::cout << "Enter new student name: " << std::endl;
		std::getline(std::cin, test);
		arr[index].EditName(test);
		std::cout << std::endl;

		std::cout << "Enter new groop: " << std::endl;
		std::getline(std::cin, test);
		arr[index].EditGroop(test);
		std::cout << std::endl;

		std::cout << "Enter new student age: " << std::endl;
		std::cin >> newYear;
		std::cin.ignore(32767, '\n');
		arr[index].EditYear(newYear);
		std::cout << std::endl;

		std::cout << "Enter new student name: " << std::endl;
		std::cin >> newGPA;
		std::cin.ignore(32767, '\n');
		arr[index].EditGPA(newGPA);
		std::cout << std::endl;
	break;
	default:
		std::cout << "Error";
		break;
	}

	system("cls");
	std::cout << "Edited student: " << std::endl;

	show_data(arr.at(index));
	waitButton();
}

//міняти
void sort(std::vector<Student>& arr) {
	system("cls");
	std::cin.ignore(32767, '\n');
	std::cout << "Choose sort metod: \n" <<
		"1)By ID\n2)By Name\n3)By Surname\n4)By Groop\n5)By Age\n6)By GPA\n0)Exit" << std::endl;
	int index = 0;
	std::cin >> index;
	switch (index)
	{
	case 1:
		for (int i = 0;i < arr.size(); i++)
			for (int j = 0; j < arr.size(); j++)
				if (arr.at(i).m_studentID < arr.at(j).m_studentID)
					std::swap(arr.at(i), arr.at(j));
		break;
	case 2:
		for (int i = 0;i < arr.size(); i++)
			for (int j = 0; j < arr.size(); j++)
				if (arr.at(i).m_name < arr.at(j).m_name)
					std::swap(arr.at(i), arr.at(j));
		break;
	case 3:
		for (int i = 0;i < arr.size(); i++)
			for (int j = 0; j < arr.size(); j++)
				if (arr.at(i).m_surname < arr.at(j).m_surname)
					std::swap(arr.at(i), arr.at(j));
		break;
	case 4:
		for (int i = 0;i < arr.size(); i++)
			for (int j = 0; j < arr.size(); j++)
				if (arr.at(i).m_groop < arr.at(j).m_groop)
					std::swap(arr.at(i), arr.at(j));
		break;
	case 5:
		for (int i = 0;i < arr.size(); i++)
			for (int j = 0; j < arr.size(); j++)
				if (arr.at(i).m_age < arr.at(j).m_age)
					std::swap(arr.at(i), arr.at(j));
		break;
	case 6:
		for (int i = 0;i < arr.size(); i++)
			for (int j = 0; j < arr.size(); j++)
				if (arr.at(i).m_GPA < arr.at(j).m_GPA)
					std::swap(arr.at(i), arr.at(j));
		break;
	}

	std::cout << "Student after sort:" << std::endl;

	show_data(arr);

	waitButton();
}

void logOutFile(bool & fileIsOpen) {
	current_file.clear();
	fileIsOpen = false;
}

void waitButton() {
	char input;
	std::cout << "Press Enter to continue..." << std::endl;
	input = getchar();
	if (input == '\n') {
		system("cls");
		return;
	}
}
