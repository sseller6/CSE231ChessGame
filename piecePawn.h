/***********************************************************************
 * Header File:
 *    PAWN
 * Author:
*    <your name here>
 * Summary:
 *    The KNIGHT class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * KNIGHT
  * The knight, aka the "Horse"
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
};
