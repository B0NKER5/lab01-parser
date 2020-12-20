#include "student.hpp"
#include "nlohmann/json.hpp"

void from_json(const nlohmann::json& j, Student& s);
auto get_name(const nlohmann::json& j) -> std::string;
auto get_debt(const nlohmann::json& j) -> std::any;
auto get_avg(const nlohmann::json& j) -> std::any;
auto get_group(const nlohmann::json& j) -> std::any;

class parser_json{
 private:
  nlohmann::json databasejson;
  std::vector<Student> student;

 public:
  parser_json(const std::string way_file);
  std::vector<Student> get_students();
};
