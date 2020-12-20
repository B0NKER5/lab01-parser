// Copyright 2020 Your Name <your_email>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include "iostream"
#include "any"
#include "vector"

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;

  std::string get_name();
  std::string get_group();
  std::string get_avg();
  std::string get_debt();
};

class Student_prepare{
 private:
  size_t width_name;
  size_t width_group;
  size_t width_avg;
  size_t width_debt;
  std::vector<Student> student;

 public:
  size_t get_name_width();
  size_t get_group_width();
  size_t get_avg_width();
  size_t get_debt_width();
  Student_prepare(std::vector<Student>);
  std::string get_students_table();
  std::string get_student_string(int);
};

#endif // INCLUDE_HEADER_HPP_
