/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>




/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3     p p p           3
 * 2     p(q)p           2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Queen queen = Queen(7, 7, true);
   Black black(PAWN);
   
   board.board[1][0] = board.board[2][0] = &black;
   board.board[3][0] = board.board[1][1] = &black;
   board.board[3][1] = board.board[1][2] = &black;
   board.board[2][2] = board.board[3][2] = &black;

   queen.fWhite = false;
   queen.position.set(2, 1);
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[1][0] = board.board[2][0] = nullptr;
   board.board[3][0] = board.board[1][1] = nullptr;
   board.board[3][1] = board.board[1][2] = nullptr;
   board.board[2][2] = board.board[3][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Queen queen = Queen(7, 7, true);

   queen.fWhite = false;
   queen.position.set(2, 1);
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);

   // First Row
   assertUnit(moves.find(Move("c2c1")) != moves.end());
   assertUnit(moves.find(Move("c2b1")) != moves.end());
   assertUnit(moves.find(Move("c2d1")) != moves.end());
   // Second Row
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2a2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2h2")) != moves.end());
   // Third Row
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   // Diagonals
   assertUnit(moves.find(Move("c2a4")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2h7")) != moves.end());
   // Column C
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   assertUnit(moves.find(Move("c2c8")) != moves.end());
   // TEARDOWN
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Queen queen = Queen(7, 7, true);
   Black black(PAWN);

   board.board[1][0] = board.board[2][0] = &black;
   board.board[3][0] = board.board[0][1] = &black;
   board.board[7][1] = board.board[0][3] = &black;
   board.board[2][7] = board.board[7][6] = &black;

   queen.fWhite = false;
   queen.position.set(2, 1);
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 15);

   // Second Row
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   // Third Row
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   // Diagonals
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   // Column C
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   
   // TEARDOWN
   board.board[1][0] = board.board[2][0] = nullptr;
   board.board[3][0] = board.board[0][1] = nullptr;
   board.board[7][1] = board.board[0][3] = nullptr;
   board.board[2][7] = board.board[7][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Queen queen = Queen(7, 7, true);
   White white(PAWN);

   board.board[1][0] = board.board[2][0] = &white;
   board.board[3][0] = board.board[0][1] = &white;
   board.board[7][1] = board.board[0][3] = &white;
   board.board[2][7] = board.board[7][6] = &white;

   queen.fWhite = false;
   queen.position.set(2, 1);
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);

   // First Row
   assertUnit(moves.find(Move("c2c1p")) != moves.end());
   assertUnit(moves.find(Move("c2b1p")) != moves.end());
   assertUnit(moves.find(Move("c2d1p")) != moves.end());
   // Second Row
   assertUnit(moves.find(Move("c2b2"))  != moves.end());
   assertUnit(moves.find(Move("c2a2p")) != moves.end());
   assertUnit(moves.find(Move("c2d2"))  != moves.end());
   assertUnit(moves.find(Move("c2e2"))  != moves.end());
   assertUnit(moves.find(Move("c2f2"))  != moves.end());
   assertUnit(moves.find(Move("c2g2"))  != moves.end());
   assertUnit(moves.find(Move("c2h2p")) != moves.end());
   // Third Row
   assertUnit(moves.find(Move("c2b3"))  != moves.end());
   assertUnit(moves.find(Move("c2d3"))  != moves.end());
   // Diagonals
   assertUnit(moves.find(Move("c2a4p")) != moves.end());
   assertUnit(moves.find(Move("c2d3"))  != moves.end());
   assertUnit(moves.find(Move("c2e4"))  != moves.end());
   assertUnit(moves.find(Move("c2f5"))  != moves.end());
   assertUnit(moves.find(Move("c2g6"))  != moves.end());
   assertUnit(moves.find(Move("c2h7p")) != moves.end());
   // Column C
   assertUnit(moves.find(Move("c2c3"))  != moves.end());
   assertUnit(moves.find(Move("c2c4"))  != moves.end());
   assertUnit(moves.find(Move("c2c5"))  != moves.end());
   assertUnit(moves.find(Move("c2c6"))  != moves.end());
   assertUnit(moves.find(Move("c2c7"))  != moves.end());
   assertUnit(moves.find(Move("c2c8p")) != moves.end());
   
   // TEARDOWN
   board.board[1][0] = board.board[2][0] = nullptr;
   board.board[3][0] = board.board[0][1] = nullptr;
   board.board[7][1] = board.board[0][3] = nullptr;
   board.board[2][7] = board.board[7][6] = nullptr;
}


/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
   // SETUP
   Queen queen(7, 7, true);
   PieceType pt;
   
   // EXERCISE
   pt = queen.getType();

   // VERIFY
   assertUnit(pt == QUEEN);
}   // TEARDOWN
