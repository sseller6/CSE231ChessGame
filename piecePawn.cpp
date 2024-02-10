/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Josh & Steven
 * Summary:
 *    The Pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
* PIECE DRAW
* Draw all the pieces.
***************************************************/
void Pawn::display(ogstream* pgout) const
{
    pgout->drawPawn(this->position, !isWhite());
}

// TODO - Lines 33 through 84 - 2/10/2024

/**********************************************
 * Pawn : GET POSSIBLE MOVES
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
    Delta singleMWhite = {  1,  0};
    Delta doubleMWhite = {  2,  0};
    Delta attackLWhite = {  1, -1};
    Delta attackRWhite = {  1,  1};

    Delta singleMBlack = { -1,  0};
    Delta doubleMBlack = { -2,  0};
    Delta attackLBlack = { -1, -1};
    Delta attackRBlack = { -1,  1};

    Position dest;
    Move move;

    if (fWhite)
    {
        // Check for move
        dest = position + singleMWhite;
        if (board[dest].getType() == SPACE)
        {
            move = Move(position, dest);
            moves.insert(move);
            dest = position + doubleMWhite;
            if (board[dest].getType() == SPACE && nMoves == 0)
            {
                move = Move(position, dest);
                moves.insert(move);
            }
        }

        // Check attacks
        dest = position + attackLWhite;
        if (board[dest].isWhite() != fWhite)
        {
            move = Move(position,
                        dest,
                        move.MOVE,
                        board[dest].getType());
        }

        dest = position + attackRWhite;
        if (board[dest].isWhite() != fWhite)
        {
            move = Move(position,
                dest,
                move.MOVE,
                board[dest].getType());
        }

        // Check for en-passant
        if (position.getRow() == 4)
        {
            // Left
            dest = position + attackLWhite;
            Position checkEP = dest + Delta({ -1, 0 });
            if (board[checkEP].getType() == PAWN &&
                board[checkEP].justMoved(board.getCurrentMove()))
            {
                Move move = Move(position,
                                 dest,
                                 move.ENPASSANT,
                                 PAWN);
                moves.insert(move);
            }

            // Right
            dest = position + attackRWhite;
            checkEP = dest + Delta({ -1, 0 });
            if (board[checkEP].getType() == PAWN &&
                board[checkEP].justMoved(board.getCurrentMove()))
            {
                Move move = Move(position,
                    dest,
                    move.ENPASSANT,
                    PAWN);
                moves.insert(move);
            }
        }
    }

    else
    {
        // Check for move
        dest = position + singleMBlack;
        if (board[dest].getType() == SPACE)
        {
            move = Move(position, dest);
            moves.insert(move);
            dest = position + doubleMBlack;
            if (board[dest].getType() == SPACE && nMoves == 0)
            {
                move = Move(position, dest);
                moves.insert(move);
            }
        }

        // Check attacks
        dest = position + attackLBlack;
        if (board[dest].isWhite() != fWhite)
        {
            move = Move(position,
                dest,
                move.MOVE,
                board[dest].getType());
        }

        dest = position + attackRBlack;
        if (board[dest].isWhite() != fWhite)
        {
            move = Move(position,
                dest,
                move.MOVE,
                board[dest].getType());
        }

        // Check for en-passant
        if (position.getRow() == 3)
        {
            // Left
            dest = position + attackLBlack;
            Position checkEP = dest + Delta({ 1, 0 });
            if (board[checkEP].getType() == PAWN &&
                board[checkEP].justMoved(board.getCurrentMove()))
            {
                Move move = Move(position,
                    dest,
                    move.ENPASSANT,
                    PAWN);
                moves.insert(move);
            }

            // Right
            dest = position + attackRBlack;
            checkEP = dest + Delta({ 1, 0 });
            if (board[checkEP].getType() == PAWN &&
                board[checkEP].justMoved(board.getCurrentMove()))
            {
                Move move = Move(position,
                    dest,
                    move.ENPASSANT,
                    PAWN);
                moves.insert(move);
            }
        }
    }
}
