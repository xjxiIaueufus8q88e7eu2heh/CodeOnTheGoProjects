#include "Address.h"

#include <arpa/inet.h>

namespace nativeproxy {

Address::Address()
{
    Set("127.0.0.1", 0);
}

Address::Address(const std::string& ip, int port)
{
    Set(ip, port);
}

bool Address::Set(const std::string& ip, int port)
{
    addr_ = {};

    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);

    return inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr) == 1;
}

sockaddr* Address::SockAddr()
{
    return reinterpret_cast<sockaddr*>(&addr_);
}

const sockaddr* Address::SockAddr() const
{
    return reinterpret_cast<const sockaddr*>(&addr_);
}

int Address::Length() const
{
    return sizeof(addr_);
}

std::string Address::Ip() const
{
    char buffer[INET_ADDRSTRLEN];

    inet_ntop(
            AF_INET,
            &addr_.sin_addr,
            buffer,
            sizeof(buffer));

    return buffer;
}

int Address::Port() const
{
    return ntohs(addr_.sin_port);
}

}