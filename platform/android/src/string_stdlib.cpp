#include <mbgl/util/platform.hpp>
#include "java/lang.hpp"
#include "attach_env.hpp"

namespace mbgl {
namespace platform {

std::string uppercase(const std::string& str) {
    auto env{ android::AttachEnv() };
    auto jstring = jni::Make<jni::String>(*env, str.c_str());
    return jni::Make<std::string>(*env, mbgl::android::java::lang::String::toUpperCase(*env, jstring));
}

std::string lowercase(const std::string& str) {
    auto env{ android::AttachEnv() };
    auto jstring = jni::Make<jni::String>(*env, str.c_str());
    return jni::Make<std::string>(*env, mbgl::android::java::lang::String::toLowerCase(*env, jstring));
}

} // namespace platform
} // namespace mbgl
