/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <string_view>
#include <vector>

#include "substrait/proto/plan.pb.h"

namespace io::substrait {

// PlanOrErrors behaves similarly to abseil::StatusOr.
class PlanOrErrors {
 public:
  explicit PlanOrErrors(::substrait::proto::Plan plan)
      : plan_(std::move(plan)){};
  explicit PlanOrErrors(std::vector<std::string> errors)
      : errors_(std::move(errors)){};

  bool ok() {
    return errors_.empty();
  }

  const ::substrait::proto::Plan& operator*() {
    return plan_;
  }

  const std::vector<std::string>& errors() {
    return errors_;
  }

 private:
  ::substrait::proto::Plan plan_;
  std::vector<std::string> errors_;
};

enum PlanFileEncoding {
  BINARY = 0,
  JSON = 1,
  PROTOTEXT = 2,
  // TODO -- Consider adding support for compressed binary files.
};

// Converts a plan in any format into a plan of the specified encoding type.
// Returns a list of errors if the file cannot be parsed.
PlanOrErrors convertPlanFile(
    std::string_view input_filename,
    std::string_view output_filename,
    PlanFileEncoding encoding);

} // namespace io::substrait
