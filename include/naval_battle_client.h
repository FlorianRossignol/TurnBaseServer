#pragma once 

#include <iostream>
#include <SFML/Network.hpp>
#include <echo_settings.h>
#include <array>
#include <system.h>

namespace navalbattle 
{
	class NavalBattleClient : public System
	{
		public:
			void Init() override;
			void Update() override;
			void Destroy() override;
			int GetPlayerNumber() const;

		private:
			sf::TcpSocket socket_;
			std::array<char, 32> ipAddressBuffer{};
			int portNumber = serverPortNumber;
			PlayerNumber playernumber_ = 255u;
	};

	class NavalBattleView
	{
	public:
		NavalBattleView(NavalBattleClient& client);
		int DrawSfml();
	private:
		NavalBattleClient& client_; 
		int portnumber_ = serverPortNumber;
		std::string ipAdressBuffer_ = "localhost";
	};

}