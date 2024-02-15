/**********************************************************************
* Source File:
*    Lab 04: Chess
* Author:
*    Josh & Steven
* Summary:
*    Play the game of chess
************************************************************************/


#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for OGSTREAM
#include "position.h"     // for POSITION
#include "piece.h"        // for PIECE and company
#include "board.h"        // for BOARD
#include "test.h"
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface *pUI, void * p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Board * pBoard = (Board *)p;
   
   Position prev = pUI->getPreviousPosition();
   Position curr = pUI->getSelectPosition();
   if (prev.isValid() && curr.isValid())
   {
       Piece* piecePrev = &(*pBoard)[prev];
       if (prev != curr && piecePrev->getType() != SPACE)
       {
           set <Move> possible;
           piecePrev->getMoves(possible, *pBoard);
           // Find the move whose destination matches the user's current click
           set<Move>::iterator it;
           for (it = possible.begin(); it != possible.end(); it++)
           {
               if (it->getDestination() == curr)
               {
                   pBoard->move(*it);
                   pUI->clearSelectPosition();
                   pUI->clearPreviousPosition();
               }
           }
       }
   }
   
   pBoard->display(pUI->getHoverPosition(), pUI->getSelectPosition());
}


/*********************************
 * MAIN - Where it all begins...
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{

   // run all the unit tests
   testRunner();
   
   // Instantiate the graphics window
   Interface ui("Chess");    

   // Initialize the game class
   ogstream* pgout = new ogstream;
   Board board(pgout);

   // set everything into action
   ui.run(callBack, (void *)(&board));      
   
   // All done.
   delete pgout;
   return 0;
}
