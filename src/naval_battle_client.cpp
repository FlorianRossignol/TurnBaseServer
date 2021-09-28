#include "..\include\naval_battle_client.h"
#include <SFML/Graphics.hpp>
#include <naval_battle_packet.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <boat.h>


namespace navalbattle {
sf::Socket::Status NavalBattleClient::Connect(sf::IpAddress adress, unsigned short portNumber)
{
const auto status = socket_.connect(adress, portNumber);
socket_.setBlocking(false);
return status;
}
void NavalBattleClient::ReceivedPacket(sf::Packet& packet)
{
Packet navalbattlepacket{};
packet >> navalbattlepacket;

switch (static_cast<PacketType>(navalbattlepacket.packetype))
{
case PacketType::GAME_INIT:
{
GameInitPacket gameinitpacket{};
packet >> gameinitpacket;
playernumber_ = gameinitpacket.playerNumber;
phase_ = NavalBattlePhase::GAME;
std::cout << "You are player " << gameinitpacket.playerNumber + 1 << "\n";
break;
}
case PacketType::MOVE:
{
if (phase_ != NavalBattlePhase::GAME)
{
break;
}
			
MovePacket movePacket;
packet >> movePacket;
std::cout << "Receive input packet from player" << movePacket.move.playerNumber + 1 << "\n";
break;
}
}
}
void navalbattle::NavalBattleClient::Init()
{
constexpr auto adress = "localhost";
std::memcpy(ipAddressBuffer.data(), adress, std::strlen(adress) + 1);
}


NavalBattleView::NavalBattleView(NavalBattleClient& client) : client_(client)
{
}	

int navalbattle::NavalBattleView::DrawSfml()
{
sf::RenderWindow window(sf::VideoMode(800, 600), "Naval Battle");
while (window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
if (event.type == sf::Event::Closed)
{
window.close();
}
}
window.clear(sf::Color::Black);

			
sf::Texture mapTexture;
if (!mapTexture.loadFromFile("C:/Users/fmusi/Desktop/Mygame/TurnBaseServer/image/naval battle map 47x96 site.jpg"))
{
std::cout << "[Error, no file loaded !]" << "\n";
}
sf::Sprite sprite;
sprite.setTexture(mapTexture);
window.draw(sprite);
ImGui::Button("Chat");
window.display();
}
return 0;

}

void NavalBattleView::DrawImGui()
{
switch (client_.GetPhase())
{
case NavalBattlePhase::CONNECTION:
{
if (client_.IsConnected())
{
return;
}
ImGui::Begin("Client");
ImGui::InputText("Ip Adress", &ipAdressBuffer_);
ImGui::InputInt("Port Number", &portnumber_);
if (ImGui::Button("Connect"))
{
const auto status = client_.Connect(sf::IpAddress(ipAdressBuffer_),portnumber_);
if (status != sf::Socket::Done)
{
switch (status)
{
case sf::Socket::NotReady:
std::cerr << "Not ready to connect to " << ipAdressBuffer_ << ":"<< portnumber_ << "\n";
break;
case sf::Socket::Partial:
std::cerr << "Connecting to " << ipAdressBuffer_ << ":" << portnumber_ << "\n";
break;
case sf::Socket::Disconnected:
std::cerr << "Disconnecting to" << ipAdressBuffer_ << ":" << portnumber_ << "\n";
break;
case sf::Socket::Error:
std::cerr << "Error connecting to " << ipAdressBuffer_ << ":" << portnumber_ << "\n";
break;
default:;
}

}
else
{
std::cout << "Succesfully connected to server\n";
}

}
ImGui::End();
break;
}
case NavalBattlePhase::GAME:
{
//TODO complete
if (client_.IsConnected())
{
DrawSfml();
}
}
}
}


void NavalBattleClient::PlaceBoat()
{
	Boat boat;
	for (int i = 0; i < 325; i++)
	{
		boat.Littleboat();
		boat.Mediumboat();
		boat.Hightboat();
	}
}

bool NavalBattleView::CheckImpact()
{
return false;
}

void navalbattle::NavalBattleClient::Update()
{
if (socket_.getLocalPort() != 0)
{
sf::Packet receivedpacket;
sf::Socket::Status status;
do
{
status = socket_.receive(receivedpacket);

} while (status == sf::Socket::Partial);
			
if (status == sf::Socket::Done)
{
ReceivedPacket(receivedpacket);
}
if (status == sf::Socket::Disconnected)
{
socket_.disconnect();
std::cerr << "Server disconnected !\n";
}

}
}
void NavalBattleClient::Destroy()
{
}
int NavalBattleClient::GetPlayerNumber() const
{
return playernumber_;
}
NavalBattlePhase NavalBattleClient::GetPhase() const
{
return phase_;
}
bool NavalBattleClient::IsConnected() const
{
return socket_.getLocalPort() != 0;
}

}