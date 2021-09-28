#pragma once 

#include <iostream>
#include <SFML/Network.hpp>
#include <echo_settings.h>
#include <array>
#include <system.h>
#include <naval_battle_server.h>

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
private:
	NavalBattlePhase phase_ = NavalBattlePhase::CONNECTION;
	sf::TcpSocket socket_;
	std::array<char, 32> ipAddressBuffer{};
	int portNumber = serverPortNumber;
	PlayerNumber playernumber_ = 255u;
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
NavalBattleClient& client_;
int portnumber_ = serverPortNumber;
std::string ipAdressBuffer_ = "localhost";	

};
}