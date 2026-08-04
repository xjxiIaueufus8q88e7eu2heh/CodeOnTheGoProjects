#include "Connection.h"

#include "../common/Logger.h"

#include <cstring>

namespace nativeproxy {

Connection::Connection()
{
}

Connection::~Connection()
{
}

bool Connection::Initialize(uv_loop_t* loop)
{
    if (uv_tcp_init(loop, &client_) != 0)
        return false;

    client_.data = this;

    return true;
}

bool Connection::Accept(uv_stream_t* server)
{
    if (uv_accept(server, Stream()) != 0)
        return false;

    Logger::Info("Client accepted");

    return true;
}

bool Connection::StartRead()
{
    int r = uv_read_start(
            Stream(),
            Connection::OnAlloc,
            Connection::OnRead);

    if (r != 0)
    {
        Logger::Error("uv_read_start failed");
        return false;
    }

    Logger::Info("Read started");

    return true;
}

bool Connection::Write(const std::string& text)
{
    auto* wr = new WriteRequest();

    wr->buffer = uv_buf_init(
            new char[text.size()],
            static_cast<unsigned int>(text.size()));

    memcpy(
            wr->buffer.base,
            text.data(),
            text.size());

    wr->request.data = wr;

    int r = uv_write(
            &wr->request,
            Stream(),
            &wr->buffer,
            1,
            Connection::OnWrite);

    if (r != 0)
    {
        delete[] wr->buffer.base;
        delete wr;

        Logger::Error("uv_write failed");

        return false;
    }

    return true;
}

void Connection::Close()
{
    Logger::Info("Closing connection");

    uv_close(
            reinterpret_cast<uv_handle_t*>(&client_),
            Connection::OnClose);
}

uv_stream_t* Connection::Stream()
{
    return reinterpret_cast<uv_stream_t*>(&client_);
}

void Connection::OnAlloc(
        uv_handle_t*,
        size_t suggested_size,
        uv_buf_t* buf)
{
    buf->base = new char[suggested_size];
    buf->len = suggested_size;
}

void Connection::OnRead(
        uv_stream_t* stream,
        ssize_t nread,
        const uv_buf_t* buf)
{
    auto* connection =
            static_cast<Connection*>(stream->data);

    if (nread > 0)
    {
        std::string text(buf->base, nread);

        Logger::Info(
                "Received " +
                std::to_string(nread) +
                " bytes");

        Logger::Info(text);

        connection->Write(text);
    }

    if (nread < 0)
    {
        Logger::Info("Client disconnected");

        connection->Close();
    }

    delete[] buf->base;
}

void Connection::OnWrite(
        uv_write_t* request,
        int status)
{
    auto* wr =
            static_cast<WriteRequest*>(request->data);

    if (status == 0)
    {
        Logger::Info("Write completed");
    }
    else
    {
        Logger::Error("Write failed");
    }

    delete[] wr->buffer.base;
    delete wr;
}

void Connection::OnClose(
        uv_handle_t* handle)
{
    auto* connection =
            static_cast<Connection*>(handle->data);

    Logger::Info("Connection destroyed");

    delete connection;
}

}