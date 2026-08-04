#pragma once

#include <string>
#include <netinet/in.h>

namespace nativeproxy {

class Address {
public:
    Address();

    Address(const std::string& ip, int port);

    bool Set(const std::string& ip, int port);

    sockaddr* SockAddr();

    const sockaddr* SockAddr() const;

    int Length() const;

    std::string Ip() const;

    int Port() const;

private:
    sockaddr_in addr_;
};

}