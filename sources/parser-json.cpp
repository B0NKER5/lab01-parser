#include "iostream"
#include "nlohmann/json.hpp"
#include "student.hpp"
#include "parser-json.hpp"
#include "fstream"

parser_json::parser_json(const std::string way_file) {
  if (way_file[0] != '{') {
    if (way_file.empty())
      throw std::invalid_argument("the path isn't available");
    std::ifstream file(way_file);
    if (!file) {
      throw std::out_of_range{"unable to open json: " + way_file};
    }
    file >> databasejson;
  } else {
    databasejson = nlohmann::json::parse(way_file);
  }
  if (databasejson.empty()) {
    throw std::invalid_argument("Object array is empty");
  }

  if (!databasejson.at("items").is_array()) {
    throw std::invalid_argument("JSON file is not array");
  }
  if (databasejson.at("items").size() != databasejson.at("_meta").at("count")) {
    throw std::out_of_range("_meta.count != len of items");
  }

  for (auto const& item : databasejson.at("items")) {
    auto studentObj = item.get<Student>();
    student.push_back(studentObj);
  }
}

auto get_name(const nlohmann::json& j) -> std::string {
  return j.get<std::string>();
}

auto get_debt(const nlohmann::json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string> >();
}

auto get_avg(const nlohmann::json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const nlohmann::json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
  return j.get<std::size_t>();
}

void from_json(const nlohmann::json& j, Student& s) {

  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_group(j.at("debt"));
}