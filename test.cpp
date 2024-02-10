/***********************************************************************
 * Source File:
 *    TEST
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPiece.h"
#include "testSpace.h"
#include "testRook.h"
#include "testKnight.h"
#include "testBishop.h"
#include "testQueen.h"
#include "testKing.h"
#include "testPawn.h"
#include "testPosition.h"
#include "testBoard.h"
#include "testMove.h"

#ifdef _WIN32
#include <windows.h>
#include <iostream>
using namespace std;
#endif


int PieceSpy::numConstruct = 0;
int PieceSpy::numCopy = 0;
int PieceSpy::numDelete = 0;
int PieceSpy::numAssign = 0;
int PieceSpy::numMove = 0;

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
#ifdef _WIN32
   AllocConsole();
   FILE* stream;
   errno_t err;
   err = freopen_s(&stream, "CONOUT$", "a", stdout);
#endif // _WIN32

   // unit tests
   PositionTest().run();
   TestMove().run();
   TestBoard().run();
   TestPiece().run();
   TestSpace().run();
   TestRook().run();
   TestKnight().run();
   TestBishop().run();
   TestQueen().run();
   TestKing().run();
   TestPawn().run();
}
