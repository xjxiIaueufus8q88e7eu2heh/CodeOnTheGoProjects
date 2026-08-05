#pragma once

#include <atomic>
#include <functional>
#include <thread>

namespace nativeproxy {

class Worker {
public:
    Worker();
    ~Worker();

    bool Start(const std::function<void()>& callback);

    void Stop();

    bool Running() const;

private:
    void ThreadMain();

    std::thread thread_;
    std::atomic<bool> running_;
    std::function<void()> callback_;
};

}