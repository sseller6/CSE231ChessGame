/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Josh & Steven
 * Summary:
 *    The Rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
* PIECE DRAW
* Draw this rook.
***************************************************/
void Rook::display(ogstream* pgout) const
{
    pgout->drawRook(this->position, !isWhite());
}

/**********************************************
 * Rook : GET POSSIBLE MOVES
 * A rook can:
 *    Slide horizontally
 *    Slide vertically
 *    Attack at the end of a slide
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[4] = {
                 {  0,  1},
       { -1,  0},          {  1,  0},
                 {  0, -1}
    };
    movesHelper(moves, board, possibleMoves, 4);
}
