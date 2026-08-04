#include "Worker.h"

#include <android/log.h>

#define LOG_TAG "NativeProxy"

namespace nativeproxy {

Worker::Worker()
        : running_(false)
{
}

Worker::~Worker()
{
    Stop();
}

bool Worker::Start(const std::function<void()>& callback)
{
    if (running_)
        return false;

    callback_ = callback;

    running_ = true;

    thread_ = std::thread(&Worker::ThreadMain, this);

    __android_log_print(
            ANDROID_LOG_INFO,
            LOG_TAG,
            "Worker thread created");

    return true;
}

void Worker::Stop()
{
    if (!running_)
        return;

    running_ = false;

    if (thread_.joinable())
        thread_.join();

    __android_log_print(
            ANDROID_LOG_INFO,
            LOG_TAG,
            "Worker stopped");
}

bool Worker::Running() const
{
    return running_;
}

void Worker::ThreadMain()
{
    __android_log_print(
            ANDROID_LOG_INFO,
            LOG_TAG,
            "Worker thread started");

    if (callback_)
    {
        callback_();
    }

    __android_log_print(
            ANDROID_LOG_INFO,
            LOG_TAG,
            "Worker thread exited");
}

}