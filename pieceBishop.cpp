/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    Josh & Steven
 * Summary:
 *    The Bishop class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
* PIECE DRAW
* Draw this bishop.
***************************************************/
void Bishop::display(ogstream* pgout) const
{
    pgout->drawBishop(this->position, !isWhite());
}


/**********************************************
 * Bishop : GET POSSIBLE MOVES
 * A bishop can:
 *    Slide diagonally in all four directions
 *    Attack at the end of a slide
 *********************************************/
void Bishop::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[4] = {
        { -1,  1}, {  1,  1},
       
        { -1, -1}, {  1, -1}
    };
    movesHelper(moves, board, possibleMoves, 4);
}
