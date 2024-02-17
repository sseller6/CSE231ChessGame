/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Josh & Steven
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board.
 ************************************************************************/

#include "position.h"
#include <cstring>
#include <iostream>

/******************************************
 * POSITION INSERTION OPERATOR
 ******************************************/
ostream & operator << (ostream & out, const Position & rhs)
{
   out << "error";
   return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream & operator >> (istream & in,  Position & rhs)
{
   return in;
}


/*************************************
 * POSITION get column
 **************************************/
int Position::getCol() const
{
   if (isInvalid())
   {
      return -1;
   }
   int col = (int)colRow / 16;
   return col;
}

/*************************************
 * POSITION get row
 **************************************/
int Position::getRow() const
{
   if (isInvalid())
   {
      return -1;
   }
   int row = (int)colRow % 16;
   return row;
}

/*************************************
 * POSITION is invalid
 **************************************/
bool Position::isInvalid() const
{
   int col = (int)colRow / 16;
   int row = (int)colRow % 16;
   if (0 > col || col > 7 || 0 > row || row > 7)
      return true;
   return false;
}

/*************************************
 * POSITION is valid
 **************************************/
bool Position::isValid() const
{
   int col = (int)colRow / 16;
   int row = (int)colRow % 16;
   if (0 <= col && col <= 7 && 0 <= row && row <= 7)
      return true;
   return false;
}

/*************************************
 * POSITION get location
 **************************************/
int Position::getLocation() const
{
   // Row is given by 0xf0. Col is given by 0x0f
   return (colRow % 16) * 8 + (colRow / 16);
}

/*************************************
 * POSITION set row
 **************************************/
void Position::setRow(int r)
{
   int col = colRow / 16;
   colRow = (uint8_t)(col * 16 + r);
}

/*************************************
 * POSITION set column
 **************************************/
void Position::setCol(int c)
{
   int row = colRow % 16;
   colRow = (uint8_t)(c * 16 + row);
}

/*************************************
 * POSITION set column and row
 **************************************/
void Position::set(int c, int r)
{
   colRow = (uint8_t)(c * 16 + r);
}

/*************************************
 * POSITION set location
 **************************************/
void Position::setLocation(int location)
{
   int col = location % 8;
   int row = location / 8;
   colRow = (uint8_t)(col * 16 + row);
}

/*************************************
 * POSITION set x and y
 **************************************/
void Position::setXY(double x, double y)
{
   // TODO: is this where we worry about border resizing?
   
   // Fix y according to flippage
   double flipped_y = (8.0 * squareHeight + 2.0 * OFFSET_BOARD) - y;
   
   // Fix x and y according to border offset
   double real_x =         x - OFFSET_BOARD;
   double real_y = flipped_y - OFFSET_BOARD;
   
   // Scale back down to col and row
   int fix_x = real_x / squareWidth;
   int fix_y = real_y / squareHeight;
   
   // Set according to fixed values
   set(fix_x, fix_y);
}

/*************************************
 * POSITION set text-based
 **************************************/
void Position::set(const char * s)
{
   if ((s[0] < 'A' || s[0] > 'H') && (s[0] < 'a' || s[0] > 'h'))
      setInvalid();
   else if (s[1] < '1' || s[1] > '8')
      setInvalid();
   else
      set(s[0] - 'a', s[1] - '1');
}

/*************************************
 * POSITION text-based constructor
 **************************************/
Position::Position(const char * s)
{
   set(s);
}

/*************************************
 * POSITION ASSIGNMENT OPERATOR char *
 **************************************/
const Position & Position::operator = (const char * rhs)
{
   set(rhs);
   return *this;
}

/*************************************
 * POSITION ASSIGNMENT OPERATOR string
 **************************************/
const Position & Position::operator = (const string & rhs)
{
   const char* char_rhs = rhs.c_str();
   set(char_rhs);
   return *this;
}

/*************************************
 * POSITION ADDITION ASSIGNMENT OPERATOR delta
 **************************************/
const Position & Position::operator += (const Delta & rhs)
{
   if (isValid())
   {
      int adjustC = rhs.dCol;
      int adjustR = rhs.dRow;
      this->colRow += (adjustC * 16 + adjustR);
   }
   if (isInvalid())
   {
      this->colRow = 0xff;
   }
   return *this;
}

/*************************************
 * POSITION ADDITION OPERATOR delta
 **************************************/
Position Position::operator+ (const Delta & rhs) const
{
   return Position(getCol() + rhs.dCol, getRow() + rhs.dRow);
}
