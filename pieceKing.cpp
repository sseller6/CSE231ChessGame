/***********************************************************************
 * Source File:
 *    KING
 * Author:
*     Josh & Steven
 * Summary:
 *    The King class
 ************************************************************************/

#include "pieceKing.h"
//#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"  


 /***************************************************
 * PIECE DRAW
 * Draw this king.
 ***************************************************/
void King::display(ogstream* pgout) const
{
    pgout->drawKing(this->position, !isWhite());
}

/**********************************************
 * King : GET POSSIBLE MOVES
 * A king can:
 *    Move one space in all 8 directions
 *    Attack one space in all directions
 *    "Castle" in either direction IF:
 *       He has not moved yet
 *       The rook he is castling with has not moved yet
 *       There are no pieces between the two
 *    Be captured (protecting him is outside the scope of this project)
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
    Delta possibleMoves[8] = {
        {  1, -1}, {  1,  0}, {  1,  1},
        {  0, -1},            {  0,  1},
        { -1, -1}, { -1,  0}, { -1,  1}
    };
   
    // Check surroundings
    for (int i = 0; i < 8; i++)
    {
        Delta d = possibleMoves[i];
        Position dest = this->position + d;

        // Cannot move there if it's off the board
        if (dest.isValid())
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
   
    // Check for castle
    if (nMoves == 0)
    {
        int kingRow = fWhite ? 0 : 7;
        
        // Queen side
        bool canQC = board[Position(0, kingRow)].getNMoves() == 0 && board[Position(0, kingRow)].getType() == ROOK;
        
        int col = 3;
        while (canQC && col > 0)
        {
            if (board[Position(col, kingRow)].getType() != SPACE)
            {
                canQC = false;
            }
            col--;
        }
       
        if (canQC)
        {
            Move move = Move(position,
                             Position(2, kingRow),
                             move.CASTLE_QUEEN);
            moves.insert(move);
        }
        
        // King side
        bool canKC = board[Position(7, kingRow)].getNMoves() == 0 && board[Position(7, kingRow)].getType() == ROOK;
        
        col = 5;
        while (canKC && col < 7)
        {
            if (board[Position(col, kingRow)].getType() != SPACE)
            {
                canKC = false;
            }
            col++;
        }
        
        if (canKC)
        {
            Move move = Move(position,
                             Position(6, kingRow),
                             move.CASTLE_KING);
            moves.insert(move);
        }
    }
}
