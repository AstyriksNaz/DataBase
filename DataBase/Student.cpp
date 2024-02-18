#include "Student.h"


#pragma region constructors

Student::Student(const std::string& _name, const std::string& _surname, const std::string& _group, const size_t& _age, const float& _GPA) {
	++s_count;
	this->m_studentID = s_count;
	this->m_name = _name;
	this->m_surname = _surname;
	this->m_group = _group;
	this->m_GPA = std::to_string(_GPA);
	this->m_age = std::to_string(_age);
}

Student::Student(const std::string& _name, const std::string& _surname, const std::string& _group, const std::string& _age, const float& _GPA) {
	++s_count;
	this->m_studentID = s_count;
	this->m_name = _name;
	this->m_surname = _surname;
	this->m_group = _group;
	this->m_GPA = std::to_string(_GPA);
	this->m_age = _age;
}

Student::Student(const std::string& _name, const std::string& _surname, const std::string& _group, const size_t& _age, const std::string& _GPA) {
	++s_count;
	this->m_studentID = s_count;
	this->m_name = _name;
	this->m_surname = _surname;
	this->m_GPA = _GPA;
	this->m_group = _group;
	this->m_age = std::to_string(_age);
}

Student::Student(const std::string& _name, const std::string& _surname, const std::string& _group, const std::string& _age, const std::string& _GPA) {
	++s_count;
	this->m_studentID = s_count;
	this->m_name = _name;
	this->m_surname = _surname;
	this->m_GPA = _GPA;
	this->m_group = _group;
	this->m_age = _age;
}

Student::Student() {
	const std::string _NAME[] = { "Nazarii", "Denus", "Roman", "Victoria", "Liza", "Vitalik" };
	const std::string _surname[] = { "Pupkin", "Mercury", "Benninghton", "Veider", "Pukalack" };
	const std::string _GROOP[] = { "PC-32", "PC-31", "EK-32", "EK-31", "PC-21" };

	auto f = [](float _min, float _max) {

		std::random_device rd; // Розподільник випадкових чисел у діапазоні [min, max]
		std::uniform_real_distribution<float> dist(_min, _max); // Генеруємо випадкове число
		return dist(rd);
		};

	++s_count;
	this->m_studentID = s_count;
	this->m_name = _NAME[std::rand() % 6];
	this->m_surname = _surname[std::rand() % 5];
	this->m_GPA = f(3.0f, 5.0f);
	this->m_group = _GROOP[std::rand() % 4];
	this->m_age = std::to_string(static_cast<int>(f(16, 19)));
}

#pragma endregion constructors



#pragma region setters&getters

 void Student::EditName(const std::string& _name) { this->m_name = _name; }
 void Student::EditSurname(const std::string& _surname) { this->m_surname = _surname; }
 void Student::EditYear(const std::string&_age) { this->m_age = _age; }

 void Student::EditGroop(const std::string& _group) { this->m_group = _group; }
 void Student::EditGPA(const std::string& _GPA) { this->m_GPA = _GPA; }
 void Student::EditID(const int& _ID) { this->m_studentID = _ID; }

#pragma endregion setters&getters;

Student::Student(const Student& other) {
	++s_count;
	this->m_studentID = other.m_studentID;
	this->m_name = other.m_name;
	this->m_surname = other.m_surname;
	this->m_age = other.m_age;
	this->m_GPA = other.m_GPA;
	this->m_group = other.m_group;
}

Student& Student::operator=(const Student& other) {
	this->m_studentID = other.m_studentID;
	this->m_name = other.m_name;
	this->m_surname = other.m_surname;
	this->m_age = other.m_age;
	this->m_GPA = other.m_GPA;
	this->m_group = other.m_group;
	return *this;
}

int Student::s_count = 0;

Student::~Student() { --s_count; }

//operators to cout and cin data in file and console
std::istream& operator>>(std::istream& in, Student& obj) {
	in >> obj.m_studentID;
	in >> obj.m_name;
	in >> obj.m_surname;
	in >> obj.m_group;
	in >> obj.m_age;
	in >> obj.m_GPA;
	return in;
}


std::ostream& operator<<(std::ostream& ou, const Student& obj) {
	ou << obj.m_studentID << ' ' << obj.m_name << ' ' << obj.m_surname << ' ' << obj.m_group << ' ' << obj.m_age << ' ' << obj.m_GPA << std::endl;
	return ou;
}

void Student::operator++() { s_count++; }

bool Student::operator==(const Student& other) const {
	return (this->m_studentID == other.m_studentID &&
		this->m_name == other.m_name &&
		this->m_surname == other.m_surname &&
		this->m_group == other.m_group &&
		this->m_age == other.m_age &&
		this->m_GPA == other.m_GPA);
}
