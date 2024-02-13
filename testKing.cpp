/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, true);
   Black black(PAWN);
   
   board.board[2][3] = board.board[3][3] = &black;
   board.board[4][3] = board.board[2][4] = &black;
   board.board[4][4] = board.board[2][5] = &black;
   board.board[3][5] = board.board[4][5] = &black;
   
   king.fWhite = false;
   king.position.set(3, 4);
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 0);
   
   // TEARDOWN
   board.board[2][3] = board.board[3][3] = nullptr;
   board.board[4][3] = board.board[2][4] = nullptr;
   board.board[4][4] = board.board[2][5] = nullptr;
   board.board[3][5] = board.board[4][5] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, true);
   White white(PAWN);
   
   board.board[2][3] = board.board[3][3] = &white;
   board.board[4][3] = board.board[2][4] = &white;
   board.board[4][4] = board.board[2][5] = &white;
   board.board[3][5] = board.board[4][5] = &white;
   
   king.fWhite = false;
   king.position.set(3, 4);
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(Move("d5c4p")) != moves.end());
   assertUnit(moves.find(Move("d5d4p")) != moves.end());
   assertUnit(moves.find(Move("d5e4p")) != moves.end());
   assertUnit(moves.find(Move("d5c5p")) != moves.end());
   assertUnit(moves.find(Move("d5e5p")) != moves.end());
   assertUnit(moves.find(Move("d5c6p")) != moves.end());
   assertUnit(moves.find(Move("d5d6p")) != moves.end());
   assertUnit(moves.find(Move("d5e6p")) != moves.end());
   
   // TEARDOWN
   board.board[2][3] = board.board[3][3] = nullptr;
   board.board[4][3] = board.board[2][4] = nullptr;
   board.board[4][4] = board.board[2][5] = nullptr;
   board.board[3][5] = board.board[4][5] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, true);
   
   king.fWhite = false;
   king.position.set(3, 4);
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(Move("d5c4")) != moves.end());
   assertUnit(moves.find(Move("d5d4")) != moves.end());
   assertUnit(moves.find(Move("d5e4")) != moves.end());
   assertUnit(moves.find(Move("d5c5")) != moves.end());
   assertUnit(moves.find(Move("d5e5")) != moves.end());
   assertUnit(moves.find(Move("d5c6")) != moves.end());
   assertUnit(moves.find(Move("d5d6")) != moves.end());
   assertUnit(moves.find(Move("d5e6")) != moves.end());
   
   // TEARDOWN
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, true);
   
   king.fWhite = false;
   king.position.set(0, 0);
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(Move("a1b1")) != moves.end());
   assertUnit(moves.find(Move("a1a2")) != moves.end());
   assertUnit(moves.find(Move("a1b2")) != moves.end());
   
   // TEARDOWN
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, false);
   White white(PAWN);
   Rook rook1 = Rook(0, 0, true);
   Rook rook2 = Rook(7, 0, true);
   
   board.board[3][1] = board.board[4][1] = &white;
   board.board[5][1] = &white;
   board.board[0][0] = &rook1;
   board.board[7][0] = &rook2;
   
   king.fWhite = true;
   king.position.set(4, 0);
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 4);
   assertUnit(moves.find(Move("e1d1")) != moves.end());
   assertUnit(moves.find(Move("e1f1")) != moves.end());
   assertUnit(moves.find(Move("e1c1C")) != moves.end());
   assertUnit(moves.find(Move("e1g1c")) != moves.end());
   
   // TEARDOWN
   board.board[3][1] = board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, true);
   Black black(PAWN);
   Rook rook1 = Rook(0, 7, false);
   Rook rook2 = Rook(7, 7, false);
   
   board.board[3][6] = board.board[4][6] = &black;
   board.board[5][6] = &black;
   board.board[0][7] = &rook1;
   board.board[7][7] = &rook2;
   
   king.fWhite = false;
   king.position.set(4, 7);
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 4);
   assertUnit(moves.find(Move("e8d8")) != moves.end());
   assertUnit(moves.find(Move("e8f8")) != moves.end());
   assertUnit(moves.find(Move("e8c8C")) != moves.end());
   assertUnit(moves.find(Move("e8g8c")) != moves.end());
   
   // TEARDOWN
   board.board[3][6] = board.board[4][6] = nullptr;
   board.board[5][6] = nullptr;
   board.board[0][7] = nullptr;
   board.board[7][7] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, false);
   White white(PAWN);
   Rook rook1 = Rook(0, 0, true);
   Rook rook2 = Rook(7, 0, true);
   
   board.board[3][1] = board.board[4][1] = &white;
   board.board[5][1] = &white;
   board.board[0][0] = &rook1;
   board.board[7][0] = &rook2;
   
   king.fWhite = true;
   king.position.set(4, 0);
   king.nMoves = 1;
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("e1d1")) != moves.end());
   assertUnit(moves.find(Move("e1f1")) != moves.end());
   
   // TEARDOWN
   board.board[3][1] = board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   // SETUP
   BoardEmpty board;
   King king = King(7, 7, false);
   White white(PAWN);
   Rook rook1 = Rook(0, 0, true);
   Rook rook2 = Rook(7, 0, true);
   
   board.board[3][1] = board.board[4][1] = &white;
   board.board[5][1] = &white;
   board.board[0][0] = &rook1;
   board.board[7][0] = &rook2;
   
   king.fWhite = true;
   king.position.set(4, 0);
   rook1.nMoves = 2;
   rook2.nMoves = 2;
   set <Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("e1d1")) != moves.end());
   assertUnit(moves.find(Move("e1f1")) != moves.end());
   
   // TEARDOWN
   board.board[3][1] = board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
   // SETUP
   King king = King(7, 7, false);
   PieceType pt;
   
   // EXERCISE
   pt = king.getType();
   
   // VERIFY
   assertUnit(pt == KING);
   
   // TEARDOWN
}


