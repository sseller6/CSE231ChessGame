/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    Josh & Steven
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceRook.h"
#include "pieceKnight.h"
#include "pieceBishop.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include "piecePawn.h"
#include <cassert>
using namespace std;


/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8   R N B Q K B N R   8
 *   7   P P P P P P P P   7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2   p p p p p p p p   2
 *   1   r n b q k b n r   1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything that's not empty
   if (fFree)
      free();
   else
   {
      // Insert Rooks
      board[0][0] = new Rook(0, 0, true);
      board[7][0] = new Rook(7, 0, true);
      board[0][7] = new Rook(0, 7, false);
      board[7][7] = new Rook(7, 7, false);
      // Insert Knights
      board[1][0] = new Knight(1, 0, true);
      board[6][0] = new Knight(6, 0, true);
      board[1][7] = new Knight(1, 7, false);
      board[6][7] = new Knight(6, 7, false);
      // Insert Bishops
      board[2][0] = new Bishop(2, 0, true);
      board[5][0] = new Bishop(5, 0, true);
      board[2][7] = new Bishop(2, 7, false);
      board[5][7] = new Bishop(5, 7, false);
      // Insert Queens
      board[3][0] = new Queen(3, 0, true);
      board[3][7] = new Queen(3, 7, false);
      // Insert Kings
      board[4][0] = new King(4, 0, true);
      board[4][7] = new King(4, 7, false);
      // Insert Pawns
      board[0][1] = new Pawn(0, 1, true);
      board[1][1] = new Pawn(1, 1, true);
      board[2][1] = new Pawn(2, 1, true);
      board[3][1] = new Pawn(3, 1, true);
      board[4][1] = new Pawn(4, 1, true);
      board[5][1] = new Pawn(5, 1, true);
      board[6][1] = new Pawn(6, 1, true);
      board[7][1] = new Pawn(7, 1, true);
      board[0][6] = new Pawn(0, 6, false);
      board[1][6] = new Pawn(1, 6, false);
      board[2][6] = new Pawn(2, 6, false);
      board[3][6] = new Pawn(3, 6, false);
      board[4][6] = new Pawn(4, 6, false);
      board[5][6] = new Pawn(5, 6, false);
      board[6][6] = new Pawn(6, 6, false);
      board[7][6] = new Pawn(7, 6, false);
      
      for (int r = 0; r < 8; r++)
      {
         for (int c = 0; c < 8; c++)
         {
            if (!board[c][r])
               board[c][r] = new Space(c, r);
         }
      }
      
   }
}

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   return *board[pos.getCol()][pos.getRow()];
}
Piece& Board::operator [] (const Position& pos)
{
   return *board[pos.getCol()][pos.getRow()];
}

 /***********************************************
 * BOARD : DISPLAY
 *         Display the board
 ***********************************************/
void Board::display(const Position & posHover, const Position & posSelect) const
{
   pgout->drawBoard();
   pgout->drawHover(posHover);
   pgout->drawSelected(posSelect);
   for (int r = 0; r < 8; r++)
   {
      for (int c = 0; c < 8; c++)
      {
         board[c][r]->display(pgout);
      }
   }
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   if (noreset)
      free();
   else
      reset();
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (board[c][r])
            {
                // TDOD: implement DELETE
                // delete board[c][r];
                board[c][r] = nullptr;
            }
        }
    }
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{

}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{  
   Position src = move.getSource();
   Position des = move.getDestination();
   
   int srcCol = src.getCol();
   int srcRow = src.getRow();
   int desCol = des.getCol();
   int desRow = des.getRow();
   
   Piece * pieceMove = board[srcCol][srcRow];
   Piece * pieceDest = board[desCol][desRow];
   
   // If only move
   if (move.getMoveType() == move.MOVE && !move.isCapture())
   {
      board[desCol][desRow] = pieceMove;
      board[srcCol][srcRow] = pieceDest;
   }
   
   // If capture
   else if (move.isCapture())
   {
      Piece * replace = new Space(srcCol, srcRow);
      board[desCol][desRow] = pieceMove;
      board[srcCol][srcRow] = replace;
      
      // If en-passant
      //if (move)
   }

   // TODO: write ENPASSANT and PROMOTE
   
   numMoves++;
}



/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty() 
{
   delete pSpace;
}
