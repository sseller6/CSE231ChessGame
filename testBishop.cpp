/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/


#include "testBishop.h"
#include "pieceBishop.h"     
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
 * 3     p   p           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop = Bishop(7, 7, true);
   Black black(PAWN);
   
   board.board[1][0] = board.board[1][2] = &black;
   board.board[3][0] = board.board[3][2] = &black;
   
   bishop.fWhite = false;
   bishop.position.set(2, 1);
   set <Move> moves;
   
   // EXERCISE
   bishop.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 0);
   
   // TEARDOWN
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop = Bishop(7, 7, true);
   
   bishop.fWhite = false;
   bishop.position.set(2, 1);
   set <Move> moves;
   
   // EXERCISE
   bishop.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 9);
   assertUnit(moves.find(Move("c2b1")) != moves.end());
   assertUnit(moves.find(Move("c2d1")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2a4")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2h7")) != moves.end());
   
   // TEARDOWN
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop = Bishop(7, 7, true);
   Black black(PAWN);
   
   board.board[1][0] = board.board[3][0] = &black;
   board.board[0][3] = board.board[7][6] = &black;
   
   bishop.fWhite = false;
   bishop.position.set(2, 1);
   set <Move> moves;
   
   // EXERCISE
   bishop.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 5);
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   
   // TEARDOWN
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop = Bishop(7, 7, true);
   White white(PAWN);
   
   board.board[1][0] = board.board[3][0] = &white;
   board.board[0][3] = board.board[7][6] = &white;
   
   bishop.fWhite = false;
   bishop.position.set(2, 1);
   set <Move> moves;
   
   // EXERCISE
   bishop.getMoves(moves, board);
   
   // VERIFY
   assertUnit(moves.size() == 9);
   assertUnit(moves.find(Move("c2b1p")) != moves.end());
   assertUnit(moves.find(Move("c2d1p")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2a4p")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2h7p")) != moves.end());
   
   // TEARDOWN
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
   // SETUP
   Bishop bishop(7, 7, true);
   PieceType pt;
   
   // EXERCISE
   pt = bishop.getType();
   
   // VERIFY
   assertUnit(pt == BISHOP);
   
} // TEARDOWN
