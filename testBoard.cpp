/***********************************************************************
 * Source File:
 *    TEST BOARD
 * Author:
 *    Josh & Steven
 * Summary:
 *    The unit tests for board
 ************************************************************************/


#include "testBoard.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceRook.h"
#include "pieceKnight.h"
#include "pieceBishop.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include "piecePawn.h"
#include "board.h"
#include <cassert>



 /********************************************************
  *   a2a3
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3   .                 3       3   p                 3
  * 2  (p)                2       2   .                 2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_pawnSimple()
{
   // SETUP
   Board board = Board(nullptr, true);
   Pawn * pawn = new Pawn(7, 7, false);
   Space space = Space(7, 7);
   
   pawn->fWhite = true;
   pawn->position.set(0, 1);
   pawn->nMoves = 0;
   
   space.position.set(0, 2);
   
   board.board[0][1] = pawn;
   board.board[0][2] = &space;
   
   Move move = Move(Position(0, 1), Position(0, 2));
   
   // EXERCISE
   board.move(move);
   
   // VERIFY
   assertUnit(board.board[0][1]->getType() == SPACE);
   assertUnit(board.board[0][2]->getType() == PAWN);
   
   // TEARDOWN
   delete pawn;
   board.board[0][1] = board.board[0][2] = nullptr;
}


 /********************************************************
  *     a6b7r
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7     R               7       7    (p)              7
  * 6  (p)                6       6   .                 6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_pawnCapture()
{
   // SETUP
   Board board = Board(nullptr, true);
   Pawn * pawn = new Pawn(7, 7, false);
   Rook * rook = new Rook(7, 7, true);
   
   pawn->fWhite = true;
   pawn->position.set(0, 5);
   pawn->nMoves = 3;
   rook->fWhite = false;
   rook->position.set(1, 6);
   
   board.board[0][5] = pawn;
   board.board[1][6] = rook;
   
   Move move = Move(Position(0, 5), Position(1, 6));
   move.capture = ROOK;
   
   // EXERCISE
   board.move(move);
   
   // VERIFY
   assertUnit(board.board[0][5]->getType() == SPACE);
   assertUnit(board.board[1][6]->getType() == PAWN);
   
   // TEARDOWN
   delete pawn;
   board.board[0][5] = board.board[1][6] = nullptr;
}


 /********************************************************
  *    e2e4
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4           .         4  -->  4          (p)        4
  * 3                     3       3                     3
  * 2          (p)        2       2           .         2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_pawnDouble()
{
   // SETUP
   Board board = Board(nullptr, true);
   Pawn * pawn = new Pawn(7, 7, false);
   Space space = Space(7, 7);
   
   pawn->fWhite = true;
   pawn->position.set(4, 1);
   pawn->nMoves = 0;
   space.position.set(4, 3);
   
   board.board[4][1] = pawn;
   board.board[4][3] = &space;
   
   Move move = Move(Position(4, 1), Position(4, 3));
   
   // EXERICE
   board.move(move);
   
   // VERIFY
   assertUnit(board.board[4][1]->getType() == SPACE);
   assertUnit(board.board[4][3]->getType() == PAWN);
   
   // TEARDOWN
   delete pawn;
   board.board[4][1] = board.board[4][3] = nullptr;
}


 /********************************************************
 *     a5b6E
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6     .               6       6     p               6
  * 5  (p)P               5       5   . .               5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_pawnEnpassant()
{
   // SETUP
   Board board = Board(nullptr, true);
   Pawn * pawn_w = new Pawn(7, 7, true);
   Pawn * pawn_b = new Pawn(7, 7, true);
   
   pawn_w->fWhite = true;
   pawn_w->position.set(0, 4);
   pawn_w->nMoves = 3;
   
   pawn_b->fWhite = false;
   pawn_b->position.set(1, 4);
   pawn_b->nMoves = 1;
   pawn_b->lastMove = 5;
   
   board.numMoves = 5;
   board.board[0][4] = pawn_w;
   board.board[1][4] = pawn_b;
   
   Move move = Move(Position(0, 4), Position(1, 5));
   move.capture = PAWN;
   move.moveType = Move::ENPASSANT;
   
   // EXERCISE
   board.move(move);
   
   // VERIFY
   assertUnit(board.board[0][4]->getType() == SPACE);
   assertUnit(board.board[1][4]->getType() == SPACE);
   assertUnit(board.board[1][5]->getType() == PAWN);
   
   // TEARDOWN
   delete pawn_w;
   board.board[0][4] = board.board[1][4] = board.board[1][5] = nullptr;
}


 /********************************************************
  *    a7a8Q 
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8   .                 8       8  (q)                8
  * 7  (p)                7       7   .                 7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_pawnPromotion()
{
   // SETUP
   Board board = Board(nullptr, true);
   Pawn * pawn = new Pawn(7, 7, true);
   Space space = Space(7, 7);
   
   pawn->fWhite = true;
   pawn->position.set(0, 6);
   
   space.position.set(0, 7);
   
   board.board[0][6] = pawn;
   board.board[0][7] = &space;
   
   Move move = Move(Position(0, 6), Position(0, 7));
   move.promote = QUEEN;
   
   // EXERCISE
   board.move(move);
   
   // VERIFY
   assertUnit(board.board[0][6]->getType() == SPACE);
   assertUnit(board.board[0][7]->getType() == QUEEN);
   
   // TEARDOWN
   delete board.board[0][7];
   board.board[0][6] = board.board[0][7] = nullptr;
}


 /********************************************************
  *    e5a5
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5   .      (r)        5       5  (r)      .         5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_rookSlide()
{
	//   // SETUP
	Board board = Board();
	Rook* rook = new Rook(7, 7, false);
	Space space = Space(7, 7);

	rook->fWhite = true;
	rook->position.set(4, 4);
	space.position.set(0, 4);

	board.board[4][4] = rook;
	board.board[0][4] = &space;
	Move move = Move(Position(4, 4), Position(0, 4));

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(board.board[4][4]->getType() == SPACE);
	assertUnit(board.board[0][4]->getType() == ROOK);

	// TEARDOWN
	delete rook;
	board.board[4][4] = board.board[0][4] = nullptr;
}


 /********************************************************
  *    e5a5b
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5   B      (r)        5       5  (r)      .         5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_rookAttack()
{
	// SETUP
	Board board = Board();
	Rook* rook = new Rook(7, 7, false);
	Bishop* bishop = new Bishop(7, 7);

	rook->fWhite = true;
	bishop->fWhite = false;
	rook->position.set(4, 4);
	bishop->position.set(0, 4);

	board.board[4][4] = rook;
	board.board[0][4] = bishop;
	Move move = Move(Position(4, 4), Position(0, 4));
	move.capture = BISHOP;

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(board.board[4][4]->getType() == SPACE);
	assertUnit(board.board[0][4]->getType() == ROOK);

	// TEARDOWN
	delete rook;
	board.board[4][4] = board.board[0][4] = nullptr;
}

 /********************************************************
  *    e5g3
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5          (b)        5       5           .         5
  * 4                     4  -->  4                     4
  * 3               .     3       3               b     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_bishopSlide()
{
	//   // SETUP
	Board board = Board();
	Bishop* bishop = new Bishop(7, 7, false);
	Space space = Space(7, 7);

	bishop->fWhite = true;
	bishop->position.set(4, 4);
	space.position.set(6, 2);

	board.board[4][4] = bishop;
	board.board[6][2] = &space;
	Move move = Move(Position(4, 4), Position(6, 2));

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(board.board[4][4]->getType() == SPACE);
	assertUnit(board.board[6][2]->getType() == BISHOP);

	// TEARDOWN
	delete bishop;
	board.board[4][4] = board.board[6][2] = nullptr;
}


 /********************************************************
  *    e5g3q
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5          (b)        5       5           .         5
  * 4                     4  -->  4                     4
  * 3               Q     3       3               b     3
  * 2                     2       2                     2
  * 1                     1       1                     1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_bishopAttack()
{
	//   // SETUP
	Board board = Board();
	Bishop* bishop = new Bishop(7, 7, false);
	Queen* queen = new Queen(7, 7);

	bishop->fWhite = true;
	queen->fWhite = false;
	bishop->position.set(4, 4);
	queen->position.set(6, 2);

	board.board[4][4] = bishop;
	board.board[6][2] = queen;
	Move move = Move(Position(4, 4), Position(6, 2));
	move.capture = BISHOP;

	// EXERCISE
	board.move(move);

	// VERIFY
	assertUnit(board.board[4][4]->getType() == SPACE);
	assertUnit(board.board[6][2]->getType() == BISHOP);

	// TEARDOWN
	delete bishop;
	board.board[4][4] = board.board[6][2] = nullptr;
}
/********************************************************
*    e5a5b
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
* |                     |       |                     |
* 8                     8       8                     8
* 7                     7       7                     7
* 6                     6       6                     6
* 5          (n)        5       5           .         5
* 4                     4  -->  4                     4
* 3         p           3       3         n           3
* 2                     2       2                     2
* 1                     1       1                     1
* |                     |       |                     |
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
********************************************************/
void TestBoard::move_knightAttack()
{
   // SETUP
   Board board = Board();
   Knight* knight = new Knight(7, 7, false);
   Pawn* pawn = new Pawn(7, 7);

   knight->fWhite = true;
   pawn->fWhite = false;
   knight->position.set(4, 4);
   pawn->position.set(3, 2);

   board.board[4][4] = knight;
   board.board[3][2] = pawn;
   Move move = Move(Position(4, 4), Position(3, 2));
   move.capture = PAWN;

   // EXERCISE
   board.move(move);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[3][2]->getType() == KNIGHT);

   // TEARDOWN
   delete knight;
   board.board[4][4] = board.board[3][2] = nullptr;
}

