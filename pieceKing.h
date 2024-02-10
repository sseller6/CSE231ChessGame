/***********************************************************************
 * Header File:
 *    KING
 * Author:
*     Josh & Steven
 * Summary:
 *    The King class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * KING
  * The king, aka "His Majesty"
  ***************************************************/
class King : public Piece
{
public:
	King(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
	King(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
	~King() {                }
	PieceType getType()            const { return KING; }
	void getMoves(set <Move>& moves, const Board& board) const;
	void display(ogstream* pgout)  const;
};
