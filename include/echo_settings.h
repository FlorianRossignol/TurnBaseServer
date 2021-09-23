#pragma once

#include <cstddef>
#include <SFML/System/Vector2.hpp>

namespace navalbattle
{
    enum class NavalBattlePhase
    {   
        CONNECTION,
        GAME,
        END
    };
    constexpr unsigned short serverPortNumber = 16000;
    constexpr std::size_t maxDataSize = 256;
    constexpr int maxClientNmb = 2;
    using PlayerNumber = unsigned char;
    enum ServerError
    {
        SERVER_FINISH_OK = 0,
        SERVER_BINDING_ERROR = 1,
    };
    struct Move
    {
        sf::Vector2i position;
        PlayerNumber playerNumber;
    };
}