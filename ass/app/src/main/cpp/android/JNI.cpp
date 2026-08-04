#include <jni.h>
#include <string>

#include "../core/Engine.h"

using namespace nativeproxy;

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void*)
{
    Engine::Get().Initialize();
    Engine::Get().Start();

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ass_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */)
{
    if (Engine::Get().Running())
    {
        return env->NewStringUTF("NativeProxy Running");
    }

    return env->NewStringUTF("NativeProxy Engine Initialized");
}