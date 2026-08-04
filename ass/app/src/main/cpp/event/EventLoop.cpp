#include "EventLoop.h"
#include "../common/Logger.h"

namespace nativeproxy {

EventLoop::EventLoop()
        : initialized_(false)
{
}

EventLoop::~EventLoop()
{
    if (initialized_)
    {
        uv_timer_stop(&heartbeat_);

        uv_close(
                reinterpret_cast<uv_handle_t*>(&heartbeat_),
                nullptr);

        uv_run(&loop_, UV_RUN_DEFAULT);

        uv_loop_close(&loop_);
    }
}

bool EventLoop::Initialize()
{
    if (initialized_)
        return true;

    if (uv_loop_init(&loop_) != 0)
        return false;

    if (uv_timer_init(&loop_, &heartbeat_) != 0)
        return false;

    heartbeat_.data = this;

    uv_timer_start(
            &heartbeat_,
            EventLoop::OnHeartbeat,
            5000,
            5000);

    initialized_ = true;

    Logger::Info("EventLoop initialized");


    return true;
}

void EventLoop::Run()
{
    Logger::Info("EventLoop running");

    uv_run(&loop_, UV_RUN_DEFAULT);

    Logger::Info("EventLoop stopped");
}

void EventLoop::Stop()
{
    if (!initialized_)
        return;

    uv_stop(&loop_);
}

uv_loop_t* EventLoop::Get()
{
    return &loop_;
}

void EventLoop::OnHeartbeat(uv_timer_t* handle)
{
    Logger::Info("Heartbeat");
}

}