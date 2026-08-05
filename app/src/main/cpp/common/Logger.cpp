#include "Logger.h"

#include <android/log.h>

#define LOG_TAG "NativeProxy"

namespace nativeproxy {

void Logger::Debug(const std::string& message)
{
    __android_log_print(
            ANDROID_LOG_DEBUG,
            LOG_TAG,
            "%s",
            message.c_str());
}

void Logger::Info(const std::string& message)
{
    __android_log_print(
            ANDROID_LOG_INFO,
            LOG_TAG,
            "%s",
            message.c_str());
}

void Logger::Warn(const std::string& message)
{
    __android_log_print(
            ANDROID_LOG_WARN,
            LOG_TAG,
            "%s",
            message.c_str());
}

void Logger::Error(const std::string& message)
{
    __android_log_print(
            ANDROID_LOG_ERROR,
            LOG_TAG,
            "%s",
            message.c_str());
}

}