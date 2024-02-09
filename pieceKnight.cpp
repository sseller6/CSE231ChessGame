/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    Josh & Steven
 * Summary:
 *    The knight class
 ************************************************************************/

#include <iostream>
using namespace std;

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
    pgout->drawKnight(this->position, !isWhite());
}


/**********************************************
 * KNIGHT : GET POSSIBLE MOVES
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   Delta possibleMoves[8] = {
                { 2, -1}, { 2,  1},
      { 1, -2},                    { 1,  2},
      
      {-1, -2},                    { -1,  2},
                {-2, -1}, {-2,  1}
   };
   for (int i = 0; i < 8; i++)
   {
      Delta d = possibleMoves[i];
      Position dest = this->position + d;
      
      // Cannot move there if it's off the board
      if (dest.getCol() != -1)
      {
         if (dest.getRow() != -1)
         {
            // or occupied by a piece of same team
            const Piece& pieceDest = board[dest];
            if (pieceDest.isWhite() != this->isWhite() || pieceDest.getType() == SPACE)
            {
               bool isCapture = pieceDest.getType() != SPACE;
               Move move = Move(this->position,
                                dest,
                                move.MOVE,
                                isCapture ? pieceDest.getType() : SPACE);
               moves.insert(move);
            }
         }
      }
   }
}
