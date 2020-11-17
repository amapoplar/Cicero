#pragma once
#include<SFML/Graphics.hpp>
#include"Chess.h"
namespace Cicero {
	class Game
	{
    public:
		Game();
		void Show();
		sf::Sprite* Update(sf::Event event, sf::Sprite* _sprite);
	private:
		std::unique_ptr<sf::RenderWindow> m_Window;
		const int size = 242;
		sf::Texture tBoard, tChess;
		sf::Sprite sBoard;
		std::vector<Chess> sChess;
	};


}

