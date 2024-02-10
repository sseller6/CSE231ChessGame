/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Josh & Steven
 * Summary:
 *    The Rook class
 ************************************************************************/

#pragma once

#include <iostream>
using namespace std;

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Rook::display(ogstream* pgout) const
{
    pgout->drawBishop(this->position, !isWhite());
}

/**********************************************
 * Rook : GET POSSIBLE MOVES
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[4] = {
              {  1,  0},
    {  0, -1}, /*ROOK*/ {  0,  1},
              { -1,  0}
    };
    for (int i = 0; i < 4; i++)
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
