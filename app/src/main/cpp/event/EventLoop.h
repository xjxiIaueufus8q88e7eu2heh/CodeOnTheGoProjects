#pragma once

#include <uv.h>

namespace nativeproxy {

class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    bool Initialize();

    void Run();

    void Stop();

    uv_loop_t* Get();

private:
    static void OnHeartbeat(uv_timer_t* handle);

    uv_loop_t loop_;

    uv_timer_t heartbeat_;

    bool initialized_;
};

}