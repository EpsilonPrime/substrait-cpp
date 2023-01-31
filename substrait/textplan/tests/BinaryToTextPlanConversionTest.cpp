#include "../PlanConverter.h"

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "substrait/plan.pb.h"

namespace io::substrait {
namespace {

class BinaryToTextPlanConversionTest : public ::testing::Test {
 protected:
  static void testType() {}
};

TEST_F(BinaryToTextPlanConversionTest, LoadFromJSON) {
  PlanConverter converter;
  std::string json = readFromFile("data/q6_first_stage.json");
  converter.loadFromJSON(json);

  ASSERT_THAT(converter.plan().extensions_size(), ::testing::Eq(7));
  //  ASSERT_THAT(plan.DebugString(), ::testing::HasSubstr("23"));
}

TEST_F(BinaryToTextPlanConversionTest, Something2) {
  PlanConverter converter;
  std::string json = readFromFile("data/q6_first_stage.json");
  converter.loadFromJSON(json);

  std::string s = converter.toString();
  // ASSERT_THAT(s, ::testing::HasSubstr("23"));
  std::cout << s;  // Output a readable version for playing with.
  ASSERT_THAT(
      s,
      ::testing::Eq(
          "extension_space {\n  function lte:fp64_fp64 as lte;\n  function sum:opt_fp64 as sum;\n  function lt:fp64_fp64 as lt;\n  function is_not_null:fp64 as is_not_null;\n  function and:bool_bool as and;\n  function gte:fp64_fp64 as gte;\n  function multiply:opt_fp64_fp64 as multiply;\n"));
}

// MEGAHACK -- Add a symbol table test.

} // namespace
} // namespace substrait