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
* Draw this queen.
***************************************************/
void Queen::display(ogstream* pgout) const
{
    pgout->drawQueen(this->position, !isWhite());
}

/**********************************************
 * Queen : GET POSSIBLE MOVES
 * A queen can:
 *    Slide vertically
 *    Slide horizontally
 *    Slide diagonally in all four directions
 *    Attack at the end of a slide
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[8] = {
        { -1,  1}, {  0,  1}, {  1,  1},
        { -1,  0},            {  1,  0},
        { -1, -1}, {  0, -1}, {  1, -1},
    };
    movesHelper(moves, board, possibleMoves, 8);
}
