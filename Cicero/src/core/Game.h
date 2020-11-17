#pragma once
#include<SFML/Graphics.hpp>
#include"Chess.h"
namespace Cicero {

	class Game:public sf::RenderWindow
	{
    public:
		Game();
		void Show();
		void Update(sf::Event event);
	private:
		int size = 242;
		double scale = 0.4;
		MoveWho who = MoveWho::RED;
		Chess* movingChess = nullptr;
		sf::Texture tBoard;
		sf::Sprite sBoard;
		std::vector<Chess*> Chesses;
		sf::Vector2i oldpos,newpos;
		bool leaglQ();

	};


}

