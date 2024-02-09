/***********************************************************************
 * Header File:
 *    QUEEN
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
class Queen : public Piece
{
public:
	Queen(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
	Queen(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
	~Queen() {                }
	PieceType getType()            const { return QUEEN; }
	void getMoves(set <Move>& moves, const Board& board) const;
	void display(ogstream* pgout)  const;
};
