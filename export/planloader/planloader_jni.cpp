/* SPDX-License-Identifier: Apache-2.0 */

#include <jni/jni.hpp>

#include "planloader.h"

class PlanLoaderException : public std::exception {
 private:
  std::string message;

 public:
  explicit PlanLoaderException(const char* msg) : message(msg) {}

  const char* what() {
    return message.c_str();
  }
};

static void RegisterPlanLoader(JavaVM* vm) {
  struct PlanLoader {
    static constexpr auto Name() {
      return "PlanLoader";
    }
  };

  jni::JNIEnv& env{jni::GetEnv(*vm)};

  auto load =
      [](jni::JNIEnv& env, jni::Object<PlanLoader>&, jni::String& filename) {
        auto str = jni::Make<std::string>(env, filename);
        auto result = load_substrait_plan(str.c_str());
        auto freeResult = [&result]() { free_substrait_plan(result); };
        if (*result->error_message) {
          throw PlanLoaderException(result->error_message);
        }
        // MEGAHACK -- Extract the plan from the result and prepare to return
        // it.
        return jni::Make<jni::String>(env, u"hello");
      };

  auto save = [](jni::JNIEnv& env,
                 jni::Object<PlanLoader>&,
                 jni::Array<jni::Byte>& planData,
                 jni::String& filename,
                 jni::Integer& format) {
    auto buffer = planData.get();
    auto size = planData.Length(env);
    // MEGAHACK -- Validate that size is less wide than an int32_t.
    auto str = jni::Make<std::string>(env, filename);
    auto msg = save_substrait_plan(
        reinterpret_cast<const unsigned char*>(buffer),
        size,
        str.c_str(),
        io::substrait::PlanFileFormat::kText);
    if (*msg) {
      throw PlanLoaderException(msg);
    }
    return;
  };

  jni::RegisterNatives(
      env,
      *jni::Class<PlanLoader>::Find(env),
      jni::MakeNativeMethod("loadSubstraitPlan", load),
      jni::MakeNativeMethod("saveSubstraitPlan", save));
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
  RegisterPlanLoader(vm);
  return jni::Unwrap(jni::jni_version_1_2);
}
