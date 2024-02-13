#include "Student.h"

Student::Student(const std::string& name, const std::string& surname, const std::string& groop, const size_t& age, const float& GPA) {
	++s_count;
	this->m_studentID = s_count;
	this->m_name = name;
	this->m_surname = surname;
	this->m_GPA = GPA;
	this->m_groop = groop;
	this->m_age = age;
}

Student::Student() {
	const std::string NAME[] = { "Nazarii", "Denus", "Roman", "Victoria", "Liza", "Vitalik"};
	const std::string surname[] = { "Pupkin", "Mercury", "Benninghton", "Veider", "Pukalack"};
	const std::string GROOP[] = { "PC-32", "PC-31", "EK-32", "EK-31", "PC-21"};

	auto f = [](float min, float max) {

		std::random_device rd; // Розподільник випадкових чисел у діапазоні [min, max]
		std::uniform_real_distribution<float> dist(min, max); // Генеруємо випадкове число
		return dist(rd);
	};

	++s_count;
	this->m_studentID = s_count;
	this->m_name = NAME[std::rand() % 6];
	this->m_surname = surname[std::rand() % 5];
	this->m_GPA = f(3.0f, 5.0f);
	this->m_groop = GROOP[std::rand() % 4];
	this->m_age = static_cast<int>(f(16, 19));
}

#pragma region setters&getters

	void Student::EditName(const std::string& name) { this->m_name = name; }
	void Student::EditSurname(const std::string& surname) { this->m_surname = surname; }
	void Student::EditYear(const size_t& age) { this->m_age = age; }
	void Student::EditGroop(const std::string& groop)  { this->m_groop = groop; }
	void Student::EditGPA(const float& GPA) { this->m_GPA = GPA; }
	void Student::EditID(const int& ID) { this->m_studentID = ID; }

#pragma endregion setters&getters;

Student::Student(const Student& other) {
	++s_count;
	this->m_studentID = other.m_studentID;
	this->m_name = other.m_name;
	this->m_surname = other.m_surname;
	this->m_age = other.m_age;
	this->m_GPA = other.m_GPA;
	this->m_groop = other.m_groop;
}

Student& Student::operator=(const Student& other) {
	this->m_studentID = other.m_studentID;
	this->m_name = other.m_name;
	this->m_surname = other.m_surname;
	this->m_age = other.m_age;
	this->m_GPA = other.m_GPA;
	this->m_groop = other.m_groop;
	return *this;
}

int Student::s_count = 0;

Student::~Student() { --s_count; }

//operators to cout and cin data in file and console
std::istream& operator>>(std::istream& in, Student& obj) {
	in >> obj.m_studentID;
	in >> obj.m_name;
	in >> obj.m_surname;
	in >> obj.m_groop;
	in >> obj.m_age;
	in >> obj.m_GPA;
	return in;
}


std::ostream& operator<<(std::ostream& ou, const Student& obj) {
	ou << obj.m_studentID << ' ' << obj.m_name << ' ' << obj.m_surname << ' ' << obj.m_groop << ' ' << obj.m_age << ' ' << obj.m_GPA << std::endl;
	return ou;
}

void Student::operator++() { s_count++; }

bool Student::operator==(const Student& other) const {
	return (this->m_studentID == other.m_studentID &&
		this->m_name == other.m_name &&
		this->m_surname == other.m_surname &&
		this->m_groop == other.m_groop &&
		this->m_age == other.m_age &&
		this->m_GPA == other.m_GPA);
}
