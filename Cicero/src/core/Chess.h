#pragma once
#include<SFML/Graphics.hpp>
namespace  Cicero {
	enum ChessName
	{
		JU,
		MA,
		XA,
		SI,
		JN,
		PA,
		ZU
	};
	class Chess
	{
	public:
		Chess(ChessName _name,bool _redQ);

		void setPos(int _x, int _y) {
			x = _x; y = _y; 
			m_Sprite.setPosition(sf::Vector2f(size * x, size * y));
		}
		sf::Sprite* getSprite() { return &m_Sprite; }
		int x, y;
		int Tx, Ty;
		bool redQ;
	private:
		ChessName name;
		sf::Sprite m_Sprite;
		const int size = 242;
	};
}


