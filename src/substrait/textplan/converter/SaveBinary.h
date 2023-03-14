/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include "substrait/proto/plan.pb.h"

namespace io::substrait::textplan {

void savePlanToBinaryFile(
    const ::substrait::proto::Plan& plan,
    const std::string_view& output_filename);

void savePlanToJSONFile(
    const ::substrait::proto::Plan& plan,
    const std::string_view& output_filename);

void savePlanToTextPlanFile(
    const ::substrait::proto::Plan& plan,
    const std::string_view& output_filename);

} // namespace io::substrait::textplan
