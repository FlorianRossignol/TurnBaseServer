#pragma once

#include <echo_settings.h>
#include <SFML/Network/Packet.hpp>

namespace navalbattle 
{
	enum class PacketType : unsigned char
	{
		GAME_INIT,
		MOVE,
		END
	};

	struct Packet
	{
		PacketType packetype;
	};
	
	inline sf::Packet& operator <<(sf::Packet& packet, const Packet& navalbattlePacket)
	{
		const auto packetType = static_cast<unsigned char>(navalbattlePacket.packetype);
		return packet << packetType;
	}

	inline sf::Packet& operator >>(sf::Packet& packet, Packet& navalbattlePacket)
	{
		unsigned char packetType;
		packet >> packetType;
		navalbattlePacket.packetype = static_cast<PacketType>(packetType);
		return packet;
	}

	struct GameInitPacket : Packet
	{
		PlayerNumber playerNumber;
	};

	inline sf::Packet& operator <<(sf::Packet& packet, const GameInitPacket& gameInitPacket)
	{
		return packet << static_cast<unsigned char>(gameInitPacket.packetype)
			<< gameInitPacket.playerNumber;
	}

	inline sf::Packet& operator >>(sf::Packet& packet, GameInitPacket& gameInitPacket)
	{
		return packet >> gameInitPacket.playerNumber;
	}
}