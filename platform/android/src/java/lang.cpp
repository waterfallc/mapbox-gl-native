#include "lang.hpp"

namespace mbgl {
namespace android {
namespace java {
namespace lang {

// String

jni::Object<String> String::New(JNIEnv& env, jni::String value) {
    static auto constructor = String::javaClass.GetConstructor<jni::String>(env);
    return String::javaClass.New(env, constructor, value);
}

jni::String String::toUpperCase(JNIEnv& env, jni::String value) {
    static auto method = javaClass.GetMethod<jni::String ()>(env, "toUpperCase");
    return String::New(env, value).Call(env, method);
}

jni::String String::toLowerCase(JNIEnv& env, jni::String value) {
    static auto method = javaClass.GetMethod<jni::String ()>(env, "toLowerCase");
    return String::New(env, value).Call(env, method);
}

void String::registerNative(jni::JNIEnv& env) {
    // Lookup the class
    javaClass = *jni::Class<String>::Find(env).NewGlobalRef(env).release();
}

jni::Class<String> String::javaClass;

// Float

jni::Object<Float> Float::valueOf(JNIEnv &env, jfloat value) {
    static auto method = javaClass.GetStaticMethod<jni::Object<Float> (jni::jfloat)>(env, "valueOf");
    return javaClass.Call(env, method, value);
}

void Float::registerNative(jni::JNIEnv &env) {
    // Lookup the class
    javaClass = *jni::Class<Float>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Float> Float::javaClass;

// Long

jni::Object<Long> Long::valueOf(JNIEnv &env, jlong value) {
    static auto method = javaClass.GetStaticMethod<jni::Object<Long> (jni::jlong)>(env, "valueOf");
    return javaClass.Call(env, method, value);
}

void Long::registerNative(jni::JNIEnv &env) {
    // Lookup the class
    javaClass = *jni::Class<Long>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Long> Long::javaClass;

// Double

jni::Object<Double> Double::valueOf(JNIEnv &env, jdouble value) {
    static auto method = javaClass.GetStaticMethod<jni::Object<Double> (jni::jdouble)>(env, "valueOf");
    return javaClass.Call(env, method, value);
}

void Double::registerNative(jni::JNIEnv &env) {
    // Lookup the class
    javaClass = *jni::Class<Double>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Double> Double::javaClass;

// Boolean

jni::Object<Boolean> Boolean::valueOf(JNIEnv &env, jboolean value) {
    static auto method = javaClass.GetStaticMethod<jni::Object<Boolean> (jni::jboolean)>(env, "valueOf");
    return javaClass.Call(env, method, value);
}

void Boolean::registerNative(jni::JNIEnv &env) {
    // Lookup the class
    javaClass = *jni::Class<Boolean>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Boolean> Boolean::javaClass;

// Number

void Number::registerNative(jni::JNIEnv &env) {
    // Lookup the class
    javaClass = *jni::Class<Number>::Find(env).NewGlobalRef(env).release();
}

jni::Class<Number> Number::javaClass;

} // namespace lang
} // namespace java
} // namespace android
} // namespace mbgl
