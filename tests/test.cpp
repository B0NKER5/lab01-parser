// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <gtest/gtest.h>
#include "parser-json.hpp"
#include "student.hpp"

TEST(jsonParser, emptyPath){
  ASSERT_THROW(parser_json(""), std::invalid_argument);
}

TEST(jsonParser, emptyArray){
  ASSERT_THROW(parser_json((R"({})")), std::invalid_argument);
}

TEST(jsonParser, simpleArray){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_student_string(2),
            "| Pertov Nikita | IU8-31 | 3.33 | Network |");
}

TEST(jsonParser, invalidPath){
  ASSERT_THROW(parser_json("/sd.json"), std::out_of_range);
}

TEST(jsonParser, sizeTest){
  ASSERT_THROW(parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 5
  }
})"), std::out_of_range);
}


TEST(jsonParser, correctOut){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_student_string(0),
            "| Ivanov Petr   | 1      | 4.25 | null    |");
  ASSERT_EQ(prepare.get_student_string(1),
            "| Sidorov Ivan  | 31     | 4    | C++     |");
  ASSERT_EQ(prepare.get_student_string(2),
            "| Pertov Nikita | IU8-31 | 3.33 | 3 items |");
}


TEST(jsonParser, nullAvg){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": null,
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_student_string(0),
            "| Ivanov Petr   | 1      | null | null    |");
  ASSERT_EQ(prepare.get_student_string(1),
            "| Sidorov Ivan  | 31     | 4    | C++     |");
  ASSERT_EQ(prepare.get_student_string(2),
            "| Pertov Nikita | IU8-31 | 3.33 | 3 items |");
}

TEST(jsonParser, printTable){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_students_table(),
            "| name          | group  | avg  | debt    |\n"
            "|---------------|--------|------|---------|\n"
            "| Ivanov Petr   | 1      | 4.25 | null    |\n"
            "| Sidorov Ivan  | 31     | 4    | C++     |\n"
            "| Pertov Nikita | IU8-31 | 3.33 | 3 items |\n"
            "|---------------|--------|------|---------|");
}


TEST(jsonParser, widthDebt){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_debt_width(), 7);
}


TEST(jsonParser, widthAvg){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_avg_width(), 4);
}

TEST(jsonParser, nameAvg){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_name_width(), 13);
}



TEST(jsonParser, groupWidth){
  parser_json parser = parser_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  Student_prepare prepare = Student_prepare(parser.get_students());
  ASSERT_EQ(prepare.get_group_width(), 6);
}
