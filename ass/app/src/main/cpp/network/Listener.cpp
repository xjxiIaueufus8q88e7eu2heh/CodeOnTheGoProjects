#include "Listener.h"
#include "../common/Logger.h"

namespace nativeproxy {

Listener::Listener()
{
}

bool Listener::Initialize(uv_loop_t* loop)
{
    return uv_tcp_init(loop, &server_) == 0;
}

bool Listener::Listen(const Address& address)
{
    int r;

    r = uv_tcp_bind(
            &server_,
            address.SockAddr(),
            0);

    if (r != 0)
    {
        Logger::Error("uv_tcp_bind failed");
        return false;
    }

    r = uv_listen(
            reinterpret_cast<uv_stream_t*>(&server_),
            128,
            Listener::OnConnection);

    if (r != 0)
    {
        Logger::Error("uv_listen failed");
        return false;
    }

    Logger::Info("Listener started");

    Logger::Info(
            "Listening on " +
            address.Ip() +
            ":" +
            std::to_string(address.Port()));

    return true;
}

void Listener::OnConnection(
        uv_stream_t* server,
        int status)
{
    if (status < 0)
        return;

    Logger::Info("Client Connected");

    auto* connection = new Connection();

    if (!connection->Initialize(server->loop))
    {
        Logger::Error("Connection initialization failed");

        delete connection;

        return;
    }

    if (!connection->Accept(server))
    {
        Logger::Error("uv_accept failed");

        delete connection;

        return;
    }

    Logger::Info("Connection object created");
    connection->StartRead();
}


}