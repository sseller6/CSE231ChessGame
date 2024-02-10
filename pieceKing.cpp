/***********************************************************************
 * Source File:
 *    KING
 * Author:
*     Josh & Steven
 * Summary:
 *    The King class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"  


 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void King::display(ogstream* pgout) const
{
    pgout->drawKing(this->position, !isWhite());
}

/**********************************************
 * King : GET POSSIBLE MOVES
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[8] = {
                     
            { 1, -1}, { 1,  0}, { 1,  1},
            { 0, -1}, /*KING*/  { 0,  1},
            {-1, -1}, {-1,  0}, {-1,  1},
                     
    };
    for (int i = 0; i < 8; i++)
    {
        Delta d = possibleMoves[i];
        Position dest = this->position + d;

        // Cannot move there if it's off the board
        if (dest.getCol() != -1 && dest.getRow() != -1)
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
