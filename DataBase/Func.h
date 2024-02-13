#pragma once
#include <fstream>
#include <thread>
#include "Student.h"

#pragma warning(disable: 4091)

//save data to file
void save_data(std::vector<Student>& arr);

//clear file
void file_clear();

//get ALL data from file
void get_data_from_file(std::vector<Student>& arr);

//clear file
void remove_all_data_from_file();

//remove student
void remove_student(std::vector<Student>& arr);

//edit data
void editData(std::vector<Student>& arr);

//show ALL data
void show_data(const std::vector<Student>& arr);

//add student
void add_data(std::vector<Student>& arr);

//clear buffer
void remove_data_from_buffer(std::vector<Student>& arr);

//sort student
void sort(std::vector<Student>& arr);

//close file
void logOutFile(bool &fileIsOpen);

//wait
void waitButton();