/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    Josh & Steven
 * Summary:
 *    The Queen class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Queen::display(ogstream* pgout) const
{
    pgout->drawQueen(this->position, !isWhite());
}

/**********************************************
 * Queen : GET POSSIBLE MOVES
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[8] = {
            { 1, -1}, { 1,  0}, { 1,  1},
            { 0, -1}, /*QUEEN*/ { 0,  1},
            {-1, -1}, {-1,  0}, {-1,  1},
    };
    for (int i = 0; i < 8; i++)
    {
        Delta d = possibleMoves[i];
        Position dest = this->position + d;

        bool extending = true;
        while (extending)
        {
            // Cannot move there if it's off the board
            if (dest.getCol() != -1 && dest.getRow() != -1)
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
