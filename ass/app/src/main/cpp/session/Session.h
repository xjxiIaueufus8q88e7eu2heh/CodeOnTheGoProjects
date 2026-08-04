#pragma once

#include "../network/Connection.h"

namespace nativeproxy {

class Session
{
public:
    Session();

    virtual ~Session();

    virtual bool Start();

    virtual void Stop();

    Connection* Client();

protected:
    Connection client_;
};

}