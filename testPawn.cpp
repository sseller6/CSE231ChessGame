/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>



 /*************************************
  * GET MOVES TEST Simple
  * White pawn in the middle of the board: b4
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, false);

   pawn.fWhite = true;
   pawn.position.set(1, 3);
   pawn.nMoves = 2;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(Move("b4b5")) != moves.end());
   // TEARDOWN
}

/*************************************
 * GET MOVES TEST Simple
 * Black pawn in the middle of the board: b4
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, true);

   pawn.fWhite = false;
   pawn.position.set(1, 3);
   pawn.nMoves = 3;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   int NUMBA_OF_MOVES = moves.size();

   assertUnit(moves.size() == 1);
   assertUnit(moves.find(Move("b4b3")) != moves.end());
   // TEARDOWN
}


/*************************************
 * GET MOVES TEST InitialAdvance
 * White pawn initial advance
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, false);

   pawn.fWhite = true;
   pawn.position.set(1, 1);
   pawn.nMoves = 0;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b2b3")) != moves.end());
   assertUnit(moves.find(Move("b2b4")) != moves.end());
   // TEARDOWN
}

/*************************************
 * GET MOVES TEST InitialAdvance
 * Black pawn initial advance
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, true);

   pawn.fWhite = false;
   pawn.position.set(2, 6);
   pawn.nMoves = 0;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("c7c6")) != moves.end());
   assertUnit(moves.find(Move("c7c5")) != moves.end());
   // TEARDOWN
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move pawn to b6 and capture
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, false);
   Black black(PAWN);

   board.board[0][6] = board.board[1][6] = &black;
   board.board[2][6] = &black;

   pawn.fWhite = true;
   pawn.position.set(1, 5);
   pawn.nMoves = 4;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   int NUMBAH_OF_MOVES = moves.size();
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b6a7p")) != moves.end());
   assertUnit(moves.find(Move("b6c7p")) != moves.end());
   // TEARDOWN
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move pawn to b6 and capture
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, true);
   White white(PAWN);

   board.board[0][4] = board.board[1][4] = &white;
   board.board[2][4] = &white;

   pawn.fWhite = false;
   pawn.position.set(1, 5);
   pawn.nMoves = 4;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b6a5p")) != moves.end());
   assertUnit(moves.find(Move("b6c5p")) != moves.end());
   // TEARDOWN
}

/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant b5a6E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, false);
   Pawn enemyPawn = Pawn(7, 7, false);

   board.board[0][4] = board.board[1][5] = &enemyPawn;
   board.board[2][4] = &enemyPawn;

   // The black pawns just moved.
   enemyPawn.lastMove = 4;
   // The game is fairly new.
   board.numMoves = 5;

   pawn.fWhite = true;
   pawn.position.set(1, 4);
   pawn.nMoves = 3;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   int NUMBAH_OF_MOVES = moves.size();
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("b5a6p")) != moves.end());
   assertUnit(moves.find(Move("b5c6p")) != moves.end());
   // TEARDOWN
}


/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant f4g3E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, true);
   Pawn enemyPawn = Pawn(7, 7, true);

   board.board[4][3] = board.board[5][2] = &enemyPawn;
   board.board[6][3] = &enemyPawn;

   // The black pawns just moved.
   enemyPawn.lastMove = 4;
   // The game is fairly new.
   board.numMoves = 5;

   pawn.fWhite = false;
   pawn.position.set(5, 3);
   pawn.nMoves = 3;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   int NUMBAH_OF_MOVES = moves.size();
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("f4e3p")) != moves.end());
   assertUnit(moves.find(Move("f4g3p")) != moves.end());
   // TEARDOWN
}

/*************************************
 * GET MOVES TEST Promotion
 * Promotion: b6a7rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, true);
   Pawn enemyPawn = Pawn(7, 7, false);

   board.board[0][7] = board.board[2][7] = &enemyPawn;

   pawn.fWhite = true;
   pawn.position.set(1, 6);
   pawn.nMoves = 5;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   int NUMBAH_OF_MOVES = moves.size();
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(Move("b7a8p")) != moves.end());
   assertUnit(moves.find(Move("b7c8p")) != moves.end());
   assertUnit(moves.find(Move("b7b8Q")) != moves.end());
   // TEARDOWN
}


/*************************************
 * GET MOVES TEST Promotion
 * Promotion: e2d1rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         p   p       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn = Pawn(7, 7, true);
   Pawn enemyPawn = Pawn(7, 7, true);

   board.board[3][0] = board.board[5][0] = &enemyPawn;

   pawn.fWhite = false;
   pawn.position.set(4, 1);
   pawn.nMoves = 5;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   int NUMBAH_OF_MOVES = moves.size();
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(Move("e2d1p")) != moves.end());
   assertUnit(moves.find(Move("e2f1p")) != moves.end());
   assertUnit(moves.find(Move("e2e1Q")) != moves.end());
   // TEARDOWN
}


/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
   // SETUP
   Pawn pawn(7, 7, true);
   PieceType pt;

   // EXERCISE
   pt = pawn.getType();

   // VERIFY
   assertUnit(pt = PAWN);
}  // TEARDOWN

