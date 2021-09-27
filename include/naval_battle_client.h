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
	void PlaceBoat();
private:
	NavalBattlePhase phase_ = NavalBattlePhase::CONNECTION;
	sf::TcpSocket socket_;
	std::array<char, 32> ipAddressBuffer{};
	int portNumber = serverPortNumber;
	PlayerNumber playernumber_ = 255u;
};

class NavalBattleView : public DrawImGuiInterface, public DrawInterface
{
public:
NavalBattleView(NavalBattleClient& client,NavalBattleServer server);
int DrawSfml();
void DrawImGui() override;
bool CheckImpact();
private:
NavalBattleClient& client_;
NavalBattleServer& server_;
int portnumber_ = serverPortNumber;
std::string ipAdressBuffer_ = "localhost";	

};
}