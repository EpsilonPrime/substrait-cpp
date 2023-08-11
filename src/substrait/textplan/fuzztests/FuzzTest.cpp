/* SPDX-License-Identifier: Apache-2.0 */

#include <filesystem>
#include <memory>
#include <sstream>
#include <string>

#include <fuzztest/fuzztest.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <protobuf-matchers/protocol-buffer-matchers.h>

#include "substrait/textplan/SymbolTablePrinter.h"
#include "substrait/textplan/converter/LoadBinary.h"
#include "substrait/textplan/converter/ParseBinary.h"
#include "substrait/textplan/converter/ReferenceNormalizer.h"
#include "substrait/textplan/parser/ParseText.h"
#include "substrait/textplan/tests/ParseResultMatchers.h"

using ::protobuf_matchers::EqualsProto;
using ::protobuf_matchers::IgnoringFields;
using ::testing::AllOf;

namespace io::substrait::textplan {
namespace {

std::string addLineNumbers(const std::string& text) {
  std::stringstream input{text};
  std::stringstream result;
  int lineNum = 0;
  std::string line;
  while (std::getline(input, line, '\n')) {
    result << std::setw(4) << ++lineNum << " " << line << std::endl;
  }
  return result.str();
}

::substrait::proto::Plan normalizePlan(const ::substrait::proto::Plan& plan) {
  ::substrait::proto::Plan newPlan = plan;
  ReferenceNormalizer::normalize(&newPlan);
  return newPlan;
}

void roundTripDoesNotCrash(const ::substrait::proto::Plan& plan) {
  auto textResult = parseBinaryPlan(plan);
  auto textSymbols = textResult.getSymbolTable().getSymbols();

  std::string outputText =
      SymbolTablePrinter::outputToText(textResult.getSymbolTable());

  ASSERT_THAT(textResult, AllOf(ParsesOk(), HasErrors({})))
      << std::endl
      << "Initial result:" << std::endl
      << addLineNumbers(outputText) << std::endl
      << textResult.getSymbolTable().toDebugString() << std::endl;

  auto stream = loadTextString(outputText);
  auto result = parseStream(stream);
  ASSERT_NO_THROW(auto outputBinary = SymbolTablePrinter::outputToBinaryPlan(
                      result.getSymbolTable()););

  auto normalizedPlan = normalizePlan(plan);
  ASSERT_THAT(
      result,
      ::testing::AllOf(
          ParsesOk(),
          HasErrors({}),
          AsBinaryPlan(IgnoringFields(
              {"substrait.proto.RelCommon.Emit.output_mapping"},
              EqualsProto(normalizedPlan)))))
      << std::endl
      << "Intermediate result:" << std::endl
      << addLineNumbers(outputText) << std::endl
      << result.getSymbolTable().toDebugString() << std::endl;
}

TEST(FuzzTestSuite, EmptyPlanDoesNotCrash) {
  ::substrait::proto::Plan plan;
  roundTripDoesNotCrash(plan);
}

FUZZ_TEST(FuzzTestSuite, roundTripDoesNotCrash);

} // namespace
} // namespace io::substrait::textplan
