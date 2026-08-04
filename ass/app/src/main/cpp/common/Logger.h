#pragma once

#include <string>

namespace nativeproxy {

class Logger {
public:
    static void Debug(const std::string& message);

    static void Info(const std::string& message);

    static void Warn(const std::string& message);

    static void Error(const std::string& message);
};

}