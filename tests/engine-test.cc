#include "gtest/gtest.h"
#include "engine.h"

#include <string>
#include <vector>

TEST(EngineTest, NumberTests){
  using namespace std;
  using namespace formulaEngine;

  vector<pair<string, double>> tests = {
    make_pair("0", 0.0),
    make_pair("1", 1.0),
    make_pair("10", 10.0),
    make_pair("200", 200.0),
    make_pair("3000", 3000.0),

    make_pair("1.1", 1.1),
    make_pair("22.22", 22.22),
    make_pair("123.123", 123.123),
    make_pair("0.0", 0.0),
    make_pair("1.0", 1.0),
    make_pair("1.1e+1", 1.1e+1),
    make_pair("1.1e1", 1.1e1),
    make_pair("2.2E2", 2.2E2),
    make_pair("3.3e-3", 3.3e-3),
    make_pair("1.2e02", 1.2e02),
    make_pair(".1", .1),
    make_pair("1.e2", 1.e2),
  };

  Engine engine;
  for(auto it = tests.begin(); it != tests.end(); it++) {
    double result = engine.Evaluate((*it).first);
    ASSERT_EQ(result, (*it).second);
  }
}

TEST(EngineTest, BinaryOperationTests){
  using namespace std;
  using namespace formulaEngine;

  vector<pair<string, double>> tests = {
    make_pair("1 + 2", 3),
    make_pair("2 * 2", 4),
    make_pair("1 - 2", -1),
    make_pair("2 / 2", 1),
    make_pair("1 + 2 + 3", 6),
    make_pair("10 - 9 + 9", 10),
    make_pair("3 * 4 - 10", 2),
    
    make_pair("1 + 1e5", 100001),
  };

  Engine engine;
  for(auto it = tests.begin(); it != tests.end(); it++) {
    double result = engine.Evaluate((*it).first);
    ASSERT_EQ(result, (*it).second);
  }
}

TEST(EngineTest, ParenthesesTests){
  using namespace std;
  using namespace formulaEngine;

  vector<pair<string, double>> tests = {
    make_pair("3 * (2 + 1)", 9),
    make_pair("3 * (2 + 1 - (3 * 3))", 3 * (2 + 1 - (3 * 3))),
  };

  Engine engine;
  for(auto it = tests.begin(); it != tests.end(); it++) {
    double result = engine.Evaluate((*it).first);
    ASSERT_EQ(result, (*it).second);
  }
}

TEST(EngineTest, FActorialTests){
  using namespace std;
  using namespace formulaEngine;

  vector<pair<string, double>> tests = {
    make_pair("5!", 120),
    make_pair("-5!", -120),
    make_pair("(2 + 3)!", 120),
    make_pair("-(2 + 3)!", -120),
  };

  Engine engine;
  for(auto it = tests.begin(); it != tests.end(); it++) {
    double result = engine.Evaluate((*it).first);
    ASSERT_EQ(result, (*it).second);
  }
}