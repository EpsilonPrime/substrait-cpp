#include "substrait/common/Convert.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "substrait/common/Exceptions.h"
#include "substrait/textplan/converter/LoadBinary.h"
#include "substrait/textplan/converter/SaveBinary.h"

namespace io::substrait {

PlanOrErrors loadPlanWithUnknownEncoding(std::string_view input_filename) {
  auto content = textplan::readFromFile(input_filename);
  auto planOrError = textplan::loadFromJSON(content);
  if (planOrError.ok()) {
    return *planOrError;
  }

  planOrError = textplan::loadFromText(content);
  if (planOrError.ok()) {
    return *planOrError;
  }

  planOrError = textplan::loadFromBinary(content);
  if (planOrError.ok()) {
    return *planOrError;
  }

  return planOrError.errors();
}

[[maybe_unused]] PlanOrErrors convertPlanFile(
    std::string_view input_filename,
    std::string_view output_filename,
    PlanFileEncoding encoding) {
  auto planOrError = loadPlanWithUnknownEncoding(input_filename);
  if (!planOrError.ok()) {
    return planOrError.errors();
  }

  switch (encoding) {
    case BINARY:
      textplan::savePlanToBinaryFile(*planOrError, output_filename);
      break;
    case JSON:
      textplan::savePlanToJSONFile(*planOrError, output_filename);
      break;
    case PROTOTEXT:
      textplan::savePlanToTextPlanFile(*planOrError, output_filename);
      break;
  }
}

} // namespace io::substrait
