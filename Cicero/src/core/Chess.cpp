#include "cicpch.h"
#include "Chess.h"

namespace Cicero {
	Chess::Chess(ChessName _name, MoveWho _redQ,double size)
		:name(_name),redQ(_redQ), scale(size)
	{
		tChess.loadFromFile("images/chess.png");
		m_Sprite.setTexture(tChess);
		m_Sprite.setTextureRect(sf::IntRect(Lsize*(int)name, Lsize*(int)redQ ,Lsize ,Lsize));
		m_Sprite.scale(size,size);
	}
	 void Chess::setPos(int _x, int _y) {
		x = _x; y = _y;
		int newx = x * scale * Lsize;
		int newy = y * scale * Lsize;
		m_Sprite.setPosition(newx, newy);
	}
}