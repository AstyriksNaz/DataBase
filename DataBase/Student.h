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
	std::string m_groop;

	size_t m_age;
	float m_GPA; 

	static int s_count;
public:
	Student();
	Student(const std::string& name, const std::string& surname, const std::string& groop, const size_t& age, const float& GPA);

	void EditName(const std::string& name);
	void EditSurname(const std::string& surname);
	void EditYear(const size_t& age);
	void EditGroop(const std::string& groop);
	void EditGPA(const float& GPA);
	void EditID(const int& ID);
		
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