/********************************************************
 *    e5g3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (n)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3             .       3       3             n       3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_knightMove()
{
   // SETUP
   Board board = Board();
   Knight* knight = new Knight(7, 7, false);
   Space space = Space(7, 7);

   knight->fWhite = true;
   knight->position.set(4, 4);
   space.position.set(5, 2);

   board.board[4][4] = knight;
   board.board[5][2] = &space;
   Move move = Move(Position(4, 4), Position(5, 2));

   // EXERCISE
   board.move(move);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[5][2]->getType() == KNIGHT);

   // TEARDOWN
   delete knight;
   board.board[4][4] = board.board[5][2] = nullptr;
}

/********************************************************
 *    e5g3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (q)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3                .    3       3               q     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_queenSlide()
{
   // SETUP
   Board board = Board();
   Queen * queen = new Queen(7, 7, false);
   Space space = Space(7, 7);

   queen->fWhite = true;
   queen->position.set(4, 4);
   space.position.set(6, 2);

   board.board[4][4] = queen;
   board.board[6][2] = &space;
   Move move = Move(Position(4, 4), Position(6, 2));

   // EXERCISE
   board.move(move);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[6][2]->getType() == QUEEN);

   // TEARDOWN
   delete queen;
   board.board[4][4] = board.board[6][2] = nullptr;
}


/********************************************************
*    e5a5b
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
* |                     |       |                     |
* 8                     8       8                     8
* 7                     7       7                     7
* 6                     6       6                     6
* 5   B      (q)        5       5  (q)      .         5
* 4                     4  -->  4                     4
* 3                     3       3                     3
* 2                     2       2                     2
* 1                     1       1                     1
* |                     |       |                     |
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
********************************************************/
void TestBoard::move_queenAttack()
{
   // SETUP
   Board board   = Board();
   Queen * queen   = new Queen(7, 7, false);
   Bishop * bishop = new Bishop(7, 7);

   queen->fWhite = true;
   bishop->fWhite = false;
   queen->position.set(4, 4);
   bishop->position.set(0, 4);

   board.board[4][4] = queen;
   board.board[0][4] = bishop;
   Move move = Move(Position(4, 4), Position(0, 4));
   move.capture = BISHOP;

   // EXERCISE
   board.move(move);

   // VERIFY
   assertUnit(board.board[4][4]->getType() == SPACE);
   assertUnit(board.board[0][4]->getType() == QUEEN);

   // TEARDOWN
   delete queen;
   board.board[4][4] = board.board[0][4] = nullptr;
}


 /********************************************************
  *  e1f1
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1          (k).       1       1           . k       1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_kingMove()
{
   // SETUP
   Board board = Board();
   King* king = new King(7, 7, false);
   Space space = Space(7, 7);

   king->fWhite = true;
   king->position.set(4, 0);
   space.position.set(5, 0);

   board.board[4][0] = king;
   board.board[5][0] = &space;
   Move move = Move(Position(4, 0), Position(5, 0));

   // EXERCISE
   board.move(move);

   // VERIFY
   assertUnit(board.board[4][0]->getType() == SPACE);
   assertUnit(board.board[5][0]->getType() == KING);

   // TEARDOWN
   delete king;
   board.board[4][0] = board.board[5][0] = nullptr;
}


 /********************************************************
  *    e1f1r
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1          (k)R       1       1           . k       1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_kingAttack()
{
   // SETUP
   Board board = Board();
   King* king = new King(7, 7, false);
   Rook* rook = new Rook(7, 7);

   king->fWhite = true;
   rook->fWhite = false;
   king->position.set(4, 0);
   rook->position.set(5, 0);

   board.board[4][0] = king;
   board.board[5][0] = rook;
   Move move = Move(Position(4, 0), Position(5, 0));
   move.capture = BISHOP;

   // EXERCISE
   board.move(move);

   // VERIFY
   assertUnit(board.board[4][0]->getType() == SPACE);
   assertUnit(board.board[5][0]->getType() == KING);

   // TEARDOWN
   delete king;
   board.board[4][0] = board.board[5][0] = nullptr;
}

 /********************************************************
  *    e1g1c
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1          (k). . r   1       1           . r k .   1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_kingShortCastle()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}



 /********************************************************
  *    e1c1C 
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  * |                     |       |                     |
  * 8                     8       8                     8
  * 7                     7       7                     7
  * 6                     6       6                     6
  * 5                     5       5                     5
  * 4                     4  -->  4                     4
  * 3                     3       3                     3
  * 2                     2       2                     2
  * 1   r . . .(k)        1       1   . . k r .         1
  * |                     |       |                     |
  * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_kingLongCastle()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}




/******************************************************** 
 *        +---a-b-c-d-e-f-g-h---+
 *        |                     |
 *        8   R N B Q K B N R   8
 *        7   P P P P P P P P   7
 *        6                     6
 *        5                     5
 *   -->  4                     4
 *        3                     3
 *        2   p p p p p p p p   2
 *        1   r n b q k b n r   1
 *        |                     |
 *        +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::construct_default()
{
   assertUnit(NOT_YET_IMPLEMENTED);
}
