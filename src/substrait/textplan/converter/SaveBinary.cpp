/* SPDX-License-Identifier: Apache-2.0 */

#include "substrait/textplan/converter/SaveBinary.h"

#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include <libc.h>

namespace io::substrait::textplan {

void savePlanToBinaryFile(
    const ::substrait::proto::Plan& plan,
    const std::string_view& output_filename) {
  int outfd = open(std::string{output_filename}.c_str(), O_WRONLY);
  auto stream = new google::protobuf::io::FileOutputStream(outfd);

  if (!plan.SerializeToZeroCopyStream(stream)) {
    // Something bad happened.
  }

  delete stream;
  close(outfd);
}

void savePlanToJSONFile(
    const ::substrait::proto::Plan& plan,
    const std::string_view& output_filename) {
  int outfd = open(std::string{output_filename}.c_str(), O_WRONLY);
  auto stream = new google::protobuf::io::FileOutputStream(outfd);

  std::string output;
  auto status = ::google::protobuf::util::MessageToJsonString(plan, &output);
  if (!status.ok()) {
    // Something bad happened.
  } else {
    // TODO -- Fix potential narrowing issue here.
    if (!stream->WriteAliasedRaw(output.data(), output.length())) {
      // Something else bad happened.
    }
  }

  delete stream;
  close(outfd);
}

void savePlanToTextPlanFile(
    const ::substrait::proto::Plan& plan,
    const std::string_view& output_filename) {
  int outfd = open(std::string{output_filename}.c_str(), O_WRONLY);
  auto stream = new google::protobuf::io::FileOutputStream(outfd);

  if (!::google::protobuf::TextFormat::Print(plan, stream)) {
    // Something bad happened.
  }

  delete stream;
  close(outfd);
}

} // namespace io::substrait::textplan
