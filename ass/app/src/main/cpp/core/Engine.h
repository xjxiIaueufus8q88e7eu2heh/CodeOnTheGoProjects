#pragma once

#include "../thread/Worker.h"
#include "../event/EventLoop.h"

namespace nativeproxy {

class Engine {
public:
    static Engine& Get();

    bool Initialize();
    bool Start();
    void Stop();

    bool Running() const;

private:
    Engine();

    Worker worker_;
    EventLoop loop_;

    bool initialized_;
    bool running_;
};

}