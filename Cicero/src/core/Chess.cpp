#include "cicpch.h"
#include "Chess.h"

namespace Cicero {
	Chess::Chess(ChessName _name, bool _redQ)
		:name(_name),redQ(_redQ)
	{
		Tx = name;
		Ty = redQ;
	}
}