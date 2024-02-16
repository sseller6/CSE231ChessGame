/***********************************************************************
 * Header File:
 *    PAWN
 * Author:
*     Josh & Steven
 * Summary:
 *    The Pawn class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * PAWN
  * The Pawn, aka "cannon fodder."
  ***************************************************/
class Pawn : public Piece
{
public:
	Pawn(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
	Pawn(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
	~Pawn() {                }
	PieceType getType()            const { return PAWN; }
	void getMoves(set <Move>& moves, const Board& board) const;
	void display(ogstream* pgout)  const;
   bool canPromote() const { return fWhite ? position.getRow() == 7 : position.getRow() == 0; }

private:
	
};
