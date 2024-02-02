/* SPDX-License-Identifier: Apache-2.0 */

#include <substrait/common/Io.h>

extern "C" {

typedef struct {
  char *buffer;
  uint32_t size;
  char *errorMessage;
} SerializedPlan;

// Load a Substrait plan (in any format) from disk.
// Stores the Substrait plan in planBuffer in serialized form.
// Returns a SerializedPlan structure containing either the serialized plan or
// an error message.
SerializedPlan* load_substrait_plan(const char* filename) {
  // MEGAHACK -- Consider putting this initialization into a separate function.
  auto newPlan = new SerializedPlan();
  newPlan->buffer = nullptr;
  newPlan->size = 0;
  newPlan->errorMessage = nullptr;

  auto planOrError = io::substrait::loadPlan(filename);
  if (!planOrError.ok()) {
    auto errMsg = planOrError.status().message();
    newPlan->errorMessage = new char[errMsg.length()+1];
    strncpy(newPlan->errorMessage, errMsg.data(), errMsg.length()+1);
    return newPlan;
  }
  ::substrait::proto::Plan plan = *planOrError;
  std::string text = plan.SerializeAsString();
  newPlan->buffer = new char[text.length()+1];
  memcpy(newPlan->buffer, text.data(), text.length()+1);
  newPlan->size = text.length();
  return newPlan;
}

void free_substrait_plan(SerializedPlan* plan) {
  if (plan->buffer) {
    free(plan->buffer);
  }
  if (plan->errorMessage) {
    free(plan->errorMessage);
  }
  free(plan);
}

// Write a serialized Substrait plan to disk in the specified format.
// On error returns a non-empty error message.
// On success an empty string is returned.
const char* save_substrait_plan(
    const char* planData,
    uint32_t planDataLength,
    const char* filename,
    io::substrait::PlanFileFormat format) {
  ::substrait::proto::Plan plan;
  std::string data(planData, planDataLength);
  plan.ParseFromString(data);
  auto result = io::substrait::savePlan(plan, filename, format);
  if (!result.ok()) {
    return result.message().data();
  }
  return "";
}

}  // extern "C"
