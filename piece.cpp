/***********************************************************************
 * Source File:
 *    PIECE 
 * Author:
 *    Josh & Steven
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;

/************************************************
 * PIECE : NON-DEFAULT CONSTRUCTORS
 ***********************************************/
Piece::Piece(const Position& pos, bool isWhite)
{
	position = pos;
	fWhite = isWhite;

	nMoves = 0;
	lastMove = 0;
}

Piece::Piece(int c, int r, bool isWhite)
{
	position = Position(c, r);
	fWhite = isWhite;

	nMoves = 0;
	lastMove = 0;
}

Piece::Piece(const Piece& piece)
{
	nMoves = piece.nMoves;
	fWhite = piece.fWhite;
	position = piece.position;
	lastMove = piece.lastMove;
}

/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece & Piece::operator = (const Piece & rhs)
{
   this->nMoves = rhs.nMoves;
   this->fWhite = rhs.fWhite;
   this->position = rhs.position;
   this->lastMove = rhs.lastMove;
   
   return *this;
}

/************************************************
 * PIECE : SET LAST MOVE
 * Set the piece's last move and increment nMoves.
 ***********************************************/
void Piece::setLastMove(int currentMove)
{
   lastMove = currentMove;
   nMoves++;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move.
 ***********************************************/
void Piece::getMoves(set <Move> & moves, const Board & board) const
{
    
}

/************************************************
 * PIECE : MOVES HELPER
 * Goes in each direction as far as possible to find all possible
 * moves for the sliding piece.
 * Do the same thing for each sliding direction given.
 ***********************************************/
void Piece::movesHelper(set <Move> & moves, const Board & board, Delta * directions, int size) const
{
   for (int i = 0; i < size; i++)
   {
       Delta d = directions[i];
       Position dest = this->position + d;

       bool extending = true;
       while (extending)
       {
           // Cannot move there if it's off the board
           if (dest.isValid())
           {
               const Piece& pieceDest = board[dest];

               // Case if destination piece is a SPACE
               if (pieceDest.getType() == SPACE)
               {
                   Move move = Move(this->position,
                                    dest);
                   moves.insert(move);
                   dest += d;
               }
               // Case if destination piece is opposite team.
               else if (pieceDest.isWhite() != this->isWhite())
               {
                   Move move = Move(this->position,
                                    dest,
                                    move.MOVE,
                                    pieceDest.getType());
                   moves.insert(move);
                   extending = false;
               }
               // Case if destination piece is same team
               else if (pieceDest.isWhite() == this->isWhite())
               {
                   extending = false;
               }
           }
           else // If off board.
           {
               extending = false;
           }
       }
   }
}

/************************************************
 * PIECE : SET POSITION
 * Set a piece's position.
 ***********************************************/
void Piece::setPosition(Position pos)
{
	position = pos;
}
