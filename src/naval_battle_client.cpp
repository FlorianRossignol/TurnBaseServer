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
if (client_.GetPhase() == NavalBattlePhase::GAME &&
	client_.GetMoveIndex() % 2 == client_.GetPlayerNumber())
{
	DrawCursor(window);
}
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
if (DrawSfml() == 1)
{
	PlaceBoat();
	std::cerr << "Succes to add Boat in place";
}
}
}
}
}


void NavalBattleView::PlaceBoat()
{
	Boat boat;
	for (int i = 0; i < 325; i++)
	{
		boat.Littleboat();
		boat.Mediumboat();
		boat.Hightboat();
	}
	BoatPlacePacket boatPlacePacket;
	boatPlacePacket.packetype = PacketType::MOVE;
	sf::Packet sentPacket;
	sentPacket << boatPlacePacket;
}

void NavalBattleView::DrawCursor(sf::RenderWindow& window)
{
	const auto& mousePos = sf::Mouse::getPosition(window);
	if (mousePos.x < boardOrigin_.x || mousePos.y < boardOrigin_.y)
	{
		cursorPos_ = sf::Vector2i(-1, -1);
		return;
	}
	if (mousePos.x > boardOrigin_.x + boardWindowSize_.x ||
		mousePos.y > boardOrigin_.y + boardWindowSize_.y)
	{
		cursorPos_ = sf::Vector2i(-1, -1);
		return;
	}
	cursorPos_ = sf::Vector2i(
		mousePos.x / (boardWindowSize_.x / 3),
		mousePos.y / (boardWindowSize_.y / 3)
	);
	rect_ = sf::RectangleShape();
	rect_.setOrigin({});
	rect_.setFillColor(sf::Color(255u, 255u, 255u, 100u));
	rect_.setSize(sf::Vector2f(tileSize_));
	rect_.setPosition(sf::Vector2f
	(
		cursorPos_.x * (tileSize_.x + thickness),
		cursorPos_.y * (tileSize_.y + thickness)
	));
	window.draw(rect_);
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
unsigned char NavalBattleClient::GetMoveIndex() const
{
	return currentMoveIndex_;
}

void NavalBattleView::DrawBoat(sf::CircleShape& circle, sf::RenderWindow& window)
{
	Boat boat;
	circle = sf::CircleShape();
	circle.setOrigin({});
	circle.setFillColor(sf::Color(255u, 255u, 255u, 100u));
	//circle.setPosition(sf::Vector2f(boat.boat(), boat.boat()));
	window.draw(circle);
	BoatPlacePacket boatPlacePacket;
	boatPlacePacket.packetype = PacketType::MOVE;
	sf::Packet sentPacket;
	sentPacket << boatPlacePacket;
}

}