#pragma once

#include <cstddef>

namespace echo
{
    constexpr unsigned short serverPortNumber = 16000;
    constexpr std::size_t maxDataSize = 256;
    constexpr int maxClientNmb = 3;
    enum ServerError
    {
        SERVER_FINISH_OK = 0,
        SERVER_BINDING_ERROR = 1,
    };
}