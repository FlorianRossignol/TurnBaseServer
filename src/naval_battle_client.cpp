#include "..\include\naval_battle_client.h"
#include <SFML/Graphics.hpp>

namespace navalbattle {
void navalbattle::NavalBattleClient::Init()
	{
		constexpr auto adress = "localhost";
		std::memcpy(ipAddressBuffer.data(), adress, std::strlen(adress) + 1);
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

			window.display();
			sf::Font font;
			if (!font.loadFromFile("Just Another Hand.ttf"))
			{
				std::cout << "[Error, no file loaded !]" << "\n";
			}
			sf::Text text;
			text.setFont(font);
			text.setString("Connect to server :");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::Red);
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			window.draw(text);
		}
		return 0;

	}

	void navalbattle::NavalBattleClient::Update()
	{
		if (socket_.getLocalPort() != 0)
		{
			std::cout << "Number" << serverPortNumber << "connected !" << "\n";

		}
	}
	void NavalBattleClient::Destroy()
	{
	}
	int NavalBattleClient::GetPlayerNumber() const
	{
		return playernumber_;
	}
	NavalBattleView::NavalBattleView(NavalBattleClient& client) : client_(client)
	{
		
	}
}