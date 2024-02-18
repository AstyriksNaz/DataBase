#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <random>
#include <iomanip>

extern std::string current_file;

class Student {
private:
	size_t m_studentID;

	std::string m_name;
	std::string m_surname;
	std::string m_group;
	std::string m_age;
	std::string m_GPA; 

	static int s_count;
public:
	Student();

	Student(const std::string& _name, const std::string& _surname, const std::string& _group, const size_t& _age, const float& _GPA);
	Student(const std::string& _name, const std::string& _surname, const std::string& _group, const std::string& _age, const float& _GPA);

	Student(const std::string& _name, const std::string& _surname, const std::string& _group, const size_t& _age, const std::string& _GPA);
	Student(const std::string& _name, const std::string& _surname, const std::string& _group, const std::string& _age, const std::string& _GPA);


	void EditName(const std::string& _name);
	void EditSurname(const std::string& _surname);
	void EditYear(const std::string& _age);

	void EditGroop(const std::string& _group);
	void EditGPA(const std::string& _GPA);
	void EditID(const int& _ID);
		
	size_t GetStudentID() const { return m_studentID; }
	std::string GetName() const { return m_name; }
	std::string GetSurname() const { return m_surname; }
	std::string GetGroup() const { return m_group; }
	std::string GetAge() const { return m_age; }
	std::string GetGPA() const { return m_GPA; };

	~Student();

	friend void remove_data_from_buffer(std::vector<Student>& arr);
	friend void show_data(const Student& x);
	friend void sort(std::vector<Student>& arr);
//operator overloads
public:
	friend std::ostream& operator<<(std::ostream& ou, const Student& obj);
	friend std::istream& operator>>(std::istream& in, Student& obj);
	Student& operator=(const Student& other);
	Student(const Student& other);
	bool operator==(const Student& other) const;
	void operator++();
};

