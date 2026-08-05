#include "Worker.h"
#include "../common/Logger.h"

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

    Logger::Info("Worker thread created");

    return true;
}

void Worker::Stop()
{
    if (!running_)
        return;

    running_ = false;

    if (thread_.joinable())
        thread_.join();

    Logger::Info("Worker stopped");
}

bool Worker::Running() const
{
    return running_;
}

void Worker::ThreadMain()
{
    Logger::Info("Worker thread started");

    if (callback_)
    {
        callback_();
    }

    Logger::Info("Worker thread exited");
}

}