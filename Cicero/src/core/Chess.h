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
	enum MoveWho
	{
		RED,
		BLACk
	};
	class Chess
	{
	public:
		Chess(ChessName _name, MoveWho _redQ, double scale);

		void setPos(int _x, int _y);
		sf::Sprite* getSprite() { return &m_Sprite; }
		int x, y;
		MoveWho redQ;
		ChessName name;
	private:
		double scale;
		int Lsize = 242;
		sf::Sprite m_Sprite;
		sf::Texture tChess;
	};
}


