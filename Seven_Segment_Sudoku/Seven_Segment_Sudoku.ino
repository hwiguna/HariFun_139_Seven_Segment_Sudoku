
// Seven Segment Sudoku - Hari Wiguna, 2016

// v0.04 - Draw one digit per interrupt.
//         Drawing the whole column (9 vertical digits) took longer than interrupt cycle.
//         Now we leave the column alone while we draw a new row for the upcoming column at each interrupt.
//         When we're done with all the rows, we turn off the column, slam the segments to the display, turn on the correct column.

// v0.03 - Use POV (Persistence Of Vision) to draw all digits "simultaneously".
//         Refresh function that is periodically called by interrupt draws the sudoku independent of main loop.

// v0.02 - Create an array to represent Sudoku grid and display it.

// v0.01 - Display actual digits 1..9

// v0.00 - Proof that we could control every segment of NINE digits.
//        One Shift Register drives the segments + decimal point.
//        Another Shift Register drives 8 columns (digits).
//        D8 drives the 9th column (digit).

//== Arduino Pin configuration ==
const byte COL_CLK_PIN = 2;
const byte COL_LATCH_PIN = 3;
const byte COL_SER_PIN = 4;

const byte COL_8_PIN = 8; // Shift register only has 8 columns, so handle 9th column special

const byte SEG_CLK_PIN = 5;
const byte SEG_LATCH_PIN = 6;
const byte SEG_SER_PIN = 7;

//== Digit bitmaps ==
volatile byte digitBits[] = {
  B00000000, // 0
  B00001100, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};

//== Sudoku Variables ==
byte sudoku[][9] = {
  {1, 2, 3, 0, 0, 6, 7, 0, 9},
  {2, 3, 4, 5, 6, 7, 8, 9, 1},
  {3, 4, 5, 6, 7, 8, 9, 1, 2},

  {4, 5, 6, 7, 8, 9, 1, 2, 3},
  {5, 6, 7, 8, 9, 1, 2, 3, 4},
  {6, 7, 8, 9, 1, 2, 3, 4, 5},

  {7, 8, 9, 1, 2, 3, 4, 5, 6},
  {8, 9, 1, 2, 3, 4, 5, 6, 7},
  {9, 1, 2, 3, 4, 5, 6, 7, 8}
};

volatile int8_t gRow = 0;
volatile int8_t gCol = 0;
#include "ScreenRefresh.h"

void setup() {
  pinMode(COL_CLK_PIN, OUTPUT);
  pinMode(COL_LATCH_PIN, OUTPUT);
  pinMode(COL_SER_PIN, OUTPUT);
  pinMode(SEG_CLK_PIN, OUTPUT);
  pinMode(SEG_LATCH_PIN, OUTPUT);
  pinMode(SEG_SER_PIN, OUTPUT);
  pinMode(COL_8_PIN, OUTPUT);

  EraseAll();
  FillSudoku1();

  SetupTimer();
}

void SegmentTest()
{
  //== Scan through all the segments ===
  for (byte seg = 0; seg < 8; seg++)
  {
    byte segByte = 0;
    bitSet(segByte, seg);

    digitalWrite(SEG_LATCH_PIN, LOW);
    shiftOut(SEG_SER_PIN, SEG_CLK_PIN, MSBFIRST, ~segByte);
    digitalWrite(SEG_LATCH_PIN, HIGH);

    delay(100);
  }
}

void EraseAll()
{
  for (byte r = 0; r < 9; r++)
  {
    for (byte c = 0; c < 9; c++)
    {
      sudoku[r][c] = 0;
    }
  }
}


void FillRandomly()
{
  for (byte r = 0; r < 9; r++)
  {
    for (byte c = 0; c < 9; c++)
    {
      sudoku[r][c] = random(1, 10);
    }
  }
}

void FillVertically()
{
  byte n = 1;
  for (byte c = 0; c < 9; c++)
  {
    delay(100);
    for (byte r = 0; r < 9; r++)
    {
      sudoku[r][c] = c + 1;
    }
  }
}

void FillHorizontally()
{
  for (byte c = 0; c < 9; c++)
  {
    delay(100);
    sudoku[0][c] = c + 1;
    sudoku[1][8 - c] = c + 1;
    sudoku[2][c] = c + 1;
  }
}

void FillSudoku1()
{
  for (byte c = 0; c < 9; c++)
  {
    //delay(100);
    sudoku[0][c] = c + 1;
    sudoku[1][c] = ((c + 3) % 9) + 1;
    sudoku[2][c] = ((c + 6) % 9) + 1;
  }
}

void loop() {
  //  EraseAll();
  //  FillVertically();
  //  delay(1000);

//  EraseAll();
//  FillHorizontally();
//  delay(1000);

//  for (byte n = 0; n < 3; n++)
//  {
//    EraseAll();
//    FillRandomly();
//    delay(1000);
//  }
}
