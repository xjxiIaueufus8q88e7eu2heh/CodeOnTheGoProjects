#include "Session.h"

namespace nativeproxy {

Session::Session()
{
}

Session::~Session()
{
}

bool Session::Start()
{
    return true;
}

void Session::Stop()
{
}

Connection* Session::Client()
{
    return &client_;
}

}