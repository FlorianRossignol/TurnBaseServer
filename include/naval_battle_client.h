#pragma once 

#include <iostream>
#include <SFML/Network.hpp>
#include <echo_settings.h>
#include <array>
#include <system.h>
#include <naval_battle_server.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace navalbattle 
{
class NavalBattleClient : public System
{
public:
	sf::Socket::Status Connect(sf::IpAddress adress, unsigned short portNumber);
	void ReceivedPacket(sf::Packet& packet);
	void Init() override;
	void Update() override;
	void Destroy() override;
	int GetPlayerNumber() const;
	NavalBattlePhase GetPhase() const;
	bool IsConnected() const;
	unsigned char GetMoveIndex() const;
private:
	NavalBattlePhase phase_ = NavalBattlePhase::CONNECTION;
	sf::TcpSocket socket_;
	std::array<char, 32> ipAddressBuffer{};
	int portNumber = serverPortNumber;
	PlayerNumber playernumber_ = 255u;
	unsigned char currentMoveIndex_ = 0;
};

class NavalBattleView : public DrawImGuiInterface
{
public:
NavalBattleView(NavalBattleClient& client);
int DrawSfml();
void DrawImGui() override;
bool CheckImpact();
void PlaceBoat();
private:
	void DrawBoat(sf::CircleShape& circle, sf::RenderWindow& window);
	void DrawCursor(sf::RenderWindow& window);
NavalBattleClient& client_;
int portnumber_ = serverPortNumber;
std::string ipAdressBuffer_ = "localhost";	
sf::Vector2i cursorPos_{ -1,-1 };
sf::Vector2i windowSize_;
sf::Vector2i boardWindowSize_;
sf::Vector2i boardOrigin_;
sf::Vector2i tileSize_;
sf::RectangleShape rect_;
static constexpr int thickness = 10;
};
}