// Copyright 2020 Your Name <your_email>

#include <student.hpp>
#include "nlohmann/json.hpp"
#include "iomanip"
#include "sstream"

std::string Student::get_name(){
    return name;
}

std::string Student::get_group(){
  if (group.type() == typeid(std::string)) {
    return std::any_cast<std::string>(group);
  } else if (group.type() == typeid(int)) {
    return std::to_string(std::any_cast<int>(group));
  } else {
    return std::to_string(std::any_cast<size_t>(group));
  }
}

std::string Student::get_avg(){
  if (avg.type() == typeid(std::string)) {
    return std::any_cast<std::string>(avg);
  } else if (avg.type() == typeid(size_t)) {
    return std::to_string(std::any_cast<size_t>(avg));
  } else if (avg.type() == typeid(nullptr)) {
    return "null";
  } else {
    return std::to_string(std::any_cast<double>(avg)).substr(0, 4);
  }
}

std::string Student::get_debt(){
  if (debt.type() == typeid(std::string)) {
    return std::any_cast<std::string>(debt);
  } else if (debt.type() == typeid(nullptr)) {
    return "null";
  } else {
    if (std::any_cast<std::vector<std::string>>(debt).size() == 1){
      return std::any_cast<std::vector<std::string>>(debt)[0];
    }
    return std::to_string(std::any_cast<std::vector<std::string>>(debt).size()) +
           " items";
  }
}

Student_prepare::Student_prepare(std::vector<Student>):width_name(4),width_group(5),width_avg(3),width_debt(4) {
  for (auto & Student : student) {
    if (Student.get_name().length() >= width_name) {
      width_name = Student.get_name().length();
    }
    if (Student.get_debt().length() >= width_debt) {
      width_debt = Student.get_debt().length();
    }
    if (Student.get_avg().length() >= width_avg) {
      width_avg = Student.get_avg().length();
    }
    if (Student.get_group().length() >= width_group) {
      width_group = Student.get_group().length();
    }
  }
}

std::string Student_prepare::get_students_table() {
  std::stringstream ss;
  ss << std::setw(2) << "| " << std::setw(width_name) << std::left << "name"
     << std::setw(3) << " | " << std::setw(width_group) << std::left << "group"
     << std::setw(3) << " | " << std::setw(width_avg) << std::left << "avg"
     << std::setw(3) << " | " << std::setw(width_debt) << "debt" << std::setw(2)
     << " |"
     << "\n";
  ss << std::setw(1) << "|" << std::setw(width_name + 2) << std::setfill('-')
     << "" << std::setw(1) << "|" << std::setw(width_group + 2)
     << std::setfill('-') << ""
     << "|" << std::setw(width_avg + 2) << std::setfill('-') << ""
     << "|" << std::setw(width_debt + 2) << std::setfill('-') << ""
     << std::setw(1) << "|"
     << "\n";
  for (size_t i = 0; i < student.size(); ++i) {
      ss << get_student_string(i) << "\n";
  }
  ss << std::setw(1) << "|" << std::setw(width_name + 2) << std::setfill('-')
     << "" << std::setw(1) << "|" << std::setw(width_group + 2)
     << std::setfill('-') << ""
     << "|" << std::setw(width_avg + 2) << std::setfill('-') << ""
     << "|" << std::setw(width_debt + 2) << std::setfill('-') << ""
     << std::setw(1) << "|";
  return ss.str();
}

std::string Student_prepare::get_student_string(int number_student) {
  std::stringstream ss;
  ss << std::setw(2) << "| " << std::setw(width_name) << std::left
     << student[number_student].get_name() << std::setw(3) << " | "
     << std::setw(width_group) << std::left
     << student[number_student].get_group() << std::setw(3) << " | "
     << std::setw(width_avg) << std::left << student[number_student].get_avg()
     << std::setw(3) << " | " << std::setw(width_debt) << std::left
     << student[number_student].get_debt() << std::setw(2) << " |";
  return ss.str();
}

std::size_t Student_prepare::get_name_width() { return width_name; }
std::size_t Student_prepare::get_group_width() { return width_group; }
std::size_t Student_prepare::get_avg_width() { return width_avg; }
std::size_t Student_prepare::get_debt_width() { return width_debt; }
