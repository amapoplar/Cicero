#pragma once
#include<SFML/Graphics.hpp>

namespace Cicero {
	struct Chess
	{
		int pos;
		int name;
	};

	class Game:public sf::RenderWindow
	{
    public:
		Game();
		void Show();
		void Update(sf::Event event);
	private:
		double scale;
		bool isMove =false;
		bool isRed = true;
		sf::Texture tBoard,tChess;
		sf::Sprite sBoard,sChess;
		Chess movingChess;
		bool legalQ(int x, int y);
		bool ruleQ(int x, int y);
		void showBorad();
		int checkMate();
	};


}

