#include "Engine.h"
#include "../network/Address.h"
#include "../common/Logger.h"

namespace nativeproxy
{

Engine::Engine()
        : initialized_(false),
          running_(false)
{
}

Engine& Engine::Get()
{
    static Engine instance;

    return instance;
}

bool Engine::Initialize()
{
    if (initialized_)
        return true;

    if (!loop_.Initialize())
        return false;

    if (!listener_.Initialize(loop_.Get()))
        return false;

    Address address("127.0.0.1", 28080);

    if (!listener_.Listen(address))
        return false;

    Logger::Info(
            "Address: " +
            address.Ip() +
            ":" +
            std::to_string(address.Port()));

    initialized_ = true;

    return true;
}

bool Engine::Start()
{
    if (!initialized_)
        return false;

    if (running_)
        return true;

    worker_.Start(
        [this]()
        {
            loop_.Run();
        });

    running_ = true;

    return true;
}

void Engine::Stop()
{
    worker_.Stop();

    running_ = false;
}

bool Engine::Running() const
{
    return running_;
}

}