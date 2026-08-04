#pragma once

#include <string>

#include <uv.h>

namespace nativeproxy {

class Connection {
public:
    Connection();

    ~Connection();

    bool Initialize(uv_loop_t* loop);

    bool Accept(uv_stream_t* server);

    bool StartRead();

    bool Write(const std::string& text);

    void Close();

    uv_stream_t* Stream();

private:

    struct WriteRequest
    {
        uv_write_t request;
        uv_buf_t buffer;
    };

    static void OnAlloc(
            uv_handle_t* handle,
            size_t suggested_size,
            uv_buf_t* buf);

    static void OnRead(
            uv_stream_t* stream,
            ssize_t nread,
            const uv_buf_t* buf);

    static void OnWrite(
            uv_write_t* request,
            int status);

    static void OnClose(
            uv_handle_t* handle);

    uv_tcp_t client_;
};

}