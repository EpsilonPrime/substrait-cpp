/* SPDX-License-Identifier: Apache-2.0 */

#include "substrait/common/NumberUtils.h"

#include <gtest/gtest.h>

using namespace io::substrait::common;

class ConvertPlanTest : public ::testing::Test {};

TEST_F(ConvertPlanTest, isNonNegativeInteger) {
  ASSERT_TRUE(NumberUtils::isNonNegativeInteger("1"));
  ASSERT_TRUE(NumberUtils::isNonNegativeInteger("0"));
  ASSERT_FALSE(NumberUtils::isNonNegativeInteger("-1"));
  ASSERT_FALSE(NumberUtils::isNonNegativeInteger("L1"));
  ASSERT_FALSE(NumberUtils::isNonNegativeInteger("1L"));
  ASSERT_FALSE(NumberUtils::isNonNegativeInteger(""));
}
