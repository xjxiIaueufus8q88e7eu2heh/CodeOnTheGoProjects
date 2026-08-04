#pragma once

#include <uv.h>
#include "Connection.h"
#include "Address.h"

namespace nativeproxy {

class Listener {
public:
    Listener();

    bool Initialize(uv_loop_t* loop);

    bool Listen(const Address& address);

private:
    static void OnConnection(uv_stream_t* server, int status);

    uv_tcp_t server_;
};

}